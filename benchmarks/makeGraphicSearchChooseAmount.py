import json
import matplotlib.pyplot as plt
import numpy as np 
from scipy.interpolate import UnivariateSpline

with open("findOptimalSearchAmount2.json") as f:
    data = json.load(f)

results = data["results"]

x = []
y = []
errors = []

for r in results:
    n = int(r["parameters"]["searches"]) 
    x.append(n)
    y.append(r["mean"])
    errors.append(r["stddev"])

x, y, errors = zip(*sorted(zip(x, y, errors)))

logX = np.log(x)
logY = np.log(y)

threshold = 0.99
best_index = None

for i in range(len(x) - 5):
    xs = logX[i:]
    ys = logY[i:]
    
    k, b = np.polyfit(xs, ys, 1)
    y_pred = k * xs + b
    
    ss_res = np.sum((ys - y_pred)**2)
    ss_tot = np.sum((ys - np.mean(ys))**2)
    
    if ss_tot == 0:
        continue
    
    r2 = 1 - ss_res / ss_tot
    
    if r2 >= threshold:
        best_index = i
        break

if best_index is not None:
    plt.plot(x[best_index], 0, marker='o', color='red', markersize=5, clip_on=False, transform=plt.gca().get_xaxis_transform(), label = f"{x[best_index]}")

    
    plt.axvline(x = x[best_index], color='r', linestyle='--', label = "Поиск начинает занимать почти все время")
    plt.axvspan(xmin=x[best_index], xmax=max(x), facecolor='green', alpha=0.2)
else:   
    print("Не найдено")


spline = UnivariateSpline(logX, logY, s=0.1)
logX_smooth = np.linspace(logX.min(), logX.max(), 300)
logY_smooth = spline(logX_smooth)

x_smooth = np.exp(logX_smooth)
y_smooth = np.exp(logY_smooth)

# # апроксимация хвоста
# mask = np.array(x) > 1e6 / 2
# x_tail = np.array(x)[mask]
# y_tail = np.array(y)[mask]

# logX = np.log(x_tail)
# logY = np.log(y_tail)

# coef = np.polyfit(logX, logY, 1)

# x_approximated = np.logspace(np.log10(min(x_tail)), np.log10(max(x_tail)), 200)
# y_approximated = np.exp(coef[1]) * x_approximated**coef[0]

plt.plot(x_smooth, y_smooth)
plt.scatter(x, y)
# plt.errorbar(
#     x, y,
#     yerr=errors,
#     marker="o",
#     capsize=5
# )

plt.xscale("log")
plt.yscale("log")   

plt.xlabel("Количество поисков")
plt.ylabel("Время исполнения (секунд)")
plt.title("Время исполнения программы в завсимости от количества поисков")

plt.grid(True, which="both", linestyle="--", linewidth=0.5)

plt.legend()

plt.savefig("t_of_n.png", dpi=300)
