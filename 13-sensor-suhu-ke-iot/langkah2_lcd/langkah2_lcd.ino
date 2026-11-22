// RR – AI dan IoT Projek | Dari Sensor ke IoT – Langkah 2/3
// ESP32 + DHT22 + LCD 16x2 I2C: suhu tampil di layar
// Wiring DHT22 : DATA > GPIO4, VCC > 3V3, GND > GND
// Wiring LCD   : VCC > VIN (5V), GND > GND, SDA > GPIO21, SCL > GPIO22

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Alamat I2C biasanya 0x27. Kalau layar kosong, coba ganti ke 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);  // SDA, SCL
  lcd.init();
  lcd.backlight();
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Monitor Suhu");
  delay(1500);
  lcd.clear();
}

void loop() {
  float suhu = dht.readTemperature();
  float lembab = dht.readHumidity();

  lcd.clear();
  if (isnan(suhu) || isnan(lembab)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor error!");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Suhu  : ");
    lcd.print(suhu, 1);
    lcd.print((char)223);  // simbol derajat di LCD
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Lembab: ");
    lcd.print(lembab, 0);
    lcd.print(" %");
  }
  delay(2000);
}
