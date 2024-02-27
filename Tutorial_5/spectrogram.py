import matplotlib.pyplot as plt
import numpy as np
from scipy import signal
from scipy.io import wavfile

sample_rate, samples = wavfile.read('file.wav')
frequencies, times, spectrogram = signal.spectrogram(samples, sample_rate)

plt.pcolormesh(times, frequencies, np.log(spectrogram))
plt.ylabel('Frequency [Hz]')
plt.xlabel('Time [sec]')
plt.show()
