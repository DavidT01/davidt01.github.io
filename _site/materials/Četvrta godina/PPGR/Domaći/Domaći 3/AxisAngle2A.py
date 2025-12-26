import numpy as np

np.set_printoptions(precision = 5, suppress = True)

def jedinicniVektor(v):
    return v / np.linalg.norm(v)

def AxisAngle2A(pphi):

    p = jedinicniVektor(np.array([pphi[0], pphi[1], pphi[2]]))
    phi = pphi[3]

    ppt = np.array([[p[0] * p[0], p[0] * p[1], p[0] * p[2]], [p[1] * p[0], p[1] * p[1], p[1] * p[2]], [p[2] * p[0], p[2] * p[1], p[2] * p[2]]])
    E = np.eye(3)
    px = np.array([[0, -p[2], p[1]], [p[2], 0, -p[0]], [-p[1], p[0], 0]])

    A = ppt + np.cos(phi) * (E - ppt) + np.sin(phi) * px
    return np.where(np.isclose(A, 0), 0, A)

if __name__ == "__main__":
    pphi = np.array([1/3, -2/3, 2/3, np.pi/2])
    print(AxisAngle2A(pphi))
    pphi2 = np.array([0, 0, 1, 0.78539816])
    print(AxisAngle2A(pphi2))