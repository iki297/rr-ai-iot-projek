#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char* SSID = "NamaWiFi";
const char* PASS = "PasswordWiFi";
#define BOT_TOKEN "TOKEN-DARI-BOTFATHER"
#define CHAT_ID   "ID-CHAT-KAMU"

const int PIN_SUHU = 4;          // DS18B20 (pull-up 4.7k ke 3V3)
const int PIN_PH   = 35;         // modul pH lewat pembagi 10k/20k
const int POMPA    = 26;         // relay pompa
const float V_PH7 = 2.50, V_PH4 = 3.04;   // hasil kalibrasi kamu
const unsigned long NYALA_MS = 15UL * 60000;   // pompa 15 menit
const unsigned long JEDA_MS  = 45UL * 60000;   // istirahat 45 menit

OneWire ow(PIN_SUHU); DallasTemperature suhuSensor(&ow);
WiFiClientSecure client; UniversalTelegramBot bot(BOT_TOKEN, client);
unsigned long mulaiSiklus = 0, terakhirLapor = 0;

float bacaPH() {
  long total = 0;
  for (int i = 0; i < 20; i++) { total += analogReadMilliVolts(PIN_PH); delay(10); }
  float v = total / 20.0 / 1000.0 * 1.5;           // balikkan pembagi tegangan
  float perPH = (V_PH4 - V_PH7) / 3.0;
  return 7.0 - (v - V_PH7) / perPH;
}

void setup() {
  Serial.begin(115200);
  pinMode(POMPA, OUTPUT);
  suhuSensor.begin();
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  bot.sendMessage(CHAT_ID, "Akuaponik online", "");
}

void loop() {
  // pompa terjadwal: 15 menit nyala, 45 menit mati
  unsigned long t = (millis() - mulaiSiklus) % (NYALA_MS + JEDA_MS);
  digitalWrite(POMPA, t < NYALA_MS ? HIGH : LOW);

  suhuSensor.requestTemperatures();
  float suhu = suhuSensor.getTempCByIndex(0);
  float ph = bacaPH();
  Serial.printf("Suhu %.1f C  pH %.2f\n", suhu, ph);

  bool aneh = suhu < 22 || suhu > 30 || ph < 6.0 || ph > 8.0;
  if (aneh && (terakhirLapor == 0 || millis() - terakhirLapor > 30UL * 60000)) {   // maks 1 pesan/30 menit
    String pesan = "Cek akuaponik!\nSuhu: " + String(suhu, 1) + " C\npH: " + String(ph, 2);
    bot.sendMessage(CHAT_ID, pesan, "");
    terakhirLapor = millis();
  }
  delay(5000);
}
