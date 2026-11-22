// RR – AI dan IoT Projek | Dari Sensor ke IoT – Langkah 1/3
// ESP32 + DHT22: alat pendeteksi suhu (hasil dilihat di Serial Monitor)
// Wiring DHT22: DATA > GPIO4, VCC > 3V3, GND > GND

#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float suhu = dht.readTemperature();
  float lembab = dht.readHumidity();

  if (isnan(suhu) || isnan(lembab)) {
    Serial.println("Gagal membaca DHT22, cek kabel!");
  } else {
    Serial.print("Suhu: ");
    Serial.print(suhu, 1);
    Serial.print(" C | Kelembapan: ");
    Serial.print(lembab, 0);
    Serial.println(" %");
  }
  delay(2000);  // DHT22 dibaca paling cepat tiap 2 detik
}
