import numpy as np

np.set_printoptions(precision=5, suppress=True)

def jedinicniVektor(v):
    return v / np.linalg.norm(v)

def jedinicniKvaternion(v):
    return v / np.linalg.norm(v)

def Q2AxisAngle(q):

    q = jedinicniKvaternion(q)
    w = q[3]

    if(w < 0):
        q = -q

    (x, y, z, w) = q

    phi = 2 * np.arccos(w)
    if(phi == 0):
        return np.array([1, 0, 0, 0])

    if(abs(w) == 1):
        pphi = np.array([1, 0, 0, phi])
    else:
        p = jedinicniVektor(np.array([x, y, z]))
        pphi = np.array([p[0], p[1], p[2], phi])

    return np.where(np.isclose(pphi, 0), 0, pphi)

if __name__ == "__main__":
    q = np.array([np.sin(np.pi/8), 0, 0, np.cos(np.pi/8)])
    print(Q2AxisAngle(q))
    q = np.array([1, 5, 1, 3])
    print(Q2AxisAngle(q))
    q = np.array([0, np.sqrt(3)/2, 0, -1/2])
    print(np.rad2deg(Q2AxisAngle(q)[3]))