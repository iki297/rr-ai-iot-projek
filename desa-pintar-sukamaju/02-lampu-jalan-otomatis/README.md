# Desa Pintar #2: Lampu Jalan Otomatis

Lampu jalan menyala redup saat gelap, terang saat ada kendaraan lewat, dan menghitung jumlah kendaraan.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, serta alamat server.

## File
- `lampu_jalan_otomatis.ino`

## Bahan
- ESP32
- Modul sensor cahaya LDR
- Sensor gerak radar RCWL-0516
- LED 12V + MOSFET
- Panel surya + solar charge controller + aki

## Wiring
- LDR AO > GPIO 34
- RCWL-0516 OUT > GPIO 27
- Gate MOSFET > GPIO 25 (lewat resistor 220 ohm)

## Library
- PubSubClient

## Catatan tambahan
- Topic MQTT: `desa/lampu`
- Cek nilai LDR di Serial Monitor lalu atur BATAS_GELAP.
