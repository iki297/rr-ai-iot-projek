# Monitoring Gas LPG + Telegram (Sanmey)

Sensor gas di dekat tabung, nilai dikirim ke Node-RED lewat MQTT, peringatan ke Telegram kalau lewat batas.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, token bot, serta alamat server.

## File
- `monitor_gas.ino`

## Bahan
- ESP32
- Sensor gas MQ-6
- Server Node-RED + MQTT Broker
- Bot Telegram (BotFather)

## Wiring
- MQ-6 VCC > VIN 5V
- MQ-6 AO > GPIO 34 lewat pembagi tegangan 2:1
- Topik MQTT: rr/gas

## Library
- PubSubClient
- Node-RED: node-red-contrib-telegrambot

## Catatan tambahan
- Alat ini hanya membantu memberi peringatan; tetap rutin cek selang dan regulator.
