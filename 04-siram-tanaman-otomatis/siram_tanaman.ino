#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <time.h>

const char* ssid = "NAMA_WIFI";
const char* pass = "PASSWORD_WIFI";
#define BOT_TOKEN "TOKEN_DARI_BOTFATHER"
#define CHAT_ID   "CHAT_ID_KAMU"

const int SENSOR = 34;  // AO sensor kelembapan
const int RELAY = 26;   // relay pompa (aktif LOW)
const int KERING = 3000, BASAH = 1200;  // hasil kalibrasi

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
int hariSiram = -1;

int kelembapan() {
  int p = map(analogRead(SENSOR), KERING, BASAH, 0, 100);
  return constrain(p, 0, 100);
}

void siram() {
  digitalWrite(RELAY, LOW);   // pompa nyala
  delay(5000);                // selama 5 detik
  digitalWrite(RELAY, HIGH);  // pompa mati
}

void setup() {
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  configTime(7 * 3600, 0, "pool.ntp.org");  // jam WIB
}

void loop() {
  // 1. Siram otomatis setiap jam 8 pagi
  struct tm w;
  if (getLocalTime(&w) && w.tm_hour == 8 &&
      w.tm_mday != hariSiram) {
    siram();
    hariSiram = w.tm_mday;
    bot.sendMessage(CHAT_ID, "Jam 8: tanaman disiram.", "");
  }

  // 2 & 3. Perintah dari Telegram
  int n = bot.getUpdates(bot.last_message_received + 1);
  for (int i = 0; i < n; i++) {
    if (bot.messages[i].chat_id != CHAT_ID) continue;
    String teks = bot.messages[i].text;
    if (teks == "siram") {
      siram();
      bot.sendMessage(CHAT_ID, "Sudah disiram!", "");
    }
    if (teks == "cek") {
      bot.sendMessage(CHAT_ID,
      "Kelembapan tanah: " + String(kelembapan()) + "%", "");
    }
  }
  delay(1000);
}
