#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <time.h>

const char* SSID = "NamaWiFi";
const char* PASS = "PasswordWiFi";
#define BOT_TOKEN "TOKEN-DARI-BOTFATHER"
#define CHAT_ID   "ID-CHAT-KAMU"

const int REED = 27;            // reed switch ke GPIO 27 dan GND

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
bool tadiTerbuka = false;

String jamSekarang() {
  struct tm waktu;
  if (!getLocalTime(&waktu)) return "--:--";
  char buf[6];
  strftime(buf, sizeof(buf), "%H:%M", &waktu);
  return String(buf);
}

void setup() {
  pinMode(REED, INPUT_PULLUP);  // tertutup = LOW, terbuka = HIGH
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  configTime(7 * 3600, 0, "pool.ntp.org");  // WIB (UTC+7)
}

void loop() {
  bool terbuka = digitalRead(REED) == HIGH;

  if (terbuka && !tadiTerbuka) {       // tutup baru saja dibuka
    bot.sendMessage(CHAT_ID, "Paket datang! Jam " + jamSekarang(), "");
  }
  tadiTerbuka = terbuka;
  delay(200);
}
