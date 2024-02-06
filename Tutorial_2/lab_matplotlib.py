import matplotlib.pyplot as plt
import numpy as np


import matplotlib as mpl
from matplotlib import cm


#------------------------[Part 1]------------------------#
x = np.linspace(0, 2*np.pi)

fig, ax = plt.subplots() 
ax.plot(x, np.sin(x));


#------------------------[Part 2]------------------------#
ax.set_xlabel('x label')
ax.set_ylabel('y label')
ax.set_title("Plot")
plt.show()


#------------------------[Part 3]------------------------#
x = np.linspace(0, 2*np.pi)
y = np.linspace(0, 2*np.pi)
X, Y = np.meshgrid(x,y)

z = np.sin(np.sqrt(X**2 + Y**2))

fig2, ax2 = plt.subplots(subplot_kw={"projection": "3d"})
ax2.plot_surface(X, Y, z, vmin=z.min() * 2, cmap=cm.Blues)
plt.show()

# need to close first figure to see second
