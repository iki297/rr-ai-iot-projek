#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "NAMA_WIFI";
const char* pass = "PASSWORD_WIFI";
const int RELAY = 26;
WebServer server(80);

// "Aplikasi" HP = halaman web dari ESP32
const char HALAMAN[] = R"(
<meta name="viewport" content="width=device-width">
<h1>Lampu Kamar</h1>
<a href="/on"><button>ON</button></a>
<a href="/off"><button>OFF</button></a>
)";

void tampil() { server.send(200, "text/html", HALAMAN); }

void lampuOn() {
  digitalWrite(RELAY, LOW);   // relay aktif LOW
  tampil();
}

void lampuOff() {
  digitalWrite(RELAY, HIGH);
  tampil();
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);  // awal: lampu mati
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println(WiFi.localIP());  // buka IP ini di HP
  server.on("/", tampil);
  server.on("/on", lampuOn);
  server.on("/off", lampuOff);
  server.begin();
}

void loop() { server.handleClient(); }
