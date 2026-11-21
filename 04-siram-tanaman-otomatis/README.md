# Siram Tanaman Otomatis + Telegram (Rizky)

Pompa menyiram tiap pagi, bisa diperintah lewat Telegram ("siram", "cek").

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, token bot, serta alamat server.

## File
- `siram_tanaman.ino`

## Bahan
- ESP32
- Sensor kelembapan tanah
- Modul relay
- Pompa air mini
- Bot Telegram (BotFather)

## Wiring
- Sensor AO > GPIO 34
- Relay pompa > GPIO 26 (aktif LOW)

## Library
- UniversalTelegramBot

## Catatan tambahan
- Kalibrasi nilai KERING dan BASAH sesuai sensormu.
