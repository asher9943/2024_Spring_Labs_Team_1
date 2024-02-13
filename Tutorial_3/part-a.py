from scipy.io.wavfile import read
import matplotlib.pyplot as plt
import os

sampling_rate, data = read(os.path.join(os.path.dirname(os.path.abspath(__file__)), "sound-files\\human_voice.wav"))
print(sampling_rate)

plt.plot(data)
plt.ylabel("Amplitude")
plt.xlabel("Time")
plt.show()

new_data = data[0::6]
plt.plot(new_data)
plt.ylabel("Amplitude")
plt.xlabel("Time")
plt.show()