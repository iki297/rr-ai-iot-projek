# Permintaan Warga: Prediksi Hujan (Kak Sanmey)

Sensor cuaca di rumah Kak Sanmey mengirim data ke server. Skrip Python dengan model SARIMA meramal tekanan udara 3 jam ke depan, lalu memberi peringatan hujan lewat MQTT.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, serta alamat server.

## File
- `sensor_cuaca_sanmey.ino`
- `sarima_hujan.py`

## Bahan
- ESP32
- Sensor BME280 (tekanan, kelembapan, suhu)
- Sensor hujan FC-37 / YL-83
- Panel surya 6V + CN3791 + baterai 18650

## Wiring
- BME280 SDA > GPIO 21, SCL > GPIO 22, VCC > 3V3
- Sensor hujan VCC > GPIO 25 (dinyalakan hanya saat membaca), AO > GPIO 34

## Library
- PubSubClient, Adafruit BME280 (ESP32)
- Python: pandas, statsmodels, paho-mqtt (server)

## Catatan tambahan
- Jalankan `sarima_hujan.py` tiap jam lewat crontab: `5 * * * * python3 /home/pakkades/sarima_hujan.py`
- Butuh data minimal sekitar seminggu sebelum ramalan bisa dipercaya.
- Topic: `desa/sanmey/cuaca` dan `desa/sanmey/prediksi`
