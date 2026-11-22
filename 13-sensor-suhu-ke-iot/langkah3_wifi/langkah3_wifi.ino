// RR – AI dan IoT Projek | Dari Sensor ke IoT – Langkah 3/3
// ESP32 + DHT22 + LCD I2C + WiFi: suhu bisa dilihat dari HP (IoT jaringan lokal)
// Wiring DHT22 : DATA > GPIO4, VCC > 3V3, GND > GND
// Wiring LCD   : VCC > VIN (5V), GND > GND, SDA > GPIO21, SCL > GPIO22
// Cara pakai: upload, lihat alamat IP di LCD / Serial Monitor,
// lalu buka alamat itu di browser HP. HP harus di WiFi yang sama.

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ===== Isi dengan WiFi rumah kamu =====
const char* ssid     = "NAMA_WIFI";
const char* password = "PASSWORD_WIFI";

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // coba 0x3F kalau layar kosong
WebServer server(80);

float suhu = NAN, lembab = NAN;
unsigned long terakhirBaca = 0;

// Halaman web yang dibuka di HP (otomatis update tiap 2 detik)
const char halaman[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Monitor Suhu</title>
<style>
 body{font-family:sans-serif;text-align:center;background:#0c1226;color:#fff;margin:0;padding:24px}
 .kartu{border-radius:20px;padding:24px;margin:16px auto;max-width:320px}
 .suhu{background:#00aae6}.lembab{background:#3cc878}
 .angka{font-size:56px;font-weight:bold}
</style></head><body>
<h2>Monitor Suhu</h2>
<div class="kartu suhu"><div class="angka" id="s">--</div>Suhu</div>
<div class="kartu lembab"><div class="angka" id="l">--</div>Kelembapan</div>
<script>
async function ambil(){
  try{
    const r = await fetch('/data'); const d = await r.json();
    document.getElementById('s').innerText = d.suhu + ' °C';
    document.getElementById('l').innerText = d.lembab + ' %';
  }catch(e){}
}
ambil(); setInterval(ambil, 2000);
</script></body></html>
)rawliteral";

void kirimHalaman() {
  server.send_P(200, "text/html", halaman);
}

void kirimData() {
  String json = "{\"suhu\":\"" + (isnan(suhu) ? String("--") : String(suhu, 1)) +
                "\",\"lembab\":\"" + (isnan(lembab) ? String("--") : String(lembab, 0)) + "\"}";
  server.send(200, "application/json", json);
}

void tampilLCD() {
  lcd.clear();
  if (isnan(suhu) || isnan(lembab)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor error!");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Suhu  : ");
    lcd.print(suhu, 1);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Lembab: ");
    lcd.print(lembab, 0);
    lcd.print(" %");
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Konek WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Tampilkan alamat IP: ini yang diketik di browser HP
  Serial.println();
  Serial.print("Buka di HP: http://");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Buka di HP:");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(5000);

  server.on("/", kirimHalaman);
  server.on("/data", kirimData);
  server.begin();
}

void loop() {
  server.handleClient();

  if (millis() - terakhirBaca >= 2000) {
    terakhirBaca = millis();
    suhu = dht.readTemperature();
    lembab = dht.readHumidity();
    tampilLCD();
  }
}
