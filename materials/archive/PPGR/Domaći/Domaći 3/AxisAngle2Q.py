import numpy as np

np.set_printoptions(precision=5, suppress=True)

def jedinicniVektor(v):
    return v / np.linalg.norm(v)

def jedinicniKvaternion(v):
    return v / np.linalg.norm(v)

def AxisAngle2Q(pphi):

    p = np.array([pphi[0], pphi[1], pphi[2]])
    phi = pphi[3]
    
    if(phi == 0):
        return np.array([0, 0, 0, 1])
    
    p = jedinicniVektor(p)
    
    w = np.cos(phi / 2)
    (x, y, z) = np.sin(phi / 2) * p
    
    q = jedinicniKvaternion(np.array([x, y, z, w]))
    return np.where(np.isclose(q, 0), 0, q)

if __name__ == "__main__":
    pphi = np.array([1, 0, 0, (np.pi) / 2])
    print(AxisAngle2Q(pphi))
    pphi = np.array([1, 1, 1, (2 * np.pi) / 3])
    print(AxisAngle2Q(pphi))
    pphi = np.array([1, 1, 1, (2 * np.pi) / 3])
    print(AxisAngle2Q(pphi))
    pphi = np.array([0, 1/np.sqrt(2), 1/np.sqrt(2), np.pi])
    print(AxisAngle2Q(pphi))