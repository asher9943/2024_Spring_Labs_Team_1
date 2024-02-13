from scipy import linalg, optimize, fft
import numpy as np
import matplotlib.pyplot as plt

a = np.array([[3, 1], [1, 2]])
b = np.array([9, 8])

print(f"Solving linear system: {linalg.solve(a, b)}")


def y(x):
    return np.power(x, 2) + 2 * x


print(f"Optimizing function: {optimize.minimize_scalar(y)}")

sr = 2000
ts = 1.0 / sr
x = np.arange(0, 1, ts)

f = np.sin(100 * np.pi * x) + 0.5 * np.sin(160 * np.pi * x)
F = fft.fft(f)

N = len(F)
n = np.arange(N)
T = N / sr
freq = n / T

plt.figure(figsize=(12, 6))
plt.stem(freq, np.abs(F), "b", markerfmt=" ", basefmt="-b")
plt.xlabel("Freq (Hz)")
plt.ylabel("FFT Amplitude |X(freq)|")
plt.xlim(0, 100)
plt.show()
