import numpy as np
from numpy import linalg
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import plotly.graph_objects as go
import plotly.express as px

# Pomera koordinatni sistem u gornji desni ugao
def piksel(koord):
    return np.array([1, -1, -1]) * (np.array([1600, 0, 0]) - koord)

# Računa fundamentalnu matricu F, M'2 @ F @ M'1 = 0
def fundamentalnaMatrica(leve, desne):

    A = []
    for i in range(len(leve)):
        A.append([leve[i][0] * desne[i][0], leve[i][1] * desne[i][0], leve[i][2] * desne[i][0],
                  leve[i][0] * desne[i][1], leve[i][1] * desne[i][1], leve[i][2] * desne[i][1],
                  leve[i][0] * desne[i][2], leve[i][1] * desne[i][2], leve[i][2] * desne[i][2]])
    A = np.array(A)

    _, _, V = np.linalg.svd(A)

    F = V[-1].reshape(3, 3)
    
    return ispravi(F)

# Popravlja fundamentalnu matricu F
def ispravi(F):

    U, D, V = np.linalg.svd(F)

    DD = np.diag(np.diag([1, 1, 0]) @ D)

    return U @ DD @ V

# Formira matricu kalibracije kamere K
def matricaKalibracije():

    return np.array([[1155, 0, 800], [0, 1155, 600], [0, 0, 1]])

# Računa osnovnu matricu E = K^T * F * K
def osnovnaMatrica(F):

    K = matricaKalibracije()
    return K.T @ F @ K

# Vrši dekompoziciju osnovne matrice E = EC*A
def dekompozicija(E):

    Q0 = np.array([[0, -1, 0], [1, 0, 0], [0, 0, 1]])
    E0 = np.array([[0, 1, 0], [-1, 0, 0], [0, 0, 0]])

    U, _, V = np.linalg.svd(E)

    EC = U @ E0 @ U.T
    A = U @ Q0 @ V

    return EC, A

# Računa matrice kamera T1 i T2
def matriceKamera(A, C):

    # T2 = K | 0
    K = matricaKalibracije()
    T2 = (np.concatenate((K.T, np.array([[0, 0, 0]])), axis = 0)).T

    # Pozicija prve kamere u koord. sistemu druge kamere
    C1 = -A.T @ C

    # T1 = [K @ A.T] | [K @ C1]
    T1 = (np.concatenate(((K @ A.T).T, np.array([K @ C1])), axis = 0)).T

    return T1, T2

# Pretvara homogene koordinate u afine
def afine(M):

    return np.array([M[0] / M[3], M[1] / M[3], M[2] / M[3]])

# Trianguliše tačku na osnovu njenih projekcija M1 i M2 i matrica kamera T1 i T2
def triangulacija(T1, T2, M1, M2):

    jedn = np.array([M1[1] * T1[2] - M1[2] * T1[1],
                     -M1[0] * T1[2] + M1[2] * T1[0],
                     M2[1] * T2[2] - M2[2] * T2[1],
                     -M2[0] * T2[2] + M2[2] * T2[0]])

    _, _, V = np.linalg.svd(jedn)

    return afine(V[-1])

# Plotuje 3D scenu
def matplotlib(tacke):

    # Crta 3D figuru čije su stranice prosleđene
    def nacrtaj(stranice, boja):

        for i in range(len(stranice)):
            ax.plot([tacke[stranice[i][0]][0], tacke[stranice[i][1]][0]],
                    [tacke[stranice[i][0]][1], tacke[stranice[i][1]][1]],
                    [tacke[stranice[i][0]][2], tacke[stranice[i][1]][2]], color = boja)

    fig = plt.figure("Scena")
    fig.set_figheight(7)
    fig.set_figwidth(10)
    fig.subplots_adjust(top = 1, bottom = 0, left = 0, right = 1)
    ax = plt.axes(projection = '3d')
    ax.set_xlabel("X", color = 'g')
    ax.set_ylabel("Y", color = 'g')
    ax.set_zlabel("Z", color = 'g')

    # Tačke
    for i in range(len(tacke)):
        oznaka, broj, boja = 'P', i + 1, 'r'
        if i >= 9 and i < 13:
            oznaka, broj, boja = 'Q', broj % 9, 'm'
        if i >= 13:
            oznaka, broj, boja = 'R', broj % 13, 'b'
        ax.text(tacke[i][0], tacke[i][1], tacke[i][2], oznaka + str(broj), color = boja, fontsize = 10)
        ax.plot(tacke[i][0], tacke[i][1], tacke[i][2], boja + '.')

    kocka = np.array([[0, 1], [0, 3], [1, 2], [2, 3], [0, 4], [1, 5], [2, 6], [3, 7], [4, 5], [5, 6], [6, 7], [7, 4]])
    nacrtaj(kocka, 'r')

    piramida = np.array([[9, 10], [9, 11], [9, 12], [10, 11], [10, 12], [11, 12]])
    nacrtaj(piramida, 'm')

    kvadar = np.array([[13, 14], [13, 16], [14, 15], [15, 16], [13, 17], [14, 18], [15, 19], [16, 20], [17, 18], [18, 19], [19, 20], [20, 17]])
    nacrtaj(kvadar, 'b')

    plt.show()
    
def plotly(tacke):

    kocka = np.array([[0, 1], [0, 3], [1, 2], [2, 3], [0, 4], [1, 5], [2, 6], [3, 7], [4, 5], [5, 6], [6, 7], [7, 4]])
    piramida = np.array([[9, 10], [9, 11], [9, 12], [10, 11], [10, 12], [11, 12]])
    kvadar = np.array([[13, 14], [13, 16], [14, 15], [15, 16], [13, 17], [14, 18], [15, 19], [16, 20], [17, 18], [18, 19], [19, 20], [20, 17]])

    xdata, ydata, zdata = (np.transpose(tacke))[0], (np.transpose(tacke))[1], (np.transpose(tacke))[2]
    
    def dodajFiguru(figura):
        
        for i in range(len(figura)):
            podaci.append(go.Scatter3d(x = [xdata[figura[i][0]], xdata[figura[i][1]]],
                                       y = [ydata[figura[i][0]], ydata[figura[i][1]]],
                                       z = [zdata[figura[i][0]], zdata[figura[i][1]]]))

    podaci = []
    dodajFiguru(kocka)
    dodajFiguru(piramida)
    dodajFiguru(kvadar)

    fig = go.Figure(data = podaci)
    fig.update_layout(showlegend = False)
    fig.write_html("C:/Users/korisnik/Desktop/Faks/2023 2024/PPGR/Domaći/Domaći 5/scena.html",
                   include_plotlyjs = 'cdn', default_width = '800px', default_height = '600px', full_html = False)
    fig.show()

if __name__ == "__main__":

    # Kocka (P), piramida (Q) i kvadar (R)
    p1l = np.array([404, 460, 1])
    p2l = np.array([622, 526, 1])
    p3l = np.array([502, 712, 1])
    p4l = np.array([262, 634, 1])
    p5l = np.array([450, 609, 1])
    p6l = np.array([641, 671, 1])
    p7l = np.array([539, 848, 1])
    p8l = np.array([332, 776, 1])
    p9l = np.array([434, 534, 1])
    q1l = np.array([1203, 906, 1])
    q2l = np.array([1381, 692, 1])
    q3l = np.array([1056, 624, 1])
    q4l = np.array([1310, 552, 1])
    r1l = np.array([810, 130, 1])
    r2l = np.array([989, 230, 1])
    r3l = np.array([747, 385, 1])
    r4l = np.array([565, 258, 1])
    r5l = np.array([808, 218, 1])
    r6l = np.array([975, 316, 1])
    r7l = np.array([745, 471, 1])
    r8l = np.array([574, 350, 1])

    p1r = np.array([434, 344, 1])
    p2r = np.array([591, 441, 1])
    p3r = np.array([405, 574, 1])
    p4r = np.array([247, 459, 1])
    p5r = np.array([469, 504, 1])
    p6r = np.array([613, 593, 1])
    p7r = np.array([452, 724, 1])
    p8r = np.array([309, 616, 1])
    p9r = np.array([426, 413, 1])
    q1r = np.array([1054, 961, 1])
    q2r = np.array([1345, 813, 1])
    q3r = np.array([1026, 655, 1])
    q4r = np.array([1231, 617, 1])
    r1r = np.array([963, 145, 1])
    r2r = np.array([1100, 263, 1])
    r3r = np.array([790, 358, 1])
    r4r = np.array([678, 213, 1])
    r5r = np.array([953, 231, 1])
    r6r = np.array([1078, 350, 1])
    r7r = np.array([786, 446, 1])
    r8r = np.array([680, 303, 1])

    leve8 = piksel(np.array([r1l, r2l, r3l, r4l, q1l, q2l, q3l, q4l]))
    desne8 = piksel(np.array([r1r, r2r, r3r, r4r, q1r, q2r, q3r, q4r]))

    F = fundamentalnaMatrica(leve8, desne8)

    E = osnovnaMatrica(F)

    EC, A = dekompozicija(E)
    C = np.array([EC[2][1], EC[0][2], EC[1][0]])
    
    T1, T2 = matriceKamera(A, C)

    leve = piksel(np.array([p1l, p2l, p3l, p4l, p5l, p6l, p7l, p8l, p9l, q1l, q2l, q3l, q4l, r1l, r2l, r3l, r4l, r5l, r6l, r7l, r8l]))
    desne = piksel(np.array([p1r, p2r, p3r, p4r, p5r, p6r, p7r, p8r, p9r, q1r, q2r, q3r, q4r, r1r, r2r, r3r, r4r, r5r, r6r, r7r, r8r]))
    
    tacke = []
    for i in range(len(leve)):
        tacke.append(triangulacija(T1, T2, leve[i], desne[i]))
    tacke = np.array(tacke)

    print('Fundamentalna matrica F:\n', F, '\n\nOsnovna matrica E:\n', E, '\n\nMatrica Ec:\n', EC, '\n\nMatrica A:\n', A,
          '\n\nMatrica leve kamere T1:\n', T1, '\n\nMatrica desne kamere T2:\n', T2, '\n\n3D koordinate tacaka:\n', tacke)

    matplotlib(tacke)
    plotly(tacke)