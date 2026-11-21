// Stasiun Pemantau Udara Desa - Desa Pintar Sukamaju
// ESP32 + DHT22 + MQ-135, kirim data ke Node-RED (MQTT)
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// ---------- Wi-Fi & MQTT ----------
const char* WIFI_SSID = "WiFi_Desa";
const char* WIFI_PASS = "password_wifi";
const char* MQTT_HOST = "IP_SERVER_MQTT";
const int   MQTT_PORT = 1883;
const char* TOPIC     = "desa/udara";

// ---------- Pin ----------
#define DHT_PIN   4      // DATA DHT22
#define DHT_TYPE  DHT22
#define MQ_PIN    34     // AO MQ-135 (lewat pembagi)

DHT dht(DHT_PIN, DHT_TYPE);
WiFiClient espClient;
PubSubClient mqtt(espClient);
unsigned long lastSend = 0;

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void connectMQTT() {
  while (!mqtt.connected()) {
    if (!mqtt.connect("stasiun-udara-01")) {
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  analogReadResolution(12);       // 0 - 4095
  connectWiFi();
  mqtt.setServer(MQTT_HOST, MQTT_PORT);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) connectWiFi();
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();

  if (millis() - lastSend < 5000) return;  // tiap 5 dtk
  lastSend = millis();

  // 1. Baca suhu & kelembapan (DHT22)
  float suhu   = dht.readTemperature();
  float lembap = dht.readHumidity();
  if (isnan(suhu) || isnan(lembap)) return;

  // 2. Baca kualitas udara (MQ-135)
  int gas = analogRead(MQ_PIN);
  const char* status;
  if (gas < 1500)      status = "BERSIH";
  else if (gas < 2500) status = "SEDANG";
  else                 status = "KOTOR";
  // batas di atas: sesuaikan setelah kalibrasi

  // 3. Kirim ke Node-RED lewat MQTT
  char data[128];
  snprintf(data, sizeof(data),
    "{\"suhu\":%.1f,\"lembap\":%.1f,"
    "\"gas\":%d,\"status\":\"%s\"}",
    suhu, lembap, gas, status);
  mqtt.publish(TOPIC, data);
  Serial.println(data);
}
