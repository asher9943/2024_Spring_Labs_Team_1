import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 2 * np.pi, 100)

plt.figure(figsize=(5, 2.7), layout="constrained")
plt.plot(x, np.sin(x), label="sine")  # Plot some data on the (implicit) axes.
plt.xlabel("x")
plt.ylabel("sin(x)")
plt.title("Sine")
plt.legend()
plt.show()
