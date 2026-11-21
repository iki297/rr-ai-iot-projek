#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* SSID = "NamaWiFi";
const char* PASS = "PasswordWiFi";
const char* SERVER = "IP-SERVER";   // IP VPS
const int TANAH = 34;               // AO sensor tanah
const int KERING = 3000, BASAH = 1200;  // hasil kalibrasi

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
    mqtt.connect("esp32-kebun", "rizky", "PASSWORD");
  mqtt.loop();

  int tanah = map(analogRead(TANAH), KERING, BASAH, 0, 100);
  tanah = constrain(tanah, 0, 100);
  float suhu = dht.readTemperature();
  float lembap = dht.readHumidity();

  mqtt.publish("kebun/tanah", String(tanah).c_str());
  if (!isnan(suhu) && !isnan(lembap)) {
    mqtt.publish("kebun/suhu", String(suhu, 1).c_str());
    mqtt.publish("kebun/kelembapan", String(lembap, 1).c_str());
  }
  delay(5000);                      // tiap 5 detik
}
