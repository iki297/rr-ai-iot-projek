# Dari Sensor ke IoT dalam 3 Langkah (Rizky)

ESP32 + sensor suhu DHT22 → tambah LCD 16x2 I2C → sambung ke WiFi supaya suhu bisa dilihat dari HP (IoT dengan jaringan lokal).

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi dan password.

## File
- `langkah1_sensor/langkah1_sensor.ino`: ESP32 + DHT22, hasil di Serial Monitor
- `langkah2_lcd/langkah2_lcd.ino`: + LCD 16x2 I2C, suhu tampil di layar
- `langkah3_wifi/langkah3_wifi.ino`: + WiFi, suhu dibuka dari browser HP

## Bahan
- ESP32 DevKit V1 (30 pin)
- DHT22 (modul 3 pin)
- LCD 16x2 + modul I2C (PCF8574, alamat 0x27 atau 0x3F)
- Kabel jumper

## Wiring
- DHT22 DATA > GPIO 4, VCC > 3V3, GND > GND
- LCD I2C VCC > VIN (5V), GND > GND, SDA > GPIO 21, SCL > GPIO 22

## Library
- DHT sensor library (Adafruit) + Adafruit Unified Sensor
- LiquidCrystal I2C
- WiFi dan WebServer sudah bawaan board ESP32

## Cara pakai langkah 3
1. Isi `ssid` dan `password` WiFi rumah, lalu upload.
2. Alamat IP muncul di LCD dan Serial Monitor (contoh `192.168.1.50`).
3. Buka alamat itu di browser HP. HP dan ESP32 harus terhubung ke WiFi yang sama.

## Catatan tambahan
- Kalau LCD menyala tapi kosong, putar potensiometer biru di belakang modul I2C (kontras), atau ganti alamat ke 0x3F.
- Karena pakai jaringan lokal, suhu hanya bisa dilihat dari HP yang ada di WiFi yang sama.
