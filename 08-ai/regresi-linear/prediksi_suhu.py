# Prediksi suhu 1 jam ke depan dengan regresi linear
# Data: suhu.csv hasil simpanan Node-RED (kolom: waktu,suhu)
import pandas as pd
from sklearn.linear_model import LinearRegression

data = pd.read_csv("suhu.csv", parse_dates=["waktu"])
data = data.tail(6)                      # pakai 6 jam terakhir

# x = jam ke-0, 1, 2, ...   y = suhu
jam = (data["waktu"] - data["waktu"].iloc[0]).dt.total_seconds() / 3600
x = jam.to_frame("jam")
y = data["suhu"]

model = LinearRegression()
model.fit(x, y)                          # cari garis paling pas

a = model.coef_[0]                       # kemiringan (derajat per jam)
b = model.intercept_                     # titik awal
print(f"Garis: suhu = {a:.2f} x jam + {b:.2f}")

jam_depan = pd.DataFrame({"jam": [jam.iloc[-1] + 1]})
prediksi = model.predict(jam_depan)[0]   # perpanjang garis 1 jam
print(f"Prediksi suhu 1 jam lagi: {prediksi:.1f} C")
