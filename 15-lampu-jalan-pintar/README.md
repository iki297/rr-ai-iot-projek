# Lampu Jalan Pintar (Rizky)

Lampu jalan versi mini: malam hari menyala redup 20%, langsung terang 100% saat ada orang atau motor lewat, lalu kembali redup setelah 30 detik tanpa gerakan. Siang hari lampu mati.

> **Catatan:** kode ini belum diuji di alat asli. Uji dulu sebelum dipakai.

## File
- `lampu_jalan_pintar.ino`

## Bahan
- ESP32
- Modul sensor cahaya LDR (keluaran AO)
- Sensor radar gelombang mikro RCWL-0516
- MOSFET logic-level IRLZ44N + resistor 10k (pull-down gate)
- Lampu LED 12V
- Adaptor 12V + modul step-down 12V ke 5V

## Wiring
- Sensor cahaya: VCC > 3V3, GND > GND, AO > GPIO 34
- RCWL-0516: VIN > 5V, GND > GND, OUT > GPIO 27
- MOSFET: gate > GPIO 26 (+ 10k ke GND), source > GND, drain > kabel minus lampu
- Lampu LED: plus > 12V
- Step-down: 5V > VIN ESP32. Semua GND disatukan.

## Library
- Tidak perlu library tambahan. Pakai board ESP32 versi 3.x (fungsi `ledcAttach`).

## Catatan tambahan
- Cek nilai LDR di Serial Monitor lalu atur `BATAS_GELAP`.
- Terang redup dan lama tahan bisa diubah di `REDUP`, `TERANG`, dan `TAHAN_MS`.
- Ini versi mini 12V. Lampu jalan 220V butuh driver LED yang bisa di-dimming dan pemasangan oleh teknisi.
