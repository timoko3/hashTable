import matplotlib.pyplot as plt

categories = ['A', 'B', 'C']
values = [5, 7, 3]

plt.bar(categories, values)

plt.title("Столбчатая диаграмма")
plt.show()
plt.savefig('example.png')