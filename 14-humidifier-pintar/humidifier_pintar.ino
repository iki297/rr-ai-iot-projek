#include <DHT.h>

const int MOSFET = 26;           // gate MOSFET modul kabut
const float NYALA = 45.0;        // % kelembapan: kabut nyala
const float MATI  = 60.0;        // % kelembapan: kabut mati
DHT dht(4, DHT22);               // data DHT22 di GPIO 4
bool kabut = false;

void setup() {
  Serial.begin(115200);
  pinMode(MOSFET, OUTPUT);
  digitalWrite(MOSFET, LOW);     // mulai dalam keadaan mati
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  if (isnan(h)) {                // sensor gagal dibaca
    digitalWrite(MOSFET, LOW);   // demi aman, matikan kabut
    kabut = false;
    delay(2000);
    return;
  }
  if (!kabut && h < NYALA) kabut = true;   // terlalu kering
  if (kabut && h >= MATI) kabut = false;   // sudah cukup lembap
  digitalWrite(MOSFET, kabut ? HIGH : LOW);

  Serial.print("Kelembapan: "); Serial.print(h);
  Serial.println(kabut ? " %  kabut ON" : " %  kabut OFF");
  delay(2000);                   // DHT22 dibaca tiap 2 detik
}
