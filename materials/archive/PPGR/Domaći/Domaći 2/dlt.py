import numpy as np
from numpy import linalg

np.set_printoptions(precision = 5, suppress = True)

def matricaLema(M, N):
    return [[0, 0, 0, -N[2] * M[0], -N[2] * M[1], -N[2] * M[2], N[1] * M[0], N[1] * M[1], N[1] * M[2]],
            [N[2] * M[0], N[2] * M[1], N[2] * M[2], 0, 0, 0, -N[0] * M[0], -N[0] * M[1], -N[0] * M[2]]]

def normiranaMatrica(matr):
    if(matr[2][2] != 1 and matr[2][2] != 0):
        matr = matr / matr[2][2]
    return matr

def DLT(origs, imgs):

    n = len(origs)
    A = []
    for i in range(n):
        matr = matricaLema(origs[i], imgs[i])
        A.append(matr[0])
        A.append(matr[1])
    A = np.array(A)
    
    U, D, V = np.linalg.svd(A)

    P = V[-1].reshape(3, 3)
    
    return normiranaMatrica(P)

if __name__ == "__main__":
    trapez = [[-3, -1, 1], [3, -1, 1], [1, 1, 1], [-1, 1, 1], [1, 2, 3], [-8, -2, 1]] 
    pravougaonik1 = [[-2, -1, 1], [2, -1, 1], [2, 1, 1], [-2, 1, 1], [2, 1, 5], [-16, -5, 5]]
    print(DLT(trapez, pravougaonik1))