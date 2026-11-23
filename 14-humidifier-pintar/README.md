# Humidifier Pintar ESP32 (Sanmey)

Membedah cara kerja humidifier (tangki, piringan piezo, papan driver, kipas, cerobong, pelampung), lalu membuat versi pintarnya: DHT22 mengukur kelembapan, ESP32 menyalakan modul kabut lewat MOSFET. Kabut menyala di bawah 45% dan mati di 60%.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai.

## File
- `humidifier_pintar.ino`

## Bahan
- ESP32
- Sensor DHT22
- Modul kabut ultrasonik 5V (USB, sekitar 108 kHz) + sumbu kapas + gelas air
- MOSFET logic-level (IRLZ44N atau AO3400) + resistor 100k
- Adaptor 5V 2A

## Wiring
- DHT22: VCC > 3V3, GND > GND, data > GPIO 4
- MOSFET gate > GPIO 26, resistor 100k dari gate ke GND
- MOSFET source > GND (GND adaptor disatukan dengan GND ESP32)
- MOSFET drain > kabel minus (-) modul kabut
- Plus (+) modul kabut > 5V adaptor

## Library
- DHT sensor library (Adafruit)

## Catatan tambahan
- Pilih modul kabut yang langsung mengeluarkan kabut begitu dapat listrik (tanpa tombol sentuh).
- Taruh DHT22 agak jauh dari kabut, supaya yang diukur udara ruangan.
- Batas 45% dan 60% bisa diubah di konstanta NYALA dan MATI.
