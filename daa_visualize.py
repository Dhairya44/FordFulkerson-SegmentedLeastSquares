import pandas as pd
import matplotlib.pyplot as plt

fig, ax = plt.subplots(1, 2)
fig.set_figwidth(10)
f = open('input2.txt', 'r')
n, c = f.readline().split(" ")
X = []
Y = []
for i in range(int(n)):
    x, y = f.readline().split(" ")
    X.append(int(x))
    Y.append(int(y))

ax[0].scatter(X, Y, c='black')
ax[1].scatter(X, Y, c='black')

f = open('output.txt', 'r')
n = int(f.readline())

for i in range(n):
    points = f.readline().split(", ")
    X = []
    Y = []
    for j in range(len(points)-1):
        x, y = points[j].split()
        X.append(float(x))
        Y.append(float(y))
    ax[1].plot(X, Y, c='red', linewidth=1)

plt.show()
