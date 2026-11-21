# Desa Pintar #3: Sensor Peringatan Dini Banjir

Mengukur tinggi air sungai, menyalakan lampu indikator dan sirene, lalu mengirim peringatan lewat MQTT.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, serta alamat server.

## File
- `sensor_banjir.ino`

## Bahan
- ESP32
- Sensor jarak tahan air JSN-SR04T
- LED hijau, kuning, merah
- Modul relay + sirene

## Wiring
- JSN-SR04T TRIG > GPIO 5, ECHO > GPIO 18 (lewat pembagi tegangan 1K/2K)
- LED hijau > GPIO 25, kuning > GPIO 26, merah > GPIO 27
- Relay sirene > GPIO 23 (aktif LOW)

## Library
- PubSubClient

## Catatan tambahan
- Topic MQTT: `desa/banjir`
- Ukur jarak sensor ke dasar sungai lalu isi JARAK_DASAR.
