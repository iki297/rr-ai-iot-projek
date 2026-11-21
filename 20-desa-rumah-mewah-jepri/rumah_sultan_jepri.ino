// Rumah Mewah Serba Otomatis - Rumah Kak Jepri (Desa Pintar Sukamaju)
// ESP32 + sensor pintu MC-38 + relay lampu + stepper 28BYJ-48 (gorden) + DFPlayer Mini (sapaan)
// Sensor pintu dikirim ke server desa; Node-RED memilih mode lalu mengirim perintah "aksi".
//
// Rangkaian:
//   MC-38 (sensor pintu) : satu kabel -> GPIO13, satu kabel -> GND (pakai INPUT_PULLUP)
//   Relay 5V (lampu)     : VCC->5V (VIN), GND->GND, IN->GPIO26
//                          lampu 220V lewat terminal COM dan NO. HATI-HATI 220V!
//   ULN2003 + 28BYJ-48   : IN1->GPIO19, IN2->GPIO18, IN3->GPIO5, IN4->GPIO4
//                          VCC dari adaptor 5V terpisah, GND disatukan dengan ESP32
//   DFPlayer Mini        : VCC->5V (VIN), GND->GND, RX<-GPIO17 lewat resistor 1K, TX->GPIO16
//                          SPK_1 & SPK_2 -> speaker 3W 4-8 ohm
//   Kartu microSD (FAT32): /mp3/0001.mp3 = "Selamat datang di rumah, Kak Jepri!"
//                          /mp3/0002.mp3 = suara alarm
//
// Library: PubSubClient, ArduinoJson (v7), DFRobotDFPlayerMini, Stepper (bawaan)

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DFRobotDFPlayerMini.h>
#include <Stepper.h>

const char* WIFI_SSID = "WiFi_Desa_Sukamaju";
const char* WIFI_PASS = "password_wifi";
const char* MQTT_HOST = "192.168.1.10";      // IP server Pak Kades
const char* MQTT_USER = "jepri";             // akun MQTT Kak Jepri
const char* MQTT_PASS = "password_jepri";

#define PINTU_PIN  13
#define RELAY_PIN  26
#define RELAY_ON   LOW       // kebanyakan modul relay aktif LOW
#define RELAY_OFF  HIGH
#define LANGKAH_GORDEN 4096  // 2 putaran, sesuaikan dengan panjang gorden

Stepper gorden(2048, 19, 5, 18, 4);          // urutan IN1, IN3, IN2, IN4
HardwareSerial dfSerial(2);
DFRobotDFPlayerMini speaker;
WiFiClient net;
PubSubClient mqtt(net);

bool gordenTerbuka = false;
int pintuTerakhir = -1;

void gerakGorden(bool buka) {
  if (buka == gordenTerbuka) return;
  gorden.step(buka ? LANGKAH_GORDEN : -LANGKAH_GORDEN);
  gordenTerbuka = buka;
}

void terimaAksi(char* topic, byte* payload, unsigned int len) {
  JsonDocument doc;
  if (deserializeJson(doc, payload, len)) return;
  digitalWrite(RELAY_PIN, doc["lampu"] == 1 ? RELAY_ON : RELAY_OFF);
  int suara = doc["suara"] | 0;
  if (suara > 0) speaker.playMp3Folder(suara);
  gerakGorden(doc["gorden"] == "BUKA");
}

void sambung() {
  while (!mqtt.connected()) {
    if (mqtt.connect("esp32-jepri", MQTT_USER, MQTT_PASS)) {
      mqtt.subscribe("desa/jepri/aksi");
    } else {
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PINTU_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF);
  gorden.setSpeed(12);

  dfSerial.begin(9600, SERIAL_8N1, 16, 17);  // RX=16, TX=17
  if (speaker.begin(dfSerial)) speaker.volume(25);
  else Serial.println("DFPlayer tidak terbaca, cek kabel & microSD");

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqtt.setServer(MQTT_HOST, 1883);
  mqtt.setKeepAlive(60);                     // gorden bisa bergerak beberapa detik
  mqtt.setCallback(terimaAksi);
}

void loop() {
  if (!mqtt.connected()) sambung();
  mqtt.loop();

  int pintu = digitalRead(PINTU_PIN);        // LOW = tertutup (magnet dekat), HIGH = terbuka
  if (pintu != pintuTerakhir) {
    delay(50);                               // anti-getar
    if (digitalRead(PINTU_PIN) == pintu) {
      pintuTerakhir = pintu;
      mqtt.publish("desa/jepri/pintu", pintu == HIGH ? "BUKA" : "TUTUP");
    }
  }
}
