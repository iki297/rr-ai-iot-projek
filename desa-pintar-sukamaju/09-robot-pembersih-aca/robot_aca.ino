// Robot Pembersih Rumah - Kak Aca (Desa Pintar Sukamaju)
// ESP32 + driver motor L298N + 2 motor TT + HC-SR04 + kipas penyedot (MOSFET)
// Perintah dari server desa (Node-RED): "MULAI" / "STOP" di topic desa/aca/robot
//
// Rangkaian:
//   Baterai 2x18650 (7.4V) -> saklar -> L298N 12V, GND
//   L298N 5V  -> ESP32 VIN dan HC-SR04 VCC  (semua GND disatukan)
//   L298N     : ENA->GPIO14, IN1->GPIO25, IN2->GPIO26   (motor kiri  di OUT1/OUT2)
//               ENB->GPIO32, IN3->GPIO27, IN4->GPIO33   (motor kanan di OUT3/OUT4)
//               lepas jumper ENA/ENB supaya kecepatan bisa diatur PWM
//   HC-SR04   : TRIG->GPIO5, ECHO->GPIO18 lewat pembagi tegangan (1K ke ECHO, 2K ke GND)
//   Kipas     : MOSFET IRLZ44N, gate<-GPIO4 lewat 220 ohm (+10K ke GND)
//               kipas + ke baterai, kipas - ke drain, source ke GND, dioda 1N4007 paralel kipas
//
// Library: PubSubClient. Butuh board ESP32 core 3.x (ledcAttach).

#include <WiFi.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "WiFi_Desa_Sukamaju";
const char* WIFI_PASS = "password_wifi";
const char* MQTT_HOST = "192.168.1.10";      // IP server Pak Kades
const char* MQTT_USER = "aca";               // akun MQTT Kak Aca
const char* MQTT_PASS = "password_aca";

#define ENA 14
#define IN1 25
#define IN2 26
#define ENB 32
#define IN3 27
#define IN4 33
#define TRIG 5
#define ECHO 18
#define KIPAS 4

const int KECEPATAN = 170;                   // 0-255
const int JARAK_AMAN = 20;                   // cm
const unsigned long LAMA_BERSIH = 20UL * 60UL * 1000UL;   // 20 menit

WiFiClient net;
PubSubClient mqtt(net);
bool bersih = false;
unsigned long mulaiBersih = 0;

void motor(int kiri, int kanan) {            // -255..255
  digitalWrite(IN1, kiri > 0);  digitalWrite(IN2, kiri < 0);
  digitalWrite(IN3, kanan > 0); digitalWrite(IN4, kanan < 0);
  ledcWrite(ENA, abs(kiri));    ledcWrite(ENB, abs(kanan));
}

long bacaJarak() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long durasi = pulseIn(ECHO, HIGH, 30000);  // maks 30 ms
  if (durasi == 0) return 999;               // tidak ada pantulan
  return durasi / 58;                        // cm
}

void kirimStatus(const char* s) { mqtt.publish("desa/aca/status", s); }

void mulai() {
  bersih = true; mulaiBersih = millis();
  digitalWrite(KIPAS, HIGH);
  kirimStatus("MEMBERSIHKAN");
}

void berhenti(const char* alasan) {
  bersih = false;
  motor(0, 0);
  digitalWrite(KIPAS, LOW);
  kirimStatus(alasan);
}

void terimaPesan(char* topic, byte* payload, unsigned int len) {
  String isi;
  for (unsigned int i = 0; i < len; i++) isi += (char)payload[i];
  if (isi == "MULAI") mulai();
  if (isi == "STOP")  berhenti("BERHENTI");
}

void sambung() {
  while (!mqtt.connected()) {
    if (mqtt.connect("esp32-aca", MQTT_USER, MQTT_PASS)) {
      mqtt.subscribe("desa/aca/robot");
      kirimStatus("SIAP");
    } else {
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  int keluaran[] = {IN1, IN2, IN3, IN4, TRIG, KIPAS};
  for (int p : keluaran) pinMode(p, OUTPUT);
  pinMode(ECHO, INPUT);
  ledcAttach(ENA, 1000, 8);                  // PWM 1 kHz, 8 bit
  ledcAttach(ENB, 1000, 8);
  motor(0, 0);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqtt.setServer(MQTT_HOST, 1883);
  mqtt.setCallback(terimaPesan);
}

void loop() {
  if (!mqtt.connected()) sambung();
  mqtt.loop();
  if (!bersih) return;

  if (millis() - mulaiBersih > LAMA_BERSIH) {
    berhenti("SELESAI");         // Node-RED kirim notifikasi
    return;
  }

  if (bacaJarak() < JARAK_AMAN) {  // ada tembok / kursi
    motor(0, 0);                   // berhenti
    delay(200);
    motor(-KECEPATAN, -KECEPATAN); // mundur sedikit
    delay(400);
    int arah = random(2) ? 1 : -1; // belok kiri / kanan
    motor(KECEPATAN * arah, -KECEPATAN * arah);
    delay(450);
  } else {
    motor(KECEPATAN, KECEPATAN);   // maju terus
  }
  delay(30);
}
