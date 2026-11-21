# Lampu Teras Otomatis (Rizky)

Lampu teras menyala hanya kalau gelap DAN ada orang, lalu mati setelah 1 menit tanpa gerakan.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, token bot, serta alamat server.

## File
- `lampu_teras.ino`

## Bahan
- ESP32
- Modul sensor cahaya LDR
- Sensor gerak PIR HC-SR501
- Modul relay + lampu teras

## Wiring
- LDR AO > GPIO 34
- PIR OUT > GPIO 27 (VCC ke VIN 5V)
- Relay > GPIO 26

## Library
- Tidak perlu library tambahan

## Catatan tambahan
- Cek nilai LDR di Serial Monitor lalu atur BATAS_GELAP.
- Putar potensiometer waktu PIR ke paling pendek.
- Hati-hati listrik 220V.
