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

### Seri Desa Pintar Sukamaju

| Folder | Proyek |
|---|---|
| [13-desa-stasiun-udara](13-desa-stasiun-udara/) | Desa Pintar #1: Stasiun Pemantau Udara |
| [14-desa-lampu-jalan-otomatis](14-desa-lampu-jalan-otomatis/) | Desa Pintar #2: Lampu Jalan Otomatis |
| [15-desa-sensor-banjir](15-desa-sensor-banjir/) | Desa Pintar #3: Sensor Peringatan Dini Banjir |
| [16-desa-rumah-pintar](16-desa-rumah-pintar/) | Desa Pintar #4: Rumah Pintar |
| [17-desa-wifi-server-azka](17-desa-wifi-server-azka/) | Wi-Fi Gratis & Server Desa (Kak Azka) |
| [18-desa-prediksi-hujan-sanmey](18-desa-prediksi-hujan-sanmey/) | Prediksi Hujan (Kak Sanmey) |
| [19-desa-pendingin-ruangan-rido](19-desa-pendingin-ruangan-rido/) | Pendingin Ruangan Otomatis (Kak Rido) |
| [20-desa-rumah-mewah-jepri](20-desa-rumah-mewah-jepri/) | Rumah Mewah Serba Otomatis (Kak Jepri) |
| [21-desa-robot-pembersih-aca](21-desa-robot-pembersih-aca/) | Robot Pembersih Rumah (Kak Aca) |
| [22-desa-pompa-hidram-sura](22-desa-pompa-hidram-sura/) | Pompa Hidram + Keran Otomatis (Kak Sura) |

## Cara pakai
- File `.ino`: buka di Arduino IDE, pilih board ESP32, install library yang disebut di README folder, isi WiFi/password/token, lalu upload.
- File `.json`: flow Node-RED, impor lewat menu Import di Node-RED.
- File `.py`: jalankan dengan Python 3 (butuh pandas dan scikit-learn; proyek prediksi hujan Kak Sanmey butuh statsmodels dan paho-mqtt).
- File `.js` (seri Desa Pintar): tempel di function node Node-RED.

Ada pertanyaan atau ide proyek? Komen di videonya!
