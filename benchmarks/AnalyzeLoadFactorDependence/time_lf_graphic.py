import json
import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import UnivariateSpline

N = 22724

with open("data2.json") as f:
    data = json.load(f)

results = data["results"]

x, y, errors = [], [], []

for r in results:
    size = int(r["parameters"]["size"])
    load_factor = N / size

    x.append(load_factor)
    y.append(r["mean"])
    errors.append(r["stddev"])

x, y, errors = zip(*sorted(zip(x, y, errors)))

x = np.array(x)
y = np.array(y)
errors = np.array(errors)

logX = np.log(x)
spline = UnivariateSpline(logX, y, s=0.2)

logX_smooth = np.linspace(logX.min(), logX.max(), 400)
x_smooth = np.exp(logX_smooth)
y_smooth = spline(logX_smooth)

best_idx = np.argmin(y)
best_x = x[best_idx]
best_y = y[best_idx]

plt.figure()

plt.plot(x_smooth, y_smooth)

plt.errorbar(
    x, y,
    yerr=errors,
    fmt='o',
    capsize=4,
)

plt.scatter(best_x, best_y, zorder=5)
plt.axvline(
    x=best_x,
    linestyle="--",
    label=f"Оптимальное значение LF ≈ {best_x:.2f}"
)

plt.axvspan(best_x * 0.8, best_x * 1.2, alpha=0.15)

plt.xscale("log")

plt.xlabel("Load factor")
plt.ylabel("Время (сек)")
plt.title("Производительность от load factor")

plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.legend()

plt.savefig("t_vs_load_factor_semilog.png", dpi=300)
plt.show()