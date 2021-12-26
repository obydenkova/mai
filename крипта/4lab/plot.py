import matplotlib.pyplot as plt
import numpy as np
from math import exp

def F(x):
    return exp(-x) / x

f = open("shooting_method")

x1 = []
y1 = []

n = int(f.readline())

for i in range(n):
    x1.append(float(f.readline()))
for i in range(n):
    y1.append(float(f.readline()))

exact_y = [F(i) for i in x1]

plt.subplot(211)
plt.scatter(x1, y1, color="r")
plt.plot(x1, exact_y, color='b')
plt.title('Shooting method')


f = open("finite_diff_method")

x2 = []
y2 = []

n = int(f.readline())

for i in range(n):
    x2.append(float(f.readline()))
for i in range(n):
    y2.append(float(f.readline()))

plt.subplot(212)
plt.scatter(x2, y2, color="r")
plt.plot(x2, exact_y, color='b')
plt.title('Finite difference method')  

plt.tight_layout()
plt.show()
