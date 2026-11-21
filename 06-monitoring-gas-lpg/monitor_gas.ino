#include <WiFi.h>
#include <PubSubClient.h>

const char* SSID = "NamaWiFi";
const char* PASS = "PasswordWiFi";
const char* SERVER = "IP-SERVER";   // IP VPS
const int SENSOR = 34;              // AO sensor gas

WiFiClient wifi;
PubSubClient mqtt(wifi);

void setup() {
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqtt.setServer(SERVER, 1883);
}

void loop() {
  if (!mqtt.connected())
    mqtt.connect("esp32-gas", "rizky", "PASSWORD");
  mqtt.loop();
  int gas = analogRead(SENSOR);     // 0 - 4095
  mqtt.publish("rr/gas", String(gas).c_str());
  delay(2000);                      // tiap 2 detik
}
