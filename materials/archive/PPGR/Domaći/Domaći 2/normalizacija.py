import numpy as np
from numpy import linalg
import math

np.set_printoptions(precision = 5, suppress = True)

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

if __name__ == "__main__":
    trapez = [[-3, -1, 1], [3, -1, 1], [1, 1, 1], [-1, 1, 1], [1, 2, 3], [-8, -2, 1]] 
    print(normMatrix(trapez))