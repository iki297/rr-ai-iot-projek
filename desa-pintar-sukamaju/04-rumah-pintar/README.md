# Desa Pintar #4: Rumah Pintar

Lampu dan kipas dikendalikan dari HP, plus notifikasi saat pintu dibuka.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, serta alamat server.

## File
- `rumah_pintar.ino`

## Bahan
- ESP32
- Modul relay 2 channel
- Sensor pintu MC-38

## Wiring
- Relay lampu IN1 > GPIO 26, relay kipas IN2 > GPIO 27 (aktif LOW)
- MC-38: satu kabel ke GPIO 4, satu kabel ke GND

## Library
- PubSubClient

## Catatan tambahan
- Hati-hati listrik 220V.
