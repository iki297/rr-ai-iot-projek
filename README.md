# RR – AI dan IoT Projek

Kumpulan kode dari video pendek **RR – AI dan IoT Projek** (Instagram Reels, TikTok, YouTube Shorts) oleh Rizky Rahmatullah.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, token bot, serta alamat server.

## Daftar proyek

| Folder | Proyek |
|---|---|
| [01-lampu-via-hp](01-lampu-via-hp/) | Lampu via HP (Rizky) |
| [02-kipas-via-hp](02-kipas-via-hp/) | Kipas via HP (Sanmey) |
| [03-jemuran-anti-hujan](03-jemuran-anti-hujan/) | Jemuran Anti Hujan + Telegram (Sanmey) |
| [04-siram-tanaman-otomatis](04-siram-tanaman-otomatis/) | Siram Tanaman Otomatis + Telegram (Rizky) |
| [05-node-red-mqtt](05-node-red-mqtt/) | Seri Node-RED & MQTT (3 part) |
| [06-monitoring-gas-lpg](06-monitoring-gas-lpg/) | Monitoring Gas LPG + Telegram (Sanmey) |
| [07-kebun-iot](07-kebun-iot/) | Seri Sistem IoT Kebun (3 part) |
| [08-ai](08-ai/) | AI: Regresi Linear dan Prediksi Hujan |
| [09-tandon-air-otomatis](09-tandon-air-otomatis/) | Tandon Air Otomatis (Sanmey) |
| [10-kotak-paket-pintar](10-kotak-paket-pintar/) | Kotak Paket Pintar (Sanmey) |
| [11-lampu-teras-otomatis](11-lampu-teras-otomatis/) | Lampu Teras Otomatis (Rizky) |
| [12-pemantau-listrik](12-pemantau-listrik/) | Pemantau Listrik Rumah (Rizky) |
| [13-sensor-suhu-ke-iot](13-sensor-suhu-ke-iot/) | Dari Sensor ke IoT dalam 3 Langkah (Rizky) |
| [14-humidifier-pintar](14-humidifier-pintar/) | Humidifier Pintar ESP32 (Sanmey) |

### Seri Desa Pintar Sukamaju

Semua proyek seri Desa Pintar ada di folder [desa-pintar-sukamaju](desa-pintar-sukamaju/).

## Cara pakai
- File `.ino`: buka di Arduino IDE, pilih board ESP32, install library yang disebut di README folder, isi WiFi/password/token, lalu upload.
- File `.json`: flow Node-RED, impor lewat menu Import di Node-RED.
- File `.py`: jalankan dengan Python 3 (butuh pandas dan scikit-learn; proyek prediksi hujan Kak Sanmey butuh statsmodels dan paho-mqtt).
- File `.js` (seri Desa Pintar): tempel di function node Node-RED.

Ada pertanyaan atau ide proyek? Komen di videonya!
