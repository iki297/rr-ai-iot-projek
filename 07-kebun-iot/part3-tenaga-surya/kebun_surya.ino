#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* SSID = "NamaWiFi";
const char* PASS = "PasswordWiFi";
const char* SERVER = "IP-SERVER";   // IP VPS
const int TANAH = 34, AKI = 33;     // pin analog
const int KERING = 3000, BASAH = 1200;
const uint64_t TIDUR = 10ULL * 60 * 1000000;  // 10 menit

DHT dht(4, DHT22);
WiFiClient wifi;
PubSubClient mqtt(wifi);

void kirim(const char* topik, float nilai) {
  mqtt.publish(topik, String(nilai, 1).c_str());
}

void setup() {
  dht.begin();
  WiFi.begin(SSID, PASS);
  for (int i = 0; i < 40 && WiFi.status() != WL_CONNECTED; i++)
    delay(500);
  mqtt.setServer(SERVER, 1883);

  if (mqtt.connect("esp32-kebun", "rizky", "PASSWORD")) {
    int tanah = map(analogRead(TANAH), KERING, BASAH, 0, 100);
    kirim("kebun/tanah", constrain(tanah, 0, 100));
    kirim("kebun/suhu", dht.readTemperature());
    kirim("kebun/kelembapan", dht.readHumidity());

    // tegangan aki lewat pembagi 100k : 47k
    float vPin = analogReadMilliVolts(AKI) / 1000.0;
    kirim("kebun/aki", vPin * 147.0 / 47.0);

    mqtt.loop();
    delay(500);                     // beri waktu kirim
  }
  esp_sleep_enable_timer_wakeup(TIDUR);
  esp_deep_sleep_start();           // tidur 10 menit
}

void loop() {}
