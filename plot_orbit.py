import pandas as pd
import matplotlib.pyplot as plt

# read generated orbit data
df = pd.read_csv('orbit.csv', skipinitialspace=True)

fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

# plot trajectory and earth
ax.plot(df['x'], df['y'], df['z'], color='red', linewidth=1.5, label='CubeSat')
ax.scatter(0, 0, 0, color='blue', s=100, label='Earth')

ax.set_xlabel('X (m)')
ax.set_ylabel('Y (m)')
ax.set_zlabel('Z (m)')
ax.legend()

plt.show()