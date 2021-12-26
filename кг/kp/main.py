import numpy as np
from tkinter import Tk, Canvas

unit_seq = 200

delta = float(input("Шаг сетки (от 0 до 1): "))

p00 = np.array([float(x) for x in input("1-ая точка: ").split()])
p01 = np.array([float(x) for x in input("2-ая точка: ").split()])
p10 = np.array([float(x) for x in input("3-я  точка: ").split()])
p11 = np.array([float(x) for x in input("4-ая точка: ").split()])

def rotate_y(angle):
    c = np.cos(angle)
    s = np.sin(angle)
    return np.array([
        [c, -s, 0],
        [s, c, 0],
        [0, 0, 1]
    ])


def rotate_z(angle):
    c = np.cos(angle)
    s = np.sin(angle)
    return np.array([
        [c, 0, s],
        [0, 1, 0],
        [-s, 0, c]
    ])

def get_point(u, w):
    return p00 * (1 - u) * (1 - w) + p01 * (1 - u) * w + p10 * u * (1 - w) + p11 * u * w

def project(point):
    return 400 + unit_seq * point[2], 400 - unit_seq * point[1]

def draw(c):
    u = 0.0
    while u <= 1.0:
        x1, y1 = project(get_point(u, 0))
        x2, y2 = project(get_point(u, 1))
        c.create_line(x1, y1, x2, y2)
        u += delta

    w = 0.0
    while w <= 1.0:
        x1, y1 = project(get_point(0, w))
        x2, y2 = project(get_point(1, w))
        c.create_line(x1, y1, x2, y2, width=2)
        w += delta

def right_arrow(event):
    global p00
    global p01
    global p10
    global p11

    p00 = np.dot(rotate_z(0.05), p00)
    p01 = np.dot(rotate_z(0.05), p01)
    p10 = np.dot(rotate_z(0.05), p10)
    p11 = np.dot(rotate_z(0.05), p11)

    canvas.delete('all')
    draw(canvas)

def left_arrow(event):
    global p00
    global p01
    global p10
    global p11

    p00 = np.dot(rotate_z(-0.05), p00)
    p01 = np.dot(rotate_z(-0.05), p01)
    p10 = np.dot(rotate_z(-0.05), p10)
    p11 = np.dot(rotate_z(-0.05), p11)

    canvas.delete('all')
    draw(canvas)

def up_arrow(event):
    global p00
    global p01
    global p10
    global p11

    p00 = np.dot(rotate_y(0.05), p00)
    p01 = np.dot(rotate_y(0.05), p01)
    p10 = np.dot(rotate_y(0.05), p10)
    p11 = np.dot(rotate_y(0.05), p11)

    canvas.delete('all')
    draw(canvas)

def down_arrow(event):
    global p00
    global p01
    global p10
    global p11

    p00 = np.dot(rotate_y(-0.05), p00)
    p01 = np.dot(rotate_y(-0.05), p01)
    p10 = np.dot(rotate_y(-0.05), p10)
    p11 = np.dot(rotate_y(-0.05), p11)

    canvas.delete('all')
    draw(canvas)

root = Tk()
root.title("Билинейная поверхность")
root.bind('d', right_arrow)
root.bind('a', left_arrow)
root.bind('w', up_arrow)
root.bind('s', down_arrow)
root.bind("<Escape>", exit)
canvas = Canvas(root, width=800, height=800, bg='white')
canvas.pack()
draw(canvas)
root.geometry("800x800")
root.mainloop()
