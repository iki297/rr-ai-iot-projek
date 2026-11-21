// Sensor Cuaca Kak Sanmey - Desa Pintar Sukamaju
// ESP32 + BME280 (I2C) + sensor hujan FC-37/YL-83 -> server desa (MQTT)
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_BME280.h>

const char* WIFI_SSID = "WiFi_Rumah_Sanmey";
const char* WIFI_PASS = "password_wifi";
const char* MQTT_HOST = "IP_SERVER_PAK_KADES";   // lewat VPN (Tailscale/ZeroTier)
const char* MQTT_USER = "sanmey";
const char* MQTT_PASS = "password_sanmey";
const char* TOPIC     = "desa/sanmey/cuaca";

#define HUJAN_VCC 25   // daya sensor hujan, nyala hanya saat membaca
#define HUJAN_AO  34   // AO sensor hujan (basah = nilai kecil)
// BME280: SDA = GPIO21, SCL = GPIO22, VCC = 3.3V

Adafruit_BME280 bme;
WiFiClient espClient;
PubSubClient mqtt(espClient);
unsigned long lastSend = 0;

void connectMQTT() {
  while (!mqtt.connected()) {
    if (!mqtt.connect("cuaca-sanmey", MQTT_USER, MQTT_PASS)) delay(2000);
  }
}

int bacaHujan() {
  digitalWrite(HUJAN_VCC, HIGH);
  delay(100);
  int nilai = analogRead(HUJAN_AO);
  digitalWrite(HUJAN_VCC, LOW);          // supaya pelat tidak cepat berkarat
  return nilai;
}

void setup() {
  Serial.begin(115200);
  pinMode(HUJAN_VCC, OUTPUT);
  if (!bme.begin(0x76)) {                // coba 0x77 kalau gagal
    Serial.println("BME280 tidak terdeteksi!");
  }
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqtt.setServer(MQTT_HOST, 1883);
}

void loop() {
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();
  if (millis() - lastSend < 60000) return;    // kirim tiap 1 menit
  lastSend = millis();

  float tekanan = bme.readPressure() / 100.0;  // Pa -> hPa
  float lembap  = bme.readHumidity();
  float suhu    = bme.readTemperature();
  int hujan     = bacaHujan();

  char data[128];
  snprintf(data, sizeof(data),
    "{\"tekanan\":%.1f,\"lembap\":%.1f,\"suhu\":%.1f,\"hujan\":%d}",
    tekanan, lembap, suhu, hujan);
  mqtt.publish(TOPIC, data);
  Serial.println(data);
}
