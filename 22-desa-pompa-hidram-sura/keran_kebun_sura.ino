// Keran Kebun Otomatis - Kak Sura (Desa Pintar Sukamaju)
// Pompa hidram menaikkan air ke tangki TANPA listrik.
// ESP32 (tenaga surya) hanya membaca kelembapan tanah dan membuka/menutup keran tangki.
//
// Rangkaian:
//   Panel surya 12V -> solar charge controller -> aki 12V 7Ah
//   Aki 12V -> LM2596 (diatur 5V) -> ESP32 VIN
//   Aki 12V -> L298N 12V ; L298N GND = GND ESP32 (jumper ENA tetap terpasang)
//   L298N  : IN1 -> GPIO26, IN2 -> GPIO27, OUT1/OUT2 -> motorized ball valve 12V (2 kabel)
//            valve 2 kabel dibalik polaritasnya: (+,-) = BUKA, (-,+) = TUTUP, butuh 3-5 detik
//   Sensor kelembapan tanah kapasitif: VCC -> 3V3, GND -> GND, AOUT -> GPIO34
//
// Kebun jauh dari Wi-Fi desa? Pakai repeater Wi-Fi atau LoRa.
// Library: PubSubClient

#include <WiFi.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "WiFi_Desa_Sukamaju";
const char* WIFI_PASS = "password_wifi";
const char* MQTT_HOST = "192.168.1.10";      // IP server Pak Kades
const char* MQTT_USER = "sura";              // akun MQTT Kak Sura
const char* MQTT_PASS = "password_sura";

#define IN1 26
#define IN2 27
#define SENSOR 34
const int NILAI_KERING = 3000;   // kalibrasi: nilai ADC saat sensor di udara
const int NILAI_BASAH  = 1300;   // kalibrasi: nilai ADC saat sensor di air
const unsigned long LAMA_GERAK = 6000;      // waktu valve berputar penuh (ms)

WiFiClient net;
PubSubClient mqtt(net);
String posisi = "";
unsigned long lastKirim = 0;

void gerakKeran(bool buka) {
  digitalWrite(IN1, buka ? HIGH : LOW);
  digitalWrite(IN2, buka ? LOW : HIGH);
  delay(LAMA_GERAK);                         // tunggu valve sampai ujung
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);   // lepas, valve tetap di posisinya
}

void terimaPesan(char* topic, byte* payload, unsigned int len) {
  String isi;
  for (unsigned int i = 0; i < len; i++) isi += (char)payload[i];
  if (isi != "BUKA" && isi != "TUTUP") return;
  if (isi == posisi) return;                 // sudah di posisi itu
  gerakKeran(isi == "BUKA");
  posisi = isi;
  mqtt.publish("desa/sura/status", posisi.c_str(), true);
}

void sambung() {
  while (!mqtt.connected()) {
    if (mqtt.connect("esp32-sura", MQTT_USER, MQTT_PASS)) {
      mqtt.subscribe("desa/sura/keran");
    } else {
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqtt.setServer(MQTT_HOST, 1883);
  mqtt.setCallback(terimaPesan);
}

void loop() {
  if (!mqtt.connected()) sambung();
  mqtt.loop();

  if (millis() - lastKirim > 60000) {          // kirim tiap 1 menit
    lastKirim = millis();
    int raw = analogRead(SENSOR);
    int tanah = constrain(map(raw, NILAI_KERING, NILAI_BASAH, 0, 100), 0, 100);
    char json[32];
    snprintf(json, sizeof(json), "{\"tanah\":%d}", tanah);
    mqtt.publish("desa/sura/kebun", json);
    Serial.println(json);
  }
}
