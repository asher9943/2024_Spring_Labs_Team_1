from scipy.io.wavfile import read
from scipy.signal import correlate
import numpy as np
import matplotlib.pyplot as plt

sampling_rate1, data1 = read("sound-files/M1.wav")
sampling_rate2, data2 = read("sound-files/M2.wav")
sampling_rate3, data3 = read("sound-files/M3.wav")

print(np.sqrt(np.mean(data1.astype(float) ** 2)))
print(np.sqrt(np.mean(data2.astype(float) ** 2)))
print(np.sqrt(np.mean(data3.astype(float) ** 2)))

good = correlate(data1, data2)

mine = np.fft.ifft(
    np.fft.fft(data1, len(data1) + len(data2))
    * np.fft.fft(data2[::-1], len(data1) + len(data2))
)

t1 = np.arange(0, len(data1), 1)
t2 = np.arange(-len(mine) / 2, len(mine) / 2, 1)
fig, ax = plt.subplots(3)
ax[0].plot(t1, data1)
ax[1].plot(t1, data2)
ax[2].plot(t2, np.abs(mine))

max = np.argmax(mine)
adjusted_max = max - (len(mine) / 2)
delay = adjusted_max * (1 / sampling_rate1)

print(delay)

plt.show()
