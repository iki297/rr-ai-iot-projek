# Permintaan Warga: Pompa Hidram + Keran Otomatis (Kak Sura)

Pompa hidram menaikkan air sungai ke tangki kebun tanpa listrik. ESP32 bertenaga surya membaca kelembapan tanah dan membuka/menutup keran tangki.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, serta alamat server.

## File
- `keran_kebun_sura.ino`
- `aturan_keran.js`

## Bahan
- Pompa hidram (pipa masuk, katup buang, katup hantar, tabung udara, pipa keluar)
- ESP32
- Sensor kelembapan tanah kapasitif
- Motorized ball valve 12V (2 kabel, balik polaritas)
- Driver L298N
- Panel surya 12V + solar charge controller + aki 12V + LM2596

## Wiring
- Sensor tanah AOUT > GPIO 34, VCC > 3V3
- L298N IN1 > GPIO 26, IN2 > GPIO 27, OUT1/OUT2 > valve
- Aki 12V > L298N, aki 12V > LM2596 (5V) > VIN ESP32

## Library
- PubSubClient

## Catatan tambahan
- Pompa hidram butuh beda tinggi air minimal sekitar 1 meter. Sebagian air kembali ke sungai lewat katup buang.
- Kalibrasi NILAI_KERING dan NILAI_BASAH sensor tanah.
- Kebun jauh dari Wi-Fi desa? Pakai repeater atau LoRa.
- `aturan_keran.js` ditempel di function node Node-RED.
