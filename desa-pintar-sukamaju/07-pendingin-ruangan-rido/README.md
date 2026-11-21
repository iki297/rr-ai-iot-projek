# Permintaan Warga: Pendingin Ruangan Otomatis (Kak Rido)

Kipas angin menyala otomatis saat kamar panas dan ada orang, lalu mati setelah kamar kosong 15 menit.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, serta alamat server.

## File
- `kipas_rido.ino`
- `aturan_kipas.js`

## Bahan
- ESP32
- Sensor suhu & kelembapan DHT22
- Sensor gerak PIR HC-SR501
- Modul relay 5V + kipas angin

## Wiring
- DHT22 DATA > GPIO 27
- PIR OUT > GPIO 14 (VCC ke 5V)
- Relay IN > GPIO 26 (VCC ke 5V), kabel kipas lewat COM dan NO

## Library
- PubSubClient
- DHT sensor library (Adafruit)

## Catatan tambahan
- `aturan_kipas.js` ditempel di function node Node-RED.
- Topic: `desa/rido/kamar` dan `desa/rido/kipas`
- Hati-hati listrik 220V.
