import json
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# === 1. Загружаем JSON ===
with open("benchmarks/compareO2andO3.json") as f:
    data = json.load(f)

results = data["results"]

# === 2. Переводим в DataFrame ===
df = pd.DataFrame(results)

print("\n=== Основная таблица ===")
print(df[["command", "mean", "stddev", "min", "max"]])

# === 3. Кто быстрее ===
fastest = df.loc[df["mean"].idxmin()]
print("\n=== Самая быстрая версия ===")
print(fastest["command"])

# === 4. Сравнение скорости ===
print("\n=== Сравнение (во сколько раз медленнее) ===")
for _, row in df.iterrows():
    ratio = row["mean"] / fastest["mean"]
    print(f"{row['command']} → {ratio:.3f}x")
