# Pemantau Listrik Rumah (Rizky)

PZEM-004T v3 mengukur tegangan, arus, daya, dan kWh; data ke Node-RED lewat MQTT, peringatan Telegram kalau daya lewat 1000 W.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, token bot, serta alamat server.

## File
- `pemantau_listrik.ino`
- `flow_pemantau_listrik.json`

## Bahan
- ESP32
- PZEM-004T v3 + kumparan CT
- Server Node-RED + MQTT Broker
- Bot Telegram (BotFather)

## Wiring
- PZEM 5V > VIN, GND > GND
- PZEM TX > GPIO 16, RX > GPIO 17
- Kumparan CT hanya di kabel fasa (L)
- Topik MQTT: listrik/tegangan, listrik/arus, listrik/daya, listrik/energi

## Library
- PZEM004Tv30
- PubSubClient
- Node-RED: @flowfuse/node-red-dashboard, node-red-contrib-telegrambot

## Catatan tambahan
- Setelah impor flow: isi alamat broker, token bot, dan CHAT_ID.
- Bagian 220V berbahaya: pemasangan oleh teknisi listrik.
