#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "NAMA_WIFI";
const char* pass = "PASSWORD_WIFI";
#define BOT_TOKEN "TOKEN_DARI_BOTFATHER"
#define CHAT_ID   "CHAT_ID_KAMU"

const int SENSOR = 34;  // AO sensor hujan
const int IN1 = 26, IN2 = 27;  // driver L298N
const int LS_TUTUP = 32, LS_BUKA = 33;  // limit switch
const int AMBANG = 2000;  // makin basah, makin kecil

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
bool tertutup = false;

void motor(int a, int b) {
  digitalWrite(IN1, a);
  digitalWrite(IN2, b);
}

// putar motor sampai limit switch tertekan (maks. 15 detik)
void gerak(int a, int b, int ls) {
  unsigned long mulai = millis();
  motor(a, b);
  while (digitalRead(ls) == HIGH &&
         millis() - mulai < 15000) delay(10);
  motor(LOW, LOW);  // berhenti
}

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(LS_TUTUP, INPUT_PULLUP);  // tertekan = LOW
  pinMode(LS_BUKA, INPUT_PULLUP);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
}

void loop() {
  bool hujan = analogRead(SENSOR) < AMBANG;

  if (hujan && !tertutup) {
    gerak(HIGH, LOW, LS_TUTUP);  // tutup atap
    bot.sendMessage(CHAT_ID, "Hujan! Jemuran aman.", "");
    tertutup = true;
  }

  if (!hujan && tertutup) {
    gerak(LOW, HIGH, LS_BUKA);  // buka lagi
    bot.sendMessage(CHAT_ID, "Cerah, atap dibuka.", "");
    tertutup = false;
  }

  delay(1000);
}
