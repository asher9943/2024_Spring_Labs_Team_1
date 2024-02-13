import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()

# syntax for 3-D projection
ax = plt.axes(projection="3d")

# defining all 3 axis
x = np.linspace(0, 2 * np.pi, 100)
y = x
z = np.sin(np.sqrt(np.power(x, 2) + np.power(y, 2)))

# plotting
ax.plot3D(x, y, z)
ax.set_title("3D line plot")
plt.show()
