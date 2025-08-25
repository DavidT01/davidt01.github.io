import numpy as np
from numpy import linalg

np.set_printoptions(precision=5, suppress=True)

def centar(T):

    b = np.array([0, 0, 0, 1])
    T = np.array([[T[0][0], T[0][1], T[0][2], T[0][3]],
                  [T[1][0], T[1][1], T[1][2], T[1][3]],
                  [T[2][0], T[2][1], T[2][2], T[2][3]],
                  [0, 0, 0, 1]])
    C = np.linalg.solve(T, b)
    return np.where(np.isclose(C, 0), 0, C)

if __name__ == "__main__":
    T = np.array([[-2, 3, 0, 7], [-3, 0, 3, -6], [1, 0, 0, -2]])
    print(centar(T))