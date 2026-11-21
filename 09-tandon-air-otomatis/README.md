# Tandon Air Otomatis (Sanmey)

Sensor ultrasonik di tutup tandon mengukur tinggi air; pompa nyala di bawah 20% dan mati di 90%, dengan notifikasi Telegram.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, token bot, serta alamat server.

## File
- `tandon_otomatis.ino`

## Bahan
- ESP32
- Sensor ultrasonik JSN-SR04T (waterproof)
- Modul relay + pompa
- Resistor 1k dan 2k
- Bot Telegram (BotFather)

## Wiring
- VCC > VIN 5V, GND > GND
- Trig > GPIO 5
- Echo > GPIO 18 lewat pembagi 1k/2k
- Relay > GPIO 26
- Sensor dipasang minimal 25 cm di atas batas air penuh

## Library
- UniversalTelegramBot

## Catatan tambahan
- Sesuaikan KOSONG dan PENUH dengan ukuran tandon.
- Banyak relay aktif LOW: tukar HIGH/LOW kalau terbalik.
- Hati-hati listrik 220V.
