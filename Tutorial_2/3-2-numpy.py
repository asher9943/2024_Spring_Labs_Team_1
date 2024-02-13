import numpy as np

print(f"Creating a numpy array:\n{np.array([1, 2, 3, 4])}")
print(f"Creating a 3x4 of ones:\n{np.ones([3, 4])}")
print(f"Creating a 4x3 of zeros:\n{np.zeros([4, 3])}")

A = np.array([[1, 2, 3], [4, 5, 6]])
B = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]])
print(f"Multiplying A and B:\n{np.matmul(A, B)}")

C = np.array([[3, 1], [1, 2]])
val, vect = np.linalg.eig(C)

print(f"Eigenvalues:\n{val}")
print(f"Eigenvectors:\n{vect}")
