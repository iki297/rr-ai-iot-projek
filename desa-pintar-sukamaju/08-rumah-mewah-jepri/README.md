# Permintaan Warga: Rumah Mewah Serba Otomatis (Kak Jepri)

Begitu pintu dibuka, mode sambutan berjalan: lampu menyala, gorden terbuka, dan speaker menyapa. Ada juga mode tidur dan mode pergi.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, serta alamat server.

## File
- `rumah_sultan_jepri.ino`
- `mode_rumah.js`

## Bahan
- ESP32
- Sensor pintu MC-38
- Modul relay + lampu
- Motor stepper 28BYJ-48 + driver ULN2003 (gorden)
- DFPlayer Mini + speaker 3W + kartu microSD

## Wiring
- MC-38 > GPIO 13 dan GND (INPUT_PULLUP)
- Relay IN > GPIO 26
- ULN2003 IN1-IN4 > GPIO 19, 18, 5, 4 (motor pakai adaptor 5V terpisah)
- DFPlayer RX < GPIO 17 lewat resistor 1K, TX > GPIO 16

## Library
- PubSubClient
- ArduinoJson (v7)
- DFRobotDFPlayerMini
- Stepper (bawaan Arduino)

## Catatan tambahan
- microSD: `/mp3/0001.mp3` sapaan, `/mp3/0002.mp3` alarm.
- `mode_rumah.js` ditempel di function node Node-RED.
- Topic: `desa/jepri/pintu`, `desa/jepri/mode`, `desa/jepri/aksi`
- Hati-hati listrik 220V.
