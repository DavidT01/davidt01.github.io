import numpy as np
from numpy import linalg

np.set_printoptions(precision=5, suppress=True)

def matricaLema(pt2D, pt3D):
    return [[0, 0, 0, 0, -pt2D[2]*pt3D[0], -pt2D[2]*pt3D[1], -pt2D[2]*pt3D[2], -pt2D[2]*pt3D[3], pt2D[1]*pt3D[0], pt2D[1]*pt3D[1], pt2D[1]*pt3D[2], pt2D[1]*pt3D[3]],
            [pt2D[2]*pt3D[0], pt2D[2]*pt3D[1], pt2D[2]*pt3D[2], pt2D[2]*pt3D[3], 0, 0, 0, 0, -pt2D[0]*pt3D[0], -pt2D[0]*pt3D[1], -pt2D[0]*pt3D[2], -pt2D[0]*pt3D[3]]]

def normiraj(K):
    if(K[2][3] != 0):
        K /= K[2][3]
    return K

def matricaKamere(pts2D, pts3D):

    A = []
    n = len(pts2D)
    for i in range(n):
        matr = matricaLema(pts2D[i], pts3D[i])
        A.append(matr[0])
        A.append(matr[1])
    A = np.array(A)

    U, D, V = np.linalg.svd(A)

    T = normiraj(V[-1].reshape(3, 4))
    return np.where(np.isclose(T, 0), 0, T)

if __name__ == "__main__":
    pts2D = np.array([[12, 61, 31], [1, 95, 4], [20, 82, 19], [56, 50, 55], [32, 65, 84], [46, 39, 16], [67, 63, 78]])
    pts3D = np.array([[44, 61, 31, 99], [17, 84, 40, 45], [20, 59, 65, 3], [37, 81, 70, 82], [7, 95, 8, 29], [31, 61, 91, 37], [82, 99, 80, 7]])
    print(matricaKamere(pts2D, pts3D))