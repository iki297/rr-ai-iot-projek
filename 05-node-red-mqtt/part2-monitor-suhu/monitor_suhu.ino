#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* SSID = "NamaWiFi";
const char* PASS = "PasswordWiFi";
const char* SERVER = "IP-SERVER";   // IP VPS

DHT dht(4, DHT22);                  // data di GPIO 4
WiFiClient wifi;
PubSubClient mqtt(wifi);

void setup() {
  dht.begin();
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqtt.setServer(SERVER, 1883);
}

void loop() {
  if (!mqtt.connected())
    mqtt.connect("esp32-kamar", "rizky", "PASSWORD");
  mqtt.loop();

  float s = dht.readTemperature();
  float k = dht.readHumidity();
  if (!isnan(s) && !isnan(k)) {
    mqtt.publish("rr/suhu", String(s, 1).c_str());
    mqtt.publish("rr/kelembapan", String(k, 1).c_str());
  }
  delay(5000);                      // tiap 5 detik
}
