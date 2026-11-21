# Permintaan Warga: Robot Pembersih Rumah (Kak Aca)

Robot dua roda dengan kipas penyedot. Kalau ada tembok atau kursi, robot berhenti, mundur, lalu belok. Jadwal bersih-bersih diatur dari Node-RED.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, serta alamat server.

## File
- `robot_aca.ino`

## Bahan
- ESP32
- Driver motor L298N + 2 motor TT dengan roda
- Sensor jarak HC-SR04
- Kipas penyedot + MOSFET IRLZ44N + dioda 1N4007
- Baterai 2x18650

## Wiring
- L298N ENA > GPIO 14, IN1 > GPIO 25, IN2 > GPIO 26
- L298N ENB > GPIO 32, IN3 > GPIO 27, IN4 > GPIO 33
- HC-SR04 TRIG > GPIO 5, ECHO > GPIO 18 (lewat pembagi tegangan 1K/2K)
- Gate MOSFET kipas > GPIO 4
- L298N 5V > VIN ESP32 dan VCC HC-SR04

## Library
- PubSubClient
- Board ESP32 core 3.x (memakai `ledcAttach`)

## Catatan tambahan
- Di Node-RED: inject node jam 09:00 dan tombol dashboard yang mengirim `MULAI` ke `desa/aca/robot`.
- Status robot dikirim ke `desa/aca/status`.
