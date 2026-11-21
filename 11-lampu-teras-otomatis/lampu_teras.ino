const int LDR = 34;            // AO sensor cahaya
const int PIR = 27;            // OUT sensor gerak
const int RELAY = 26;          // relay lampu teras

const int BATAS_GELAP = 2500;            // atur dari hasil uji
const unsigned long NYALA_MS = 60000;    // 1 menit

unsigned long gerakTerakhir = 0;
bool lampu = false;

void setup() {
  Serial.begin(115200);
  pinMode(PIR, INPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
}

void loop() {
  int cahaya = analogRead(LDR);
  Serial.println(cahaya);               // cek nilai terang & gelap
  bool gelap = cahaya > BATAS_GELAP;    // modul ini: gelap = nilai besar
  bool gerak = digitalRead(PIR) == HIGH;

  if (gelap && gerak) {                 // gelap DAN ada orang
    gerakTerakhir = millis();
    if (!lampu) {
      lampu = true;
      digitalWrite(RELAY, HIGH);
    }
  }

  if (lampu && millis() - gerakTerakhir > NYALA_MS) {
    lampu = false;                      // 1 menit tanpa gerakan
    digitalWrite(RELAY, LOW);
  }
  delay(100);
}
