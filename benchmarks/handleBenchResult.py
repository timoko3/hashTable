import json
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

with open("compareO0andO3.json") as f:
    data = json.load(f)

results = data["results"]

df = pd.DataFrame(results)

cols = ["mean", "stddev", "min", "max"]
df_rounded = df.copy()
df_rounded[cols] = df_rounded[cols].round(2)

print("\n=== Основная таблица ===")
print(df_rounded[["command", "mean", "stddev", "min", "max"]])

fastest = df.loc[df["mean"].idxmin()]
slowest = df.loc[df["mean"].idxmax()]
print("\n=== Самая быстрая версия ===")
print(fastest["command"])

print("\n=== Сравнение (во сколько раз медленнее) ===")
for _, row in df.iterrows():
    ratio = row["mean"] / fastest["mean"]
    print(f"{row['command']} → {ratio:.2f}x")

output_file = "analysis.txt"

with open(output_file, "w") as out:

    out.write("=== Основная таблица ===\n")
    out.write(df_rounded[["command", "mean", "stddev", "min", "max"]].to_string())
    out.write("\n\n")

    out.write("=== Самая быстрая версия ===\n")
    out.write(f"{fastest['command']}\n\n")

    out.write("=== Сравнение ===\n")
    for _, row in df.iterrows():
        ratio = slowest["mean"] / row["mean"]
        out.write(f"{row['command']} → {ratio:.2f}x\n")