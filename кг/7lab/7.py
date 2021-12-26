from collections import namedtuple
import numpy as np
import pylab as plt
Vector = namedtuple('Vector', ['x', 'y'])
p1 = Vector(0.0, 0.0)
p2 = Vector(2.0, 0.0)
t1 = Vector(1.0, 0.0)
t2 = Vector(1.0, 1.0)
A = np.array([
    [p1.x ** 3, p1.x ** 2, p1.x, 1],
    [p2.x ** 3, p2.x ** 2, p2.x, 1],
    [3 * p1.x ** 2, 2 * p1.x, 1, 0],
    [3 * p2.x ** 2, 2 * p2.x, 1, 0]
], dtype=np.float64)
b = np.array([p1.y, p2.y, t1.y / t1.x, t2.y / t2.x])
coefficients = np.linalg.solve(A, b)
x = np.arange(p1.x, p2.x + 0.01, 0.01)
y = (coefficients[0] * x ** 3 +
     coefficients[1] * x ** 2 +
     coefficients[2] * x +
     coefficients[3])
print(coefficients)
plt.plot(x, y)
plt.scatter([p1.x, p2.x], [p1.y, p2.y])
plt.grid()
plt.show()
