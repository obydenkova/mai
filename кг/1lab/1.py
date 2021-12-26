import numpy as np
import pylab as plt

a = float(input("Input a: "))


def f(x, y):
    return (x ** 2 + y ** 2) ** 2 - (a ** 2) * (x ** 2 - y ** 2)


x_grid, y_grid = np.meshgrid(np.arange(-a, a + 0.1, 0.1), np.arange(-a, a + 0.1, 0.1))
z_grid = f(x_grid, y_grid)

plt.grid()
plt.contour(x_grid, y_grid, z_grid, levels=[0])
plt.show()
