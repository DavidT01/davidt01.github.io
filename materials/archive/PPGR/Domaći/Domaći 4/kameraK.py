import numpy as np
from numpy import linalg

np.set_printoptions(precision=5, suppress=True)

def normiraj(K):
    if(K[2][2] != 0):
        K /= K[2][2]
    return K

def kameraK(T):
    
    T0 = np.array([[T[0][0], T[0][1], T[0][2]], [T[1][0], T[1][1], T[1][2]], [T[2][0], T[2][1], T[2][2]]])
    if(np.linalg.det(T0) < 0):
        T0 *= -1
        T *= -1

    Q, R = np.linalg.qr(np.linalg.inv(T0))

    for i in range(3):
        if(R[i][i] < 0):
            for j in range(3):
                R[i][j] *= -1
                Q[j][i] *= -1

    K = normiraj(np.linalg.inv(R))
    return np.where(np.isclose(K, 0), 0, K)

if __name__ == "__main__":
    T = np.array([[-2, 3, 0, 7], [-3, 0, 3, -6], [1, 0, 0, -2]])
    print(kameraK(T))