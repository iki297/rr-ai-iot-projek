// Penegur jarak nonton TV: buzzer bunyi kalau anak terlalu dekat
const int TRIG = 5;              // HC-SR04 Trig
const int ECHO = 18;             // HC-SR04 Echo lewat pembagi 1k/2k
const int BUZZER = 26;           // modul buzzer aktif
const int LED = 27;              // LED merah + resistor 220
const int BATAS_CM = 150;        // lebih dekat dari ini = terlalu dekat
const unsigned long TUNGGU_MS = 3000;   // harus dekat 3 detik dulu
unsigned long mulaiDekat = 0;

int ukurCm() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long us = pulseIn(ECHO, HIGH, 30000);   // maks sekitar 5 meter
  if (us == 0) return -1;                 // tidak ada pantulan
  return us * 0.0343 / 2;                 // kecepatan suara 343 m/s, pulang-pergi
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT); pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT); pinMode(LED, OUTPUT);
}

void loop() {
  int cm = ukurCm();
  bool dekat = cm > 0 && cm < BATAS_CM;

  if (!dekat) mulaiDekat = 0;
  else if (mulaiDekat == 0) mulaiDekat = millis();

  bool tegur = mulaiDekat > 0 && millis() - mulaiDekat >= TUNGGU_MS;
  bool kedip = (millis() / 250) % 2;      // bunyi putus-putus
  digitalWrite(BUZZER, tegur && kedip);
  digitalWrite(LED, tegur);

  Serial.printf("Jarak %d cm  %s\n", cm, tegur ? "TERLALU DEKAT" : "aman");
  delay(60);
}
