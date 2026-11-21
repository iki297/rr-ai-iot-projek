# Prediksi hujan 1 jam ke depan dengan pohon keputusan
# Data: hujan.csv (kolom: suhu, kelembapan, hujan_1jam)
import pandas as pd
from sklearn.tree import DecisionTreeClassifier, export_text

data = pd.read_csv("hujan.csv")
x = data[["suhu", "kelembapan"]]
y = data["hujan_1jam"]                   # "ya" atau "tidak"

pohon = DecisionTreeClassifier(max_depth=2, random_state=0)
pohon.fit(x, y)                          # susun pertanyaan ya/tidak

print(export_text(pohon, feature_names=["suhu", "kelembapan"]))

sekarang = pd.DataFrame({"suhu": [25.8], "kelembapan": [88]})
hasil = pohon.predict(sekarang)[0]
print(f"Suhu 25.8 C, lembap 88% -> hujan 1 jam lagi? {hasil}")
