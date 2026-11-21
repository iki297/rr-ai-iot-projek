// Mode rumah Kak Jepri (function node)
let mode = flow.get("mode") || "SAMBUTAN";
if (msg.topic === "desa/jepri/mode") {      // tombol di HP
    mode = msg.payload;
    flow.set("mode", mode);
}
const buka = msg.payload === "BUKA";        // dari sensor pintu
let aksi = null;
if (mode === "SAMBUTAN" && buka) aksi = { lampu: 1, gorden: "BUKA", suara: 1 };
if (mode === "TIDUR") aksi = { lampu: 0, gorden: "TUTUP", suara: 0 };
if (mode === "PERGI") aksi = { lampu: 0, gorden: "TUTUP", suara: buka ? 2 : 0 };
if (!aksi) return null;
msg.topic = "desa/jepri/aksi";
msg.payload = aksi;
return msg;
