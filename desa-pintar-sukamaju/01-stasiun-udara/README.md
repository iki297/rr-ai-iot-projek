# Desa Pintar #1: Stasiun Pemantau Udara

Memantau suhu, kelembapan, dan kualitas udara desa, lalu mengirim datanya ke Node-RED lewat MQTT.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, serta alamat server.

## File
- `stasiun_udara_desa.ino`

## Bahan
- ESP32
- Sensor suhu & kelembapan DHT22
- Sensor kualitas udara MQ-135
- Panel surya + baterai (opsional, untuk dipasang di luar)

## Wiring
- DHT22 DATA > GPIO 4
- MQ-135 AO > GPIO 34 (lewat pembagi tegangan)

## Library
- PubSubClient
- DHT sensor library (Adafruit)

## Catatan tambahan
- Topic MQTT: `desa/udara`
- MQ-135 perlu dipanaskan beberapa menit sebelum nilainya stabil.
