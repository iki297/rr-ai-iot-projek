# Prediksi Hujan Kak Sanmey - SARIMA (server Pak Kades)
# Dijalankan tiap jam lewat crontab:
#   5 * * * * python3 /home/pakkades/sarima_hujan.py
import sqlite3, json
import pandas as pd
import paho.mqtt.publish as publish
from statsmodels.tsa.statespace.sarimax import SARIMAX

DB = "/home/pakkades/desa.db"
AUTH = {"username": "pakkades", "password": "rahasia"}

# 1. Ambil data tekanan & kelembapan 14 hari terakhir
con = sqlite3.connect(DB)
q = ("SELECT waktu, tekanan, lembap FROM cuaca_sanmey "
     "WHERE waktu >= datetime('now', '-14 days')")
df = pd.read_sql(q, con, parse_dates=["waktu"],
                 index_col="waktu")
data = df.resample("1h").mean().interpolate()

# 2. Latih SARIMA dengan pola harian (musim 24 jam)
model = SARIMAX(data["tekanan"], order=(1, 0, 1),
                seasonal_order=(1, 1, 1, 24))
hasil = model.fit(disp=False, maxiter=200)

# 3. Ramal tekanan udara 3 jam ke depan
ramalan = hasil.forecast(steps=3)
# bandingkan dengan jam yang sama kemarin (pola normal)
normal = data["tekanan"].iloc[-24:-21].values
selisih = float((ramalan.values - normal).mean())   # hPa
lembap = float(data["lembap"].iloc[-1])

# 4. Tentukan status, kirim ke Node-RED lewat MQTT
hujan = selisih < -1.0 and lembap > 85
pesan = {"ramalan": [round(v, 1) for v in ramalan],
         "selisih": round(selisih, 2),
         "lembap": round(lembap, 1),
         "status": "HUJAN" if hujan else "AMAN"}
publish.single("desa/sanmey/prediksi", json.dumps(pesan),
               hostname="localhost", auth=AUTH)
print(pesan)
