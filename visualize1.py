import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('output1.txt',names=["x","Time"])
print(data)
plt.scatter(data['x'].astype(int), data['Time'].astype(float))
plt.show()
