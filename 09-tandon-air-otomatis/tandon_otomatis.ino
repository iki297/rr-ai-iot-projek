#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* SSID = "NamaWiFi";
const char* PASS = "PasswordWiFi";
#define BOT_TOKEN "TOKEN-DARI-BOTFATHER"
#define CHAT_ID   "ID-CHAT-KAMU"

const int TRIG = 5, ECHO = 18, RELAY = 26;
const float KOSONG = 120;   // jarak sensor ke dasar (cm)
const float PENUH  = 30;    // jarak saat penuh (min 25 cm)

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
bool pompa = false;

float bacaJarak() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long waktu = pulseIn(ECHO, HIGH, 30000);  // waktu pantul (us)
  return waktu * 0.0343 / 2;                // jadi cm
}

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
}

void loop() {
  float jarak = bacaJarak();
  int persen = (KOSONG - jarak) * 100 / (KOSONG - PENUH);
  persen = constrain(persen, 0, 100);

  if (persen < 20 && !pompa) {
    pompa = true;
    digitalWrite(RELAY, HIGH);
    bot.sendMessage(CHAT_ID, "Air " + String(persen) + "%, pompa NYALA", "");
  }
  if (persen >= 90 && pompa) {
    pompa = false;
    digitalWrite(RELAY, LOW);
    bot.sendMessage(CHAT_ID, "Tandon penuh, pompa MATI", "");
  }
  delay(2000);
}
