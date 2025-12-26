import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

np.set_printoptions(precision = 5, suppress = True)

def matricaLema(pt2D, pt3D):
    return [[0, 0, 0, 0, -pt2D[2]*pt3D[0], -pt2D[2]*pt3D[1], -pt2D[2]*pt3D[2], -pt2D[2]*pt3D[3], pt2D[1]*pt3D[0], pt2D[1]*pt3D[1], pt2D[1]*pt3D[2], pt2D[1]*pt3D[3]],
            [pt2D[2]*pt3D[0], pt2D[2]*pt3D[1], pt2D[2]*pt3D[2], pt2D[2]*pt3D[3], 0, 0, 0, 0, -pt2D[0]*pt3D[0], -pt2D[0]*pt3D[1], -pt2D[0]*pt3D[2], -pt2D[0]*pt3D[3]]]

def normirajT(T):
    if(T[2][3] != 0):
        T /= T[2][3]
    return T

def matricaKamere(pts2D, pts3D):
    
    A = []
    n = len(pts2D)
    for i in range(n):
        matr = matricaLema(pts2D[i], pts3D[i])
        A.append(matr[0])
        A.append(matr[1])
    A = np.array(A)

    _, _, V = np.linalg.svd(A)

    T = normirajT(V[-1].reshape(3, 4))
    return np.where(np.isclose(T, 0), 0, T)

def centar(T):
    
    b = np.array([0, 0, 0, 1])
    T = np.array([[T[0][0], T[0][1], T[0][2], T[0][3]],
                  [T[1][0], T[1][1], T[1][2], T[1][3]],
                  [T[2][0], T[2][1], T[2][2], T[2][3]],
                  [0, 0, 0, 1]])
    C = np.linalg.solve(T, b)
    return np.where(np.isclose(C, 0), 0, C)

def kameraA(T):
    
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

    A = Q.T
    return np.where(np.isclose(A, 0), 0, A)

def normirajK(K):
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

    K = normirajK(np.linalg.inv(R))
    return np.where(np.isclose(K, 0), 0, K)

if __name__ == "__main__":

    pixelOrgs = np.array([[481, 554, 1],
                          [742, 702, 1],
                          [568, 692, 1],
                          [306, 631, 1],
                          [203, 676, 1],
                          [461, 844, 1],
                          [640, 955, 1],
                          [710, 1002, 1],
                          [275, 935, 1],
                          [207, 984, 1],
                          [451, 1154, 1]])

    orgs =  np.array([1, -1, -1]) * (np.array([1599, 0, 0]) - pixelOrgs)

    imgs = np.array([[0, 0, 3, 1],
                     [0, 3, 3, 1],
                     [1, 2, 3, 1],
                     [2, 0, 3, 1],
                     [3, 0, 3, 1],
                     [3, 3, 3, 1],
                     [1, 3, 1, 1],
                     [0, 3, 0, 1],
                     [3, 1, 1, 1],
                     [3, 0, 0, 1],
                     [3, 3, 0, 1]])

    T = matricaKamere(orgs, imgs)
    print("Matrica kamere:\n\n", T)
    C = centar(T)
    print("\nCentar kamere:\n\n", C)
    A = kameraA(T)
    print("\nSpoljasnja matrica kamere:\n\n", A)
    K = kameraK(T)
    print("\nMatrica kalibracije kamere:\n\n", K)
    
    # Plotovanje
    fig = plt.figure("Kocka i kamera")
    fig.set_figheight(7)
    fig.set_figwidth(10)
    fig.subplots_adjust(top = 1, bottom = 0, left = 0, right = 1)
    ax = plt.axes(projection = '3d')
    ax.set_xlim([0, 17])
    ax.set_ylim([0, 17])
    ax.set_zlim([0, 17])
    ax.set_xlabel("X-osa", color = 'r')
    ax.set_ylabel("Y-osa", color = 'g')
    ax.set_zlabel("Z-osa", color = 'b')
    
    # Kocka
    kocka = np.ones((3, 3, 3), dtype = 'bool')
    ax.voxels(kocka, facecolor = 'yellow', edgecolors = 'k')
    ax.quiver(0, 0, 0, 6, 0, 0, color = 'r')
    ax.quiver(0, 0, 0, 0, 6, 0, color = 'g')
    ax.quiver(0, 0, 0, 0, 0, 6, color = 'b')
    
    # Tacke na kocki
    for i in range(len(imgs)):
        ax.plot(imgs[i][0], imgs[i][1], imgs[i][2], 'mo')
        ax.text(imgs[i][0], imgs[i][1], imgs[i][2], 'P' + str(i + 1), color = 'm', fontsize = 10)
    
    # Kamera
    ax.plot(C[0], C[1], C[2], 'm.')
    ax.text(C[0], C[1], C[2] - 1, 'C', color = 'm')
    e1 = np.array(A[0])
    e2 = np.array(A[1])
    e3 = np.array(A[2])
    ax.quiver(C[0], C[1], C[2], e1[0], e1[1], e1[2], color = 'r')
    ax.quiver(C[0], C[1], C[2], e2[0], e2[1], e2[2], color = 'g')
    ax.quiver(C[0], C[1], C[2], e3[0], e3[1], e3[2], color = 'b')

    plt.show()