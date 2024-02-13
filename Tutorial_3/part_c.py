import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from scipy import fft
from scipy.io import wavfile


#------------------------[Part 1]------------------------#
fs, data = wavfile.read('./sound-files/Cafe_with_noise.wav', 'rb')

fig, ax = plt.subplots() 
ax.plot(data)

ax.set_xlabel('sample')
ax.set_ylabel('y label')
ax.set_title("Cafe_with_noise.wav")
plt.show()


#------------------------[Part 2]------------------------#
Data = fft.fft(data);

for i in range(int(len(Data)/2), len(Data)):
    Data[i] = 0

fig, ax = plt.subplots() 
ax.plot(np.abs(Data))

ax.set_xlabel('sample')
ax.set_ylabel('y label')
ax.set_title("Cafe_with_noise.wav")
plt.show()


#------------------------[Part 3]------------------------#
for i in range(17250, 18500):
    Data[i] = 0

for i in range(553500, 555500):
    Data[i] = 0

data_new = (fft.ifft(Data)).real

wavfile.write('cafe_clean.wav', fs, data_new)
