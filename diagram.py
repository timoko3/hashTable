import matplotlib.pyplot as plt
import numpy as np
cellNum = ['0','1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40','41','42','43','44','45','46','47','48','49','50','51','52','53','54','55','56','57','58','59','60','61','62','63','64','65','66','67','68','69','70','71','72','73','74','75','76','77','78','79','80','81','82','83','84','85','86','87','88','89','90','91','92','93','94','95','96','97','98','99']
plt.figure(figsize=(12, 6))
values = [6, 7, 6, 9, 10, 7, 9, 4, 2, 12, 4, 11, 5, 5, 2, 3, 2, 4, 2, 8, 6, 6, 10, 3, 5, 22, 11, 7, 2, 7, 5, 10, 1, 17, 9, 7, 3, 3, 3, 7, 4, 5, 22, 6, 8, 4, 4, 2, 19, 5, 4, 1, 7, 4, 60, 2, 7, 10, 2, 10, 21, 2, 3, 5, 18, 1, 23, 1, 5, 9, 29, 4, 1, 1, 27, 0, 9, 10, 3, 3, 7, 9, 28, 6, 23, 3, 15, 2, 8, 16, 8, 3, 6, 7, 1, 4, 8, 4, 0, 5]
plt.xticks(range(0, len(cellNum), 10))
plt.grid(axis='y', linestyle='--', alpha=0.5)
plt.xlabel('Номер ячейки')
plt.ylabel('Количество элементов')
plt.title("Загрузка хэш-таблицы")
mean = 7.86
std = 8.23
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
f"Среднее: 7.86\n"
f"Стандартное отклонение:  8.23\n"
f"Коэф. вариации:   1.05\n"
f"zeros: {values.count(0)}"
)
plt.plot([], [], ' ', label=stats)
plt.legend(loc='best')
plt.axhline(y = 7.86, linewidth = 2.5, linestyle = '--', label=f'Среднее: 7.86')
plt.axhline(y = 16.09, linewidth = 2, linestyle = ':', label=f'+1σ')
plt.legend()
plt.tight_layout()
plt.savefig('images/diagrams/gnuHashLoad.png')
