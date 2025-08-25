import numpy as np
from numpy import linalg

np.set_printoptions(precision = 5, suppress = True)

def jedinicnaMatrica(matrica):
    if(np.allclose(matrica, np.eye(3))):
        return True
    return False

def matricaKretanja(matrica):
    determinanta = np.linalg.det(matrica)
    if(not np.isclose(determinanta, 1)):
        return False
    if(np.allclose(matrica @ matrica.T, np.eye(3))):
        return True
    return False

def jedinicniVektor(v):
    return v / np.linalg.norm(v)

def sopstveniVektor(matrica):
    p = np.cross(np.array(matrica[0]), np.array(matrica[1]))
    if(np.allclose(p, np.zeros(3))):
        p = np.cross(np.array(matrica[0]), np.array(matrica[2]))
    if(np.allclose(p, np.zeros(3))):
        p = np.cross(np.array(matrica[1]), np.array(matrica[2]))
    return jedinicniVektor(p)

def A2AxisAngle(matrica):

    if(jedinicnaMatrica(matrica)):
        return np.array([1, 0, 0]), 0

    if(not matricaKretanja(matrica)):
        return "Nije matrica kretanja!"

    mE = matrica - np.eye(3)
    p = sopstveniVektor(mE)

    u = jedinicniVektor(np.array(mE[2]))
    if(np.allclose(u, np.zeros(3))):
        u = jedinicniVektor(np.array(mE[1]))
    if(np.allclose(u, np.zeros(3))):
        u = jedinicniVektor(np.array(mE[0]))

    uP = jedinicniVektor(matrica @ u)

    phi = np.arccos(u @ uP)

    if((np.cross(u, uP) @ p) < 0):
        p = -p

    pphi = np.array([p[0], p[1], p[2], phi])
    return np.where(np.isclose(pphi, 0), 0, pphi)

if __name__ == "__main__":
    A = (1/9) * np.array([[1, -8, -4], [4, 4, -7], [8, -1, 4]])
    print(A2AxisAngle(A))
    A = (1/9) * np.array([[1, -8, -4], [4, 4, -7], [8, -1, 5]])
    print(A2AxisAngle(A))
    A = np.array([[np.cos(np.pi/4), -np.sin(np.pi/4), 0], [np.sin(np.pi/4), np.cos(np.pi/4), 0], [0, 0, 1]])
    print(A2AxisAngle(A))
    A = np.array([[0, 0, 1], [1, 0, 0], [0, 1, 0]])
    print(A2AxisAngle(A))
    A = np.array([[1, 0, 0], [0, 1, 0], [0, 0, 1]])
    print(A2AxisAngle(A))
    A = np.array([[-1, 0, 0], [0, 0, 1], [0, 1, 0]])
    print(A2AxisAngle(A))