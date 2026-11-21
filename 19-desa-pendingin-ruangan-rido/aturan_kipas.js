// Aturan kipas Kak Rido (function node)
const d = msg.payload;              // {suhu, lembap, gerak}
const batas = flow.get("batas") || 29;
let kosong = flow.get("kosong") || 0;
kosong = d.gerak ? 0 : kosong + 1;  // data tiap 1 menit
flow.set("kosong", kosong);
let kipas = flow.get("kipas") || "OFF";
if (d.suhu > batas && d.gerak) kipas = "ON";
if (kosong >= 15) kipas = "OFF";    // kosong 15 menit
flow.set("kipas", kipas);
msg.topic = "desa/rido/kipas";
msg.payload = kipas;
return msg;
