// Rumah Pintar - Desa Pintar Sukamaju
// ESP32 + relay 2 channel + sensor pintu MC-38 + MQTT
#include <WiFi.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "WiFi_Desa";
const char* WIFI_PASS = "password_wifi";
const char* MQTT_HOST = "IP_SERVER_MQTT";

#define RELAY_LAMPU  26   // IN1 relay (aktif LOW)
#define RELAY_KIPAS  27   // IN2 relay (aktif LOW)
#define PINTU_PIN    4    // MC-38: GPIO4 dan GND

WiFiClient espClient;
PubSubClient mqtt(espClient);
bool pintuLama = false;

// 1. Terima perintah dari ponsel lewat MQTT
void terimaPesan(char* topic, byte* isi, unsigned int len) {
  String pesan = "";
  for (unsigned int i = 0; i < len; i++) {
    pesan += (char)isi[i];
  }
  String t = String(topic);

  // 2. Nyalakan / matikan relay sesuai perintah
  bool nyala = (pesan == "ON");
  if (t == "desa/rumah/lampu")
    digitalWrite(RELAY_LAMPU, nyala ? LOW : HIGH);
  if (t == "desa/rumah/kipas")
    digitalWrite(RELAY_KIPAS, nyala ? LOW : HIGH);
}

void connectMQTT() {
  while (!mqtt.connected()) {
    if (mqtt.connect("rumah-pintar-01")) {
      mqtt.subscribe("desa/rumah/lampu");
      mqtt.subscribe("desa/rumah/kipas");
    } else {
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_LAMPU, OUTPUT);
  pinMode(RELAY_KIPAS, OUTPUT);
  digitalWrite(RELAY_LAMPU, HIGH);     // awal: mati
  digitalWrite(RELAY_KIPAS, HIGH);
  pinMode(PINTU_PIN, INPUT_PULLUP);    // tertutup = LOW
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqtt.setServer(MQTT_HOST, 1883);
  mqtt.setCallback(terimaPesan);
}

void loop() {
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();

  // 3. Kirim status pintu ke Node-RED saat berubah
  bool terbuka = digitalRead(PINTU_PIN) == HIGH;
  if (terbuka != pintuLama) {
    pintuLama = terbuka;
    mqtt.publish("desa/rumah/pintu",
                 terbuka ? "TERBUKA" : "TERTUTUP", true);
    Serial.println(terbuka ? "TERBUKA" : "TERTUTUP");
    delay(50);                         // anti-pantul
  }
}
