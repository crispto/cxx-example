"""bezier 曲线模拟"""
import time
import numpy as np
import matplotlib.pyplot as plt

np.set_printoptions(suppress=True)
P = [(3, 4), (4, 7), (12, 10), (15, 6)]
N = len(P) - 1   # 控制点P数量

x_l = [p[0] for p in P]
y_l = [p[1] for p in P]

x_l_scale = max(x_l) - min(x_l)

x_ln = [(x - x_l[0])/x_l_scale for x in x_l]
y_ln = [(y-y_l[0])/x_l_scale for y in y_l]

plt.plot(x_l, y_l, 'b')
plt.plot(x_ln, y_ln, 'g')


def fab(n):
    if n == 0:
        return 1
    ret = n
    for i in range(1, n):
        ret *= i
    return ret


start = time.perf_counter()

# Ci
C = [fab(N)/(fab(i) * fab(N - i)) for i in range(N+1)]
# print(C)
t = np.linspace(0, 1, 513)
#t**i (1-t)**N-i
T = np.zeros((N+1, len(t)))
for i in range(N+1):
    def gen(t):
        return t ** i * (1-t)**(N-i)
    vf = np.vectorize(gen)
    T[i] = vf(t)

# print(T)
# print()
# new y
x_ln2 = np.zeros(len(t))
y_ln2 = np.zeros(len(t))
for t_index in range(len(t)):
    pt = np.array([0, 0], dtype=float)
    for i in range(N+1):
        deta = C[i] * T[i][t_index] * np.array([x_ln[i], y_ln[i]])
        pt += deta
    x_ln2[t_index] = pt[0]
    y_ln2[t_index] = pt[1]


end = time.perf_counter()

print("time escap ", end - start)

plt.plot(x_ln2, y_ln2, 'b')
x_big = [(x * x_l_scale + x_l[0]) for x in x_ln2]
y_big = [(y * x_l_scale + y_l[0]) for y in y_ln2]

# print(x_ln2, y_ln2)
plt.plot(x_big, y_big, 'r')
plt.show()
