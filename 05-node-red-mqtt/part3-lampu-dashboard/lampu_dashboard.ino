#include <WiFi.h>
#include <PubSubClient.h>

const char* SSID = "NamaWiFi";
const char* PASS = "PasswordWiFi";
const char* SERVER = "IP-SERVER";   // IP VPS
const int RELAY = 26;               // aktif LOW

WiFiClient wifi;
PubSubClient mqtt(wifi);

void sambung() {
  while (!mqtt.connected()) {
    if (mqtt.connect("esp32-lampu", "rizky", "PASSWORD"))
      mqtt.subscribe("rr/lampu");
    else delay(2000);
  }
}

void terima(char* topik, byte* isi, unsigned int n) {
  String pesan = "";
  for (int i = 0; i < n; i++) pesan += (char)isi[i];
  if (pesan == "ON")  digitalWrite(RELAY, LOW);   // nyala
  if (pesan == "OFF") digitalWrite(RELAY, HIGH);  // mati
}

void setup() {
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);        // awal: mati
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqtt.setServer(SERVER, 1883);
  mqtt.setCallback(terima);
}

void loop() {
  sambung();
  mqtt.loop();
}
