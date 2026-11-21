// Pendingin Ruangan Otomatis - Kamar Kak Rido (Desa Pintar Sukamaju)
// ESP32 + DHT22 + PIR HC-SR501 + modul relay 5V (kipas angin)
// Data dikirim ke server desa (Pak Kades), keputusan kipas dari Node-RED.
//
// Rangkaian:
//   DHT22   : VCC->3V3, DATA->GPIO27, GND->GND  (pakai modul DHT22 / resistor 10K ke 3V3)
//   PIR     : VCC->5V (VIN), OUT->GPIO14, GND->GND
//   Relay   : VCC->5V (VIN), IN->GPIO26, GND->GND
//             Kabel listrik kipas (220V) lewat terminal COM dan NO relay.
//   HATI-HATI 220V: cabut steker saat memasang, tutup semua sambungan.
//
// Library: PubSubClient (Nick O'Leary), DHT sensor library (Adafruit)

#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* WIFI_SSID = "WiFi_Desa_Sukamaju";
const char* WIFI_PASS = "password_wifi";
const char* MQTT_HOST = "192.168.1.10";      // IP server Pak Kades
const char* MQTT_USER = "rido";              // akun MQTT Kak Rido
const char* MQTT_PASS = "password_rido";

#define DHT_PIN    27
#define PIR_PIN    14
#define RELAY_PIN  26
#define RELAY_ON   LOW      // kebanyakan modul relay aktif LOW, ganti HIGH jika terbalik
#define RELAY_OFF  HIGH

DHT dht(DHT_PIN, DHT22);
WiFiClient net;
PubSubClient mqtt(net);

bool adaGerak = false;            // ada gerakan selama 1 menit terakhir?
unsigned long lastKirim = 0;

void terimaPesan(char* topic, byte* payload, unsigned int len) {
  String isi;
  for (unsigned int i = 0; i < len; i++) isi += (char)payload[i];
  if (isi == "ON")  digitalWrite(RELAY_PIN, RELAY_ON);
  if (isi == "OFF") digitalWrite(RELAY_PIN, RELAY_OFF);
  Serial.println("Kipas: " + isi);
}

void sambung() {
  while (!mqtt.connected()) {
    if (mqtt.connect("esp32-rido", MQTT_USER, MQTT_PASS)) {
      mqtt.subscribe("desa/rido/kipas");
    } else {
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF);
  dht.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqtt.setServer(MQTT_HOST, 1883);
  mqtt.setCallback(terimaPesan);
}

void loop() {
  if (!mqtt.connected()) sambung();
  mqtt.loop();

  if (digitalRead(PIR_PIN) == HIGH) adaGerak = true;

  if (millis() - lastKirim > 60000) {          // kirim tiap 1 menit
    lastKirim = millis();
    float suhu = dht.readTemperature();
    float lembap = dht.readHumidity();
    if (isnan(suhu) || isnan(lembap)) return;
    char json[96];
    snprintf(json, sizeof(json),
             "{\"suhu\":%.1f,\"lembap\":%.0f,\"gerak\":%d}",
             suhu, lembap, adaGerak ? 1 : 0);
    mqtt.publish("desa/rido/kamar", json);
    Serial.println(json);
    adaGerak = false;
  }
}
