from scipy.io.wavfile import read
import matplotlib.pyplot as plt
import numpy as np

sampling_rate, data = read("sound-files/human_voice.wav")
print(sampling_rate)

t = np.arange(0, len(data), 1)
fig, ax = plt.subplots()
ax.plot(t, data)

ax.set(xlabel="Sample", ylabel="Audio", title="Human voice recording")
ax.grid()

subdata = data[::6]
print(len(subdata))

t2 = np.arange(0, len(subdata), 1)
fig2, ax2 = plt.subplots()
ax2.plot(t2, subdata)

ax2.set(xlabel="Sample", ylabel="Audio", title="Human voice recording downsampled")
ax2.grid()

plt.show()
