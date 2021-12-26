from math import sqrt

N = 3
matrix = []

'''
for i in range(k):  #ввод строк расширенной матрицы
    matrix.append([float(i) for i in input().split()])
'''

matrix = [[-5, -15, -10],
           [-15, -5, -2],
           [-10, -2, 15]]

print("Исходная матрица:")
for i in range(N):
    for j in range(N):
        print(int(matrix[i][j]), end='\t')
    print()

#print("\nИтерации")
omega = [[]]  #инициализация структур хранения результатов вычислений
v = [[]]
rho = [0.0]
omega_mod = [[]]
v_mod = [[]]
rho_mod = [0.0]
for i in range(N):  #задание начальных векторов для классического и модифицированного степенных методов
    omega[0].append(sqrt(1/N))
    omega_mod[0].append(1.0)
for k in range(1, 11):
    #print(f'i = {k}.')
    #print("Классический метод")
    v.append([])
    for i in range(N):  #умножение вектора omega на матрицу
        v_i = 0
        for j in range(N):
            v_i += matrix[i][j]*omega[k-1][j]
        #print(f'v_{i+1} = {v_i}', end='\t')
        v[k].append(v_i)
   # print()
    rho_k = 0
    for i in range(N):  #числение pho как произведения векторов
        rho_k += v[k][i]*omega[k-1][i]
    #print(f'rho = {rho_k}', end='\t')
    rho.append(rho_k)
    norm_v = 0
    for i in range(N):  #вычисление евклидовой нормы вектора v
        norm_v += v[k][i]**2
    norm_v = sqrt(norm_v)
    #print(f'||v||E = {norm_v}')
    omega.append([])
    for i in range(N):  #вычисление вектора omega
        omega_i = v[k][i] / norm_v
        omega[k].append(omega_i)
        #print(f'omega_{i+1} = {omega_i}', end='\t')
   # print()

    #print("Модифицированный метод")
    v_mod.append([])
    for i in range(N):
        vm_i = 0
        for j in range(N):
            vm_i += matrix[i][j] * omega_mod[k - 1][j]
        #print(f'v_{i + 1} = {vm_i}', end='\t')
        v_mod[k].append(vm_i)
    #print()
    rho_m_k = 0
    for i in range(N):  #вычисление нромы вектора v как наибольший по модулю его элемент
        rho_m_k = (v_mod[k][i] if abs(v_mod[k][i]) > abs(rho_m_k) else rho_m_k)
    #print(f'rho = {rho_m_k}', end='\t')
    rho_mod.append(rho_m_k)
    #print(f'||v|| = {rho_m_k}')
    omega_mod.append([])
    for i in range(N):
        omega_i = v_mod[k][i] / rho_m_k
        omega_mod[k].append(omega_i)
        #print(f'omega_{i + 1} = {omega_i}', end='\t')
    #print()

print("\nПРОВЕРКА:\n\tКлассический метод")
res1 = []
res2 = []
for i in range(N):
    res2.append(rho[len(rho)-1] * omega[len(omega)-1][i])
for i in range(N):
    tmp = 0
    for j in range(N):
        tmp += matrix[i][j] * omega[len(omega)-1][j]
    res1.append(tmp)
print("A*omega:")
for i in range(N):
    print(res1[i], end='\t')
print("\nrho*omega:")
for i in range(N):
    print(res2[i], end='\t')
print("\n\tМодифицированный метод")
res1 = []
res2 = []
for i in range(N):
    res2.append(rho_mod[len(rho_mod)-1] * omega_mod[len(omega_mod)-1][i])
for i in range(N):
    tmp = 0
    for j in range(N):
        tmp += matrix[i][j] * omega_mod[len(omega_mod)-1][j]
    res1.append(tmp)
print("A*omega:")
for i in range(N):
    print(res1[i], end='\t')
print("\nrho*omega:")
for i in range(N):
    print(res2[i], end='\t')

print("\n\nТАБЛИЦА РЕЗУЛЬТАТОВ:\nКлассический метод")  #вывод результатов ввиде таблицы
print("вектор", end='\t')
for i in range(N):
    print(f'v_{i+1}(omega_{i+1})', end='\t\t')
print("rho")
print("om_0", end='\t')
for i in range(N):
    print(omega[0][i], end='\t')
print()
for k in range(1, 11):
    print(f'v_{k}', end='\t')
    for i in range(N):
        print(v[k][i], end='\t')
    print(rho[k])
    print(f'om_{k}', end='\t')
    for i in range(N):
        print(omega[k][i], end='\t')
    print()

print("Модифицированный метод")
print("вектор", end='\t')
for i in range(N):
    print(f'v_{i+1}(omega_{i+1})', end='\t\t')
print("||v||")
print("om_0", end='\t')
for i in range(N):
    print("%.16f"%omega_mod[0][i], end='\t')
print()
for k in range(1, 11):
    print(f'v_{k}', end='\t')
    for i in range(N):
        print("%.16f"%v_mod[k][i], end='\t')
    print(rho_mod[k])
    print(f'om_{k}', end='\t')
    for i in range(N):
        print("%.16f"%(omega_mod[k][i]), end='\t')
    print()


