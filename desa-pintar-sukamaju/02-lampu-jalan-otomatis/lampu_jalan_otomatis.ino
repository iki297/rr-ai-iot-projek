// Lampu Jalan Otomatis - Desa Pintar Sukamaju
// ESP32 + LDR + RCWL-0516 + LED 12V (MOSFET) + MQTT
#include <WiFi.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "WiFi_Desa";
const char* WIFI_PASS = "password_wifi";
const char* MQTT_HOST = "IP_SERVER_MQTT";
const char* TOPIC     = "desa/lampu";

#define LDR_PIN    34   // AO modul LDR
#define RADAR_PIN  27   // OUT RCWL-0516
#define LAMPU_PIN  25   // gate MOSFET (lewat 220)

const int BATAS_GELAP = 2500;  // cek di Serial Monitor
const int REDUP  = 70;         // PWM 0-255 (~30%)
const int TERANG = 255;        // PWM 100%
const unsigned long LAMA_TERANG = 10000;  // 10 dtk

WiFiClient espClient;
PubSubClient mqtt(espClient);
unsigned long terakhirGerak = 0;
unsigned long lastSend = 0;
int jumlahKendaraan = 0;
bool gerakSebelum = false;

void connectMQTT() {
  while (!mqtt.connected()) {
    if (!mqtt.connect("lampu-jalan-01")) delay(2000);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RADAR_PIN, INPUT);
  ledcAttach(LAMPU_PIN, 5000, 8);   // PWM 5 kHz, 8 bit
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqtt.setServer(MQTT_HOST, 1883);
}

void loop() {
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();

  // 1. Cek: sudah malam atau belum?
  int cahaya = analogRead(LDR_PIN);
  bool malam = cahaya > BATAS_GELAP;  // makin gelap,
                                      // nilai makin besar

  // 2. Ada gerakan? Lampu jadi terang
  bool gerak = digitalRead(RADAR_PIN);
  if (gerak && !gerakSebelum && malam) jumlahKendaraan++;
  gerakSebelum = gerak;
  if (gerak) terakhirGerak = millis();

  int pwm = 0;                      // siang: lampu mati
  if (malam) {
    bool lewat = millis() - terakhirGerak < LAMA_TERANG;
    pwm = lewat ? TERANG : REDUP;
  }
  ledcWrite(LAMPU_PIN, pwm);

  // 3. Kirim status ke Node-RED tiap 5 detik
  if (millis() - lastSend >= 5000) {
    lastSend = millis();
    char data[96];
    snprintf(data, sizeof(data),
      "{\"cahaya\":%d,\"pwm\":%d,\"kendaraan\":%d}",
      cahaya, pwm, jumlahKendaraan);
    mqtt.publish(TOPIC, data);
    Serial.println(data);
  }
}
