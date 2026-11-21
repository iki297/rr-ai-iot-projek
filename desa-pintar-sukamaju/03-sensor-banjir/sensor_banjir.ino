// Sensor Peringatan Dini Banjir - Desa Pintar Sukamaju
// ESP32 + JSN-SR04T + LED indikator + relay sirene + MQTT
#include <WiFi.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "WiFi_Desa";
const char* WIFI_PASS = "password_wifi";
const char* MQTT_HOST = "IP_SERVER_MQTT";
const char* TOPIC     = "desa/banjir";

#define TRIG_PIN   5     // TRIG JSN-SR04T
#define ECHO_PIN   18    // ECHO (lewat pembagi 1K/2K)
#define LED_HIJAU  25
#define LED_KUNING 26
#define LED_MERAH  27
#define RELAY_PIN  23    // relay sirene (aktif LOW)

const float JARAK_DASAR = 400.0;  // sensor ke dasar sungai
const float WASPADA = 150.0;      // tinggi air (cm)
const float BAHAYA  = 200.0;      // tinggi air (cm)

WiFiClient espClient;
PubSubClient mqtt(espClient);
unsigned long lastSend = 0;
String statusLama = "";

void connectMQTT() {
  while (!mqtt.connected()) {
    if (!mqtt.connect("sensor-banjir-01")) delay(2000);
  }
}

float ukurJarak() {
  digitalWrite(TRIG_PIN, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long durasi = pulseIn(ECHO_PIN, HIGH, 30000);
  return durasi / 58.0;                 // cm
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(LED_KUNING, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);        // sirene mati
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqtt.setServer(MQTT_HOST, 1883);
}

void loop() {
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();

  // 1. Hitung tinggi air dari jarak sensor
  float jarak = ukurJarak();
  if (jarak <= 0) return;               // gagal baca
  float tinggi = JARAK_DASAR - jarak;

  // 2. Tentukan status: aman, waspada, bahaya
  String status = "AMAN";
  if (tinggi >= BAHAYA)       status = "BAHAYA";
  else if (tinggi >= WASPADA) status = "WASPADA";

  digitalWrite(LED_HIJAU,  status == "AMAN");
  digitalWrite(LED_KUNING, status == "WASPADA");
  digitalWrite(LED_MERAH,  status == "BAHAYA");
  digitalWrite(RELAY_PIN, status == "BAHAYA" ? LOW : HIGH);

  // 3. Kirim ke Node-RED (langsung saat status berubah)
  bool berubah = status != statusLama;
  if (berubah || millis() - lastSend >= 5000) {
    lastSend = millis();
    statusLama = status;
    char data[96];
    snprintf(data, sizeof(data),
      "{\"tinggi\":%.0f,\"status\":\"%s\"}",
      tinggi, status.c_str());
    mqtt.publish(TOPIC, data);
    Serial.println(data);
  }
}
