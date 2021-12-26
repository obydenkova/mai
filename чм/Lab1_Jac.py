from math import atan, cos, sin, pi


def matrix_multiply(A, B):  #функция перемножения двух матриц
    res = []
    for i in range(len(A)):
        res.append([])
        for j in range(len(A)):
            c = 0
            for k in range(len(A)):
                c += A[i][k]*B[k][j]
            res[i].append(c)
    return res


def transp(A):  #функция транспонирования
    res = []
    for i in range(len(A)):
        res.append([])
        for j in range(len(A)):
            res[i].append(A[j][i])
    return res



def matrix_output(A):  #функция для вывода матрицы
    for i in range(len(A)):
        for j in range(len(A[i])):
            print("%.16f"%A[i][j], end='\t')
        print()



N = 3
matrix = []  #инициализация списка строк матрицы

'''
for i in range(k):  #ввод строк расширенной матрицы
    matrix.append([float(i) for i in input().split()])
'''

matrix = [[-5, -15, -10],
           [-15, -5, -2],
           [-10, -2, 15]]
matrix_original = matrix  #сохраняем исходную матрицу для проверки решения
print("Исходная матрица:")
matrix_output(matrix)
print("\nИтерации")

V = []
for i in range(N):
    V.append([])
    for j in range(N):
        V[i].append(1 if i == j else 0)

for iter in range(1, 7):
    print(f'Шаг {iter}')
    a_max = 0
    k = 0
    m = 0
    for i in range(N):  #поиск максимального по модулю элемента выше главн. диагонали
        for j in range(i+1, N):
            if abs(matrix[i][j]) > abs(a_max):
                k = i
                m = j
                a_max = matrix[i][j]
    print(f'a_max = {a_max}, k = {k+1}, m = {m+1}')
    phi = (atan((2*a_max)/(matrix[k][k]-matrix[m][m])) / 2 if matrix[k][k] != matrix[m][m]
           else (pi/4 if matrix[k][m] > 0 else -pi/4))  #вычисление угла поворота по формуле
    print(f'phi = {phi}')               #в случае деления на ноль присваивается значение pi/4
    H = []
    for i in range(N):  #построение матрицы поворота H по алгоритму
        H.append([])
        for j in range(N):
            h = 0.0
            if i == j:
                if (i == k) or (i == m):
                    h = cos(phi)
                else:
                    h = 1.0
            elif i == k and j == m:
                h = -sin(phi)
            elif i == m and j == k:
                h = sin(phi)
            H[i].append(h)
    print(f'H_{iter}:')
    matrix_output(H)
    H_t = transp(H)
    V = matrix_multiply(V, H)
    print(f'H_{iter}^-1:')
    matrix_output(H_t)
    matrix = matrix_multiply(matrix_multiply(H_t, matrix), H)  #вычисление поворота
    print(f'A_{iter}:')
    matrix_output(matrix)
    print()
print("Конец итерационного процесса.\n")

lamdas = []
for i in range(N):  #собственные значения на главной диагонали
    lamdas.append(matrix[i][i])
print("матрица V:")
matrix_output(V)
for i in range(N):
    norm = 0
    for j in range(N):
        norm = (V[j][i] if abs(norm) < abs(V[j][i]) else norm)
    for j in range(N):
        V[j][i] /= norm
print()

print("ПРОВЕРКА:")
V_t = transp(V)
for k in range(N):
    print(f'\tПара {k+1}')
    res1 = []
    res2 = []
    for i in range(N):
        tmp = 0
        for j in range(N):
            tmp += matrix_original[i][j] * V[k][j]
        res1.append(tmp)
    for i in range(N):
        res2.append(lamdas[k]*V[k][i])
    print(f'A*V_{k+1}:')
    for i in range(N):
        print(res1[i], end='\t')
    print(f'\nlambda_{k+1}*V_{k+1}:')
    for i in range(N):
        print(res2[i], end='\t')
    print()

print("\nРЕЗУЛЬТАТЫ:")
for i in range(N):
    print(f'lambda_{i+1} = {lamdas[i]}')
    for j in range(N):
        print(f'V_{i+1}{j+1}', end='\t\t\t')
    print()
    for j in range(N):
        print(V[j][i], end='\t')
    print()


