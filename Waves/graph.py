from matplotlib import pyplot as plt
from math import cos

fvalues = open("values.csv", 'r')
h, T, tau = fvalues.readline().split(';')
h, T, tau = float(h), float(T), float(tau)
values = fvalues.readline().split(';')

values = [float(i) for i in values]
fvalues.close()
x = [h * i for i in range(int(1 / h))]
y = [2*cos(T - h * i) for i in range(int(1 / h))]
err = [abs(y[i] - values[i]) for i in range(int(1 / h))]

plt.plot(x, y)
plt.plot(x, values)
plt.savefig('solution.png')

plt.plot(x, err)
plt.savefig('error.png')