import matplotlib.pyplot as plt
import numpy as np
cellNum = ['0','1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40','41','42','43','44','45','46','47','48','49','50','51','52','53','54','55','56','57','58','59','60','61','62','63','64','65','66','67','68','69','70','71','72','73','74','75','76','77','78','79','80','81','82','83','84','85','86','87','88','89','90','91','92','93','94','95','96','97','98','99']
plt.figure(figsize=(12, 6))
values = [9, 11, 6, 7, 5, 8, 7, 7, 5, 14, 3, 8, 8, 6, 2, 5, 6, 5, 4, 11, 6, 4, 8, 4, 6, 14, 11, 12, 4, 8, 6, 8, 4, 8, 6, 8, 9, 5, 4, 9, 5, 7, 12, 8, 10, 8, 7, 4, 8, 3, 9, 2, 7, 6, 10, 2, 7, 8, 4, 8, 4, 4, 5, 9, 7, 4, 11, 2, 8, 9, 4, 5, 0, 1, 6, 1, 10, 9, 5, 7, 6, 6, 11, 5, 11, 5, 4, 2, 5, 10, 7, 5, 7, 5, 4, 10, 10, 7, 0, 6]
plt.xticks(range(0, len(cellNum), 10))
plt.grid(axis='y', linestyle='--', alpha=0.5)
plt.xlabel('Номер ячейки')
plt.ylabel('Количество элементов')
plt.title("Загрузка хэш-таблицы")
mean = 6.53
std = 2.90
colors = []
for v in values:
	if v > mean + std:
		colors.append('red')
	elif v > mean:
		colors.append('orange')
	else:
		colors.append('green')
plt.bar(cellNum, values, color = colors, alpha=0.8)
stats = (
f"Среднее: 6.53\n"
f"Стандартное отклонение:  2.90\n"
f"Коэф. вариации:   0.44\n"
f"zeros: {values.count(0)}"
)
plt.plot([], [], ' ', label=stats)
plt.legend(loc='best')
plt.axhline(y = 6.53, linewidth = 2.5, linestyle = '--', label=f'Среднее: 6.53')
plt.axhline(y = 9.43, linewidth = 2, linestyle = ':', label=f'+1σ')
plt.axhline(y = 3.63, linestyle = ':', label=f'-1σ')
plt.legend()
plt.tight_layout()
plt.savefig('images/diagrams/gnuHashLoad.png')
