# Jemuran Anti Hujan + Telegram (Sanmey)

Atap jemuran menutup sendiri saat sensor hujan basah, lalu mengirim notifikasi Telegram.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, token bot, serta alamat server.

## File
- `jemuran_anti_hujan.ino`

## Bahan
- ESP32
- Sensor hujan (FC-37/YL-83)
- Motor DC + driver L298N
- Limit switch
- Bot Telegram (BotFather)

## Wiring
- Lihat konstanta pin di bagian atas kode

## Library
- UniversalTelegramBot

## Catatan tambahan
- Bot Telegram dibuat dulu lewat @BotFather.
