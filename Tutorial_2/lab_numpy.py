import numpy as np

#------------------------[Part 3]------------------------#
ar1 = np.array([1,2,3,4])

print()
print("Part 3")
print(ar1)
print()
print("------------------")


#------------------------[Part 4]------------------------#
ones = np.ones((3,4))
zeros = np.zeros((4,3))

print("Part 4")
print(ones)
print()
print(zeros)
print()
print("------------------")


#------------------------[Part 5]------------------------#
A = np.arange(6).reshape(2,3)
B = np.arange(12).reshape(3,4)
C = A @ B

print("Part 5")
print(A)
print()
print(B)
print()
print(C)
print()
print("------------------")


#------------------------[Part 6]------------------------#
mat = np.matrix('[3,1]; [1,2]')
eig = np.linalg.eig(mat)

print("Part 6")
print(mat)
print()
print(eig.eigenvalues)
print()
print(eig.eigenvectors)
print()


