// Lampu jalan pintar: redup saat sepi, terang saat ada yang lewat
const int LDR   = 34;            // AO modul sensor cahaya
const int RADAR = 27;            // OUT sensor radar (3.3V)
const int LAMPU = 26;            // gate MOSFET lampu LED 12V
const int BATAS_GELAP = 2500;    // cek di Serial Monitor, sesuaikan
const int REDUP = 51;            // 20% dari 255
const int TERANG = 255;          // 100%
const unsigned long TAHAN_MS = 30000;   // 30 detik
unsigned long terakhirGerak = 0;
int sekarang = 0;

void setup() {
  Serial.begin(115200);
  pinMode(RADAR, INPUT);
  ledcAttach(LAMPU, 5000, 8);    // PWM 5 kHz, 8 bit
  ledcWrite(LAMPU, 0);
}

void loop() {
  int cahaya = analogRead(LDR);  // makin gelap, makin besar
  bool malam = cahaya > BATAS_GELAP;
  if (digitalRead(RADAR) == HIGH) terakhirGerak = millis();
  bool adaOrang = millis() - terakhirGerak < TAHAN_MS;

  int target = 0;                          // siang: mati
  if (malam) target = adaOrang ? TERANG : REDUP;

  // ubah terang pelan-pelan biar halus
  if (sekarang < target) sekarang = min(sekarang + 5, target);
  if (sekarang > target) sekarang = max(sekarang - 2, target);
  ledcWrite(LAMPU, sekarang);

  Serial.printf("cahaya %d  gerak %d  lampu %d\n", cahaya, adaOrang, sekarang);
  delay(20);
}
