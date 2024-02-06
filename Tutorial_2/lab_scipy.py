import matplotlib.pyplot as plt
import numpy as np


import matplotlib as mpl
from matplotlib import cm
from scipy import linalg, optimize, fft

#------------------------[Part 3]------------------------#
A = np.matrix('[3,1]; [1,2]')
b = np.matrix('[9]; [8]')

x = np.linalg.solve(A, b)
print(x)

#------------------------[Part 3]------------------------#
def f(x):
    return x**2 + 2*x

res = optimize.minimize_scalar(f)
print(res)

#------------------------[Part 3]------------------------#
t = np.linspace(0,160)
sp = fft.fftshift(fft.fft(np.sin(100*np.pi*t) + 0.5*np.sin(160*np.pi*t)))
freq = fft.fftshift(fft.fftfreq(t.shape[-1]))

plt.plot(freq, np.absolute(sp), freq, np.angle(sp))
plt.show()