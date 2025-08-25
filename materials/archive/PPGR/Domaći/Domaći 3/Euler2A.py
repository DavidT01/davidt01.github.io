import numpy as np

np.set_printoptions(precision = 5, suppress = True)

def Euler2A(uglovi):

    stheta = np.sin(uglovi[1])

    if(stheta == 1):
        sRaz = np.sin(uglovi[2] - uglovi[0])
        cRaz = np.cos(uglovi[2] - uglovi[0])
        A = np.array([[0, sRaz, cRaz],
                    [0, cRaz, -sRaz],
                    [-1, 0, 0]])

    elif(stheta == -1):
        sZbir = np.sin(uglovi[2] + uglovi[0])
        cZbir = np.cos(uglovi[2] + uglovi[0])
        A = np.array([[0, -sZbir, -cZbir],
                    [0, cZbir, -sZbir],
                    [1, 0, 0]])

    else:
        cpsi = np.cos(uglovi[0])
        spsi = np.sin(uglovi[0])
        ctheta = np.cos(uglovi[1])
        cphi = np.cos(uglovi[2])
        sphi = np.sin(uglovi[2])
        A = np.array([[ctheta * cpsi, cpsi * stheta * sphi - cphi * spsi, cphi * cpsi * stheta + sphi * spsi],
                    [ctheta * spsi, cphi * cpsi + stheta * sphi * spsi, cphi * stheta * spsi - cpsi * sphi],
                    [-stheta, ctheta * sphi, ctheta * cphi]])

    return np.where(np.isclose(A, 0), 0, A)

if __name__ == "__main__":
    uglovi = np.array([np.pi/4, -np.pi/2, (7/5)*np.pi])
    print(Euler2A(uglovi))