import numpy as np
from numpy import linalg

np.set_printoptions(precision=5, suppress=True)

def matricaKretanja(matrica):
    determinanta = np.linalg.det(matrica)
    if(not np.isclose(determinanta, 1)):
        return False
    if(np.allclose(matrica @ matrica.T, np.eye(3))):
        return True
    return False

def A2Euler(matrica):

    if(not matricaKretanja(matrica)):
        return "Nije matrica kretanja!"

    if(matrica[2][0] < 1):
        if(matrica[2][0] > -1):
            psi = np.arctan2(matrica[1][0], matrica[0][0])
            theta = np.arcsin(-matrica[2][0])
            phi = np.arctan2(matrica[2][1], matrica[2][2])

        else:
            psi = np.arctan2(-matrica[0][1], matrica[1][1])
            theta = np.pi / 2
            phi = 0

    else:
        psi = np.arctan2(-matrica[0][1], matrica[1][1])
        theta = -np.pi / 2
        phi = 0

    uglovi = np.array([psi, theta, phi])
    return np.where(np.isclose(uglovi, 0), 0, uglovi)

if __name__ == "__main__":
    A = (1/9) * np.array([[1, -8, -4], [4, 4, -7], [8, -1, 4]])
    print(A2Euler(A))