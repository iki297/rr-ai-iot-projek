# Kotak Paket Pintar (Sanmey)

Reed switch di bingkai pintu atas mendeteksi paket masuk, lalu ESP32 mengirim notifikasi Telegram lengkap dengan jam. Desain kotak: pintu atas + pembatas bentuk L.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, token bot, serta alamat server.

## File
- `kotak_paket.ino`
- `desain/desain_kotak_v3.png`
- `desain/mekanisme_pembatas.png`

## Bahan
- ESP32
- Reed switch + magnet
- Bot Telegram (BotFather)

## Wiring
- Reed switch > GPIO 27 dan GND (pull-up internal)

## Library
- UniversalTelegramBot

## Catatan tambahan
- Jam memakai WIB (UTC+7); ganti offset untuk WITA/WIT.
