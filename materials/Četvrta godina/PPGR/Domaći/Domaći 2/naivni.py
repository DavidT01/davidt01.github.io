import numpy as np

np.set_printoptions(precision = 5, suppress = True)

def opstiPolozaj(matr):
    
    A = matr[0]
    B = matr[1]
    C = matr[2]
    D = matr[3]
    m1 = [A, B, C]
    m2 = [A, B, D]
    m3 = [A, C, D]
    m4 = [B, C, D]

    if(np.linalg.det(m1) == 0 or np.linalg.det(m2) == 0 or np.linalg.det(m3) == 0 or np.linalg.det(m4) == 0):
        return False

    return True

def predstaviCetvrtu(matr):

    A = np.array([[matr[0][0], matr[1][0], matr[2][0]], [matr[0][1], matr[1][1], matr[2][1]], [matr[0][2], matr[1][2], matr[2][2]]])
    B = np.array([matr[3][0], matr[3][1], matr[3][2]])
    return np.linalg.solve(A, B)

def matricaPreslikavanja(matr, koef):

    return np.array([[koef[0] * matr[0][0], koef[1] * matr[1][0], koef[2] * matr[2][0]],
                  [koef[0] * matr[0][1], koef[1] * matr[1][1], koef[2] * matr[2][1]],
                  [koef[0] * matr[0][2], koef[1] * matr[1][2], koef[2] * matr[2][2]]])

def normiranaMatrica(matr):
    if(matr[2][2] != 1 and matr[2][2] != 0):
        matr = matr / matr[2][2]
    return matr

def ukloniMinusNulu(matr):
    for i in range (3):
        for j in range(3):
            if(matr[i][j] < 0 and matr[i][j] > -0.00001):
                matr[i][j] = 0
    return matr

def naivni(origs, imgs):

    if(not opstiPolozaj(origs)):
        return "Losi originali!"

    if(not opstiPolozaj(imgs)):
        return "Lose slike!"

    # h: A0B0C0D0 -> A'B'C'D'
    X = predstaviCetvrtu(imgs)
    h = matricaPreslikavanja(imgs, X)

    # g: A0B0C0D0 -> ABCD
    Y = predstaviCetvrtu(origs)
    g = np.linalg.inv(matricaPreslikavanja(origs, Y))

    # f: ABCD -> A'B'C'D'
    f = np.dot(h, g)

    f = normiranaMatrica(f)
    f = ukloniMinusNulu(f)
    return f

if __name__ == "__main__":
    trapez = [[-3, -1, 1], [3, -1, 1], [1, 1, 1], [-1, 1, 1], [1, 2, 3], [-8, -2, 1]] 
    pravougaonik = [[-2, -1, 1], [2, -1, 1], [2, 1, 1], [-2, 1, 1], [2, 1, 5], [-16, -5, 5]]
    print(naivni(trapez, pravougaonik))