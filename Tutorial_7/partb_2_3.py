import numpy as np

mat_BA = np.matrix('[0,-1,0]; [1,0,0]; [0,0,1]')
mat_AB = np.invert(mat_BA)

p_b = np.transpose(np.array([1,2,3]))
t = np.transpose(np.array([1,2,3]))

p_a = mat_AB@p_b + t

print(p_a)

