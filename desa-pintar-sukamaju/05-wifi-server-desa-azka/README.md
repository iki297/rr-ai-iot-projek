# Permintaan Warga: Wi-Fi Gratis & Server Desa (Kak Azka)

Menyiapkan server desa di rumah Pak Kades: broker MQTT Mosquitto dengan akun per warga, plus Node-RED.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, serta alamat server.

## File
- `server_desa.txt`

## Bahan
- Raspberry Pi / mini PC (server desa)
- Router + titik Wi-Fi gratis (pos ronda, balai desa, rumah Kak Azka)

## Catatan tambahan
- Setiap warga punya akun MQTT sendiri dan hanya bisa menulis ke topic `desa/<nama>/#`.
- Akun `pakkades` bisa membaca semua topic `desa/#`.
