# Seri Sistem IoT Kebun (3 part)

Part 1: sensor tanah, suhu, kelembapan ke dashboard. Part 2: simpan data ke SQLite. Part 3: tenaga surya + deep sleep.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, token bot, serta alamat server.

## File
- `part1-sensor/kebun_sensor.ino`
- `part2-database/flow_kebun_database.json`
- `part3-tenaga-surya/kebun_surya.ino`

## Bahan
- ESP32
- Capacitive Soil Moisture Sensor v1.2
- DHT22
- Panel surya ~9V + PWM solar charge controller 6V 5A + aki kering 6V
- Resistor 100k dan 47k (pembagi tegangan aki)

## Wiring
- Sensor tanah AOUT > GPIO 34
- DHT22 data > GPIO 4
- Tegangan aki lewat pembagi 100k:47k > GPIO 33
- Beban controller > VIN ESP32
- Topik MQTT: kebun/tanah, kebun/suhu, kebun/kelembapan, kebun/aki

## Library
- PubSubClient
- DHT sensor library (Adafruit)
- Node-RED: node-red-node-sqlite, @flowfuse/node-red-dashboard

## Catatan tambahan
- Cek jenis aki yang didukung solar charge controller.
