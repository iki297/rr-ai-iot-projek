#include <WiFi.h>
#include <PubSubClient.h>
#include <PZEM004Tv30.h>

const char* SSID = "NamaWiFi";
const char* PASS = "PasswordWiFi";
const char* SERVER = "IP-SERVER";     // IP VPS (MQTT Broker)

PZEM004Tv30 pzem(Serial2, 16, 17);    // RX2 = GPIO 16, TX2 = GPIO 17
WiFiClient wifi;
PubSubClient mqtt(wifi);

void sambung() {
  while (!mqtt.connected()) {
    mqtt.connect("esp32-listrik", "rizky", "PASSWORD");
    delay(1000);
  }
}

void kirim(const char* topik, float nilai) {
  if (!isnan(nilai)) mqtt.publish(topik, String(nilai, 2).c_str());
}

void setup() {
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqtt.setServer(SERVER, 1883);
}

void loop() {
  sambung();
  mqtt.loop();

  kirim("listrik/tegangan", pzem.voltage());   // volt
  kirim("listrik/arus",     pzem.current());   // ampere
  kirim("listrik/daya",     pzem.power());     // watt
  kirim("listrik/energi",   pzem.energy());    // kWh

  delay(5000);                                 // tiap 5 detik
}
