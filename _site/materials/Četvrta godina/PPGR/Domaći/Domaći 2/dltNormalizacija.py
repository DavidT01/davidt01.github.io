import numpy as np
from numpy import linalg
import math

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

def normMatrix(origs):

    # translacija
    n = len(origs)
    x = sum([t[0] / t[2] for t in origs]) / n
    y = sum([t[1] / t[2] for t in origs]) / n
    G = [[1, 0, -x], [0, 1, -y], [0, 0, 1]]

    # prosecno rastojanje
    r = 0.0
    for i in range(n):
        t1 = float(origs[i][0] / origs[i][2]) - x
        t2 = float(origs[i][1] / origs[i][2]) - y

        r = r + math.sqrt(t1**2 + t2**2)
    r = r / float(n)

    # skaliranje
    S = [[float(math.sqrt(2)) / r, 0, 0], [0, float(math.sqrt(2)) / r, 0], [0, 0, 1]]

    return np.dot(S, G)

def normiranaMatrica(matr):
    if(matr[2][2] != 1 and matr[2][2] != 0):
        matr = matr / matr[2][2]
    return matr

def DLTwithNormalization(origs, imgs):

    T = normMatrix(origs)
    TP = normMatrix(imgs)
    
    # normalizacija tacaka
    n = len(origs)
    for i in range(n):
        origs[i] = np.dot(T, origs[i]).tolist()
        imgs[i] = np.dot(TP, imgs[i]).tolist()
        
    PP = DLT(origs, imgs)
    
    P = np.dot(np.dot(np.linalg.inv(TP), PP), T)
    return normiranaMatrica(P)

if __name__ == "__main__":
    trapez = [[-3, -1, 1], [3, -1, 1], [1, 1, 1], [-1, 1, 1], [1, 2, 3], [-8, -2, 1]] 
    pravougaonik1 = [[-2, -1, 1], [2, -1, 1], [2, 1, 1], [-2, 1, 1], [2, 1, 5], [-16, -5, 5]]
    print(DLTwithNormalization(trapez, pravougaonik1))