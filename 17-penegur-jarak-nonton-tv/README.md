# Penegur Jarak Nonton TV (Rizky)

Sensor jarak ultrasonik di bawah TV mengukur jarak anak ke layar. Kalau anak lebih dekat dari 150 cm selama 3 detik, buzzer berbunyi putus-putus dan LED merah menyala. Begitu anak mundur, buzzer diam sendiri.

Catatan: menurut American Academy of Ophthalmology, nonton terlalu dekat tidak merusak mata, tapi bisa membuat mata capek dan tegang.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai.

## File
- `jarak_nonton_tv.ino`

## Bahan
- ESP32
- Sensor ultrasonik HC-SR04
- Resistor 1k dan 2k (pembagi tegangan Echo)
- Modul buzzer aktif
- LED merah + resistor 220

## Wiring
- HC-SR04: VCC > 5V (VIN), GND > GND, Trig > GPIO 5
- HC-SR04 Echo > pembagi 1k/2k > GPIO 18 (Echo keluar 5V, ESP32 hanya tahan 3.3V)
- Modul buzzer aktif: I/O > GPIO 26, VCC > 3V3, GND > GND
- LED merah: GPIO 27 > resistor 220 > LED > GND

## Library
- Tidak perlu library tambahan.

## Catatan tambahan
- Arahkan sensor ke tempat duduk anak, kira-kira setinggi mata.
- Ubah `BATAS_CM` sesuai ukuran TV, dan `TUNGGU_MS` untuk lama tunggu sebelum menegur.
