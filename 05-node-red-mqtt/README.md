# Seri Node-RED & MQTT (3 part)

Part 1: install Node-RED dan Mosquitto di VPS Ubuntu (lihat videonya). Part 2: ESP32 kirim suhu dan kelembapan ke dashboard. Part 3: kontrol lampu dari dashboard.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, token bot, serta alamat server.

## File
- `part2-monitor-suhu/monitor_suhu.ino`
- `part3-lampu-dashboard/lampu_dashboard.ino`

## Bahan
- VPS Ubuntu (Node-RED + Mosquitto)
- ESP32
- Sensor DHT22
- Modul relay + lampu

## Wiring
- DHT22 data > GPIO 4
- Relay IN > GPIO 26 (aktif LOW)
- Topik MQTT: rr/suhu, rr/kelembapan, rr/lampu

## Library
- PubSubClient
- DHT sensor library (Adafruit)
- Node-RED: @flowfuse/node-red-dashboard

## Catatan tambahan
- Hati-hati listrik 220V pada relay.
