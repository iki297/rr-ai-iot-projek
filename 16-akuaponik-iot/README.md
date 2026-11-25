# Akuaponik IoT (Rizky)

Akuaponik = hidroponik + akuarium. Kotoran ikan (amonia) diubah bakteri baik menjadi nitrat, nitrat diserap akar sayur, lalu air bersih kembali ke akuarium. ESP32 memantau suhu dan pH air, menyalakan pompa sesuai jadwal, dan mengirim notifikasi Telegram kalau ada yang tidak normal.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai, dan isi sendiri nama WiFi, password, token bot, serta chat ID.

## File
- `akuaponik_iot.ino`

## Bahan
- ESP32
- Sensor suhu tahan air DS18B20 + resistor 4.7k
- Modul sensor pH (misalnya PH-4502C) + resistor 10k dan 20k (pembagi tegangan)
- Modul relay + pompa air celup
- Akuarium, rak/talang hidroponik, pipa
- Bot Telegram (buat lewat @BotFather)

## Wiring
- DS18B20: merah > 3V3, hitam > GND, kuning (data) > GPIO 4, resistor 4.7k dari data ke 3V3
- Modul pH: V+ > 5V, G > GND, PO > pembagi 10k/20k > GPIO 35
- Relay: IN > GPIO 26, VCC > 5V, GND > GND, pompa lewat kontak relay

## Library
- UniversalTelegramBot (dan ArduinoJson)
- OneWire
- DallasTemperature

## Catatan tambahan
- Kalibrasi sensor pH dengan larutan buffer pH 7 dan pH 4, lalu isi `V_PH7` dan `V_PH4`.
- Jadwal pompa (15 menit nyala, 45 menit mati) bisa diubah di `NYALA_MS` dan `JEDA_MS`.
- Batas peringatan: suhu di bawah 22 atau di atas 30 C, pH di bawah 6 atau di atas 8. Sesuaikan dengan jenis ikan dan sayur.
- Sistem baru butuh beberapa minggu sampai bakteri baiknya tumbuh sebelum ikan ditambah banyak.
- Kalau relaymu aktif LOW, tukar HIGH/LOW pada pompa.
