// Aturan keran kebun Kak Sura (function node)
const d = msg.payload;              // {"tanah": 35}  (% kelembapan)
let keran = flow.get("keran") || "TUTUP";
if (d.tanah < 40) keran = "BUKA";   // tanah kering
if (d.tanah > 60) keran = "TUTUP";  // sudah cukup basah
flow.set("keran", keran);
msg.topic = "desa/sura/keran";
msg.payload = keran;
return msg;
