import numpy as np
import imutils
import cv2
import math

class Panorama:

    # Proverava verziju OpenCV-a
    #def __init__(self):
    #    self.verzija3 = imutils.is_cv3(or_better = True)

    # Lepi dve slike u panoramu
    def zalepi(self, slike, odnos = 0.75):
		# Određivanje značajnih tačaka i karakteristika slika SIFT algoritmom
        (slikaL, slikaD) = slike
        (tackeL, karakteristikeL) = self.detektuj(slikaL)
        (tackeD, karakteristikeD) = self.detektuj(slikaD)
		# Uparivanje "istih" tačaka na slikama, određivanje matrice preslikavanja i "uljeza" pomoću RANSAC algoritma
        M = self.upariTacke(tackeD, tackeL, karakteristikeD, karakteristikeL, odnos)
        # Nedovoljno tačaka za uparivanje
        if M is None:
            return None
        (parovi, matricaPreslikavanja, tacneTacke) = M
        # Formiranje slike uparenih tačaka i određivanje najlevlje detektovane tačke
        (slikaParova, minTacka) = self.nacrtajPoklapanja(slikaD, slikaL, tackeD, tackeL, parovi, tacneTacke)
        # Određivanje konačne dužine panorame (na osnovu najlevlje tačke)
        duzinaPanorame = self.odrediDuzinu(slikaD.shape[1], slikaL.shape[1], minTacka)
        # Formiranje panorame
        pan = cv2.warpPerspective(slikaD, matricaPreslikavanja, (duzinaPanorame, slikaD.shape[0]))
        pan[0:slikaL.shape[0], 0:slikaL.shape[1]] = slikaL
        return (pan, slikaParova)

    # Detektuje značajne tačke i karakteristike slike
    def detektuj(self, slika):
    	# Prebacivanje u grayscale sliku
        siva = cv2.cvtColor(slika, cv2.COLOR_BGR2GRAY)
		# Detekcija tačaka (postupak zavisi od verzije OpenCV-a)
        #if self.verzija3:
        deskriptor = cv2.xfeatures2d.SIFT_create()
        (tacke, karakteristike) = deskriptor.detectAndCompute(slika, None)
        #else:
        #    detektor = cv2.FeatureDetector_create("SIFT")
        #    tacke = detektor.detect(siva)
        #    ekstraktor = cv2.DescriptorExtractor_create("SIFT")
        #    (tacke, karakteristike) = ekstraktor.compute(siva, tacke)
        tacke = np.float32([tacka.pt for tacka in tacke])
        return (tacke, karakteristike)

    # Uparuje značajne tačke dve slike
    def upariTacke(self, tackeD, tackeL, karakteristikeD, karakteristikeL, odnos):
		# Računanje sirovih (inicijalnih) preklapanja
        matcher = cv2.DescriptorMatcher_create("BruteForce")
        inicijalnaPoklapanja = matcher.knnMatch(karakteristikeD, karakteristikeL, 2)
        # Primena Lowe-ovog testa i računanje finalnih poklapanja
        poklapanja = []
        for m in inicijalnaPoklapanja:
            if len(m) == 2 and m[0].distance < m[1].distance * odnos:
                poklapanja.append((m[0].trainIdx, m[0].queryIdx))
        # Postupak se nastavlja ako imamo bar 4 uparene tačke
        if len(poklapanja) >= 4:
            tackeD = np.float32([tackeD[i] for (_, i) in poklapanja])
            tackeL = np.float32([tackeL[i] for (i, _) in poklapanja])
            # Traženje "uljeza" RANSAC algoritmom
            (_, tacneTacke) = cv2.findHomography(tackeD, tackeL, cv2.RANSAC, 4.0)
            # Računanje matrice preslikavanja DLT algoritmom sa normalizacijom
            matricaPreslikavanja = self.DLTsaNormalizacijom(tackeD, tackeL, tacneTacke)
            return (poklapanja, matricaPreslikavanja, tacneTacke)
        return None

    # Crta poklopljene tačke dve slike i pronalazi najlevlju poklopljenu tačku
    def nacrtajPoklapanja(self, slikaD, slikaL, tackeD, tackeL, poklapanja, tacneTacke):
    	# Spajanje slika u jednu (jedna pored druge)
        (visinaL, duzinaL) = slikaL.shape[:2]
        (visinaD, duzinaD) = slikaD.shape[:2]
        slikaParova = np.zeros((max(visinaL, visinaD), duzinaL + duzinaD, 3), dtype="uint8")
        slikaParova[0:visinaL, 0:duzinaL] = slikaL
        slikaParova[0:visinaD, duzinaL:] = slikaD
		# Obeležavanje uparenih tačaka (bez uljeza) i određivanje najlevlje tačke
        minTacka = (duzinaL + duzinaD, 0)
        for ((i, j), tacnaTacka) in zip(poklapanja, tacneTacke):
            tackaL = (int(tackeL[i][0]), int(tackeL[i][1]))
            tackaD = (int(tackeD[j][0]) + duzinaL, int(tackeD[j][1]))
            if tacnaTacka == 1:
                cv2.circle(slikaParova, tackaL, radius = 0, color = (0, 0, 255), thickness = 3)
                cv2.circle(slikaParova, tackaD, radius = 0, color = (0, 255, 0), thickness = 3)
                if(tackaL[0] < minTacka[0]):
                    minTacka = tackaL
            else:
                cv2.circle(slikaParova, tackaL, radius = 0, color = (255, 0, 0), thickness = 6)
                cv2.circle(slikaParova, tackaD, radius = 0, color = (255, 0, 0), thickness = 6)
        return (slikaParova, minTacka)
    
    # Određuje dužinu panorame na osnovu najlevlje detektovane tačke
    def odrediDuzinu(self, duzinaD, duzinaL, minTacka):
        odsecak = duzinaL - minTacka[0]
        return duzinaL + duzinaD - odsecak
    
    # Normira matricu tako da u donjem desnom uglu vrednost bude 1
    def normiranaMatrica(self, matrica):
        if(matrica[2][2] != 1 and matrica[2][2] != 0):
            matrica = matrica / matrica[2][2]
        return matrica
    
    # Određuje 2x9 matricu iz leme
    def matricaLema(self, M, N):
        M = np.array([M[0], M[1], 1])
        N = np.array([N[0], N[1], 1])
        return [[0, 0, 0, -N[2] * M[0], -N[2] * M[1], -N[2] * M[2], N[1] * M[0], N[1] * M[1], N[1] * M[2]],
            [N[2] * M[0], N[2] * M[1], N[2] * M[2], 0, 0, 0, -N[0] * M[0], -N[0] * M[1], -N[0] * M[2]]]

    # DLT algoritam
    def DLT(self, originali, slike):
        # Formiranje matrice dimenzije 2nx9 od matrica dimenzije 2x9 za svaki od n parova originala i slika
        n = len(originali)
        A = []
        for i in range(n):
            matr = self.matricaLema(originali[i], slike[i])
            A.append(matr[0])
            A.append(matr[1])
        A = np.array(A)
        # Određivanje SVD dekompozicije
        U, D, V = np.linalg.svd(A)
        # Određivanje konačne matrice preslikavanja (poslednja vrsta matrice V)
        P = V[-1].reshape(3, 3)
        return self.normiranaMatrica(P)

    # Normalizuje skup tacaka
    def normalizacija(self, tacke):
        # Translacija težišta tačaka u koordinatni početak
        n = len(tacke)
        X = sum([t[0] for t in tacke]) / n
        Y = sum([t[1] for t in tacke]) / n
        # Matrica translacije
        G = [[1, 0, -X], [0, 1, -Y], [0, 0, 1]]
        # Prosečno rastojanje
        r = 0.0
        for i in range(n):
            Xi = float(tacke[i][0]) - X
            Yi = float(tacke[i][1]) - Y
            r = r + math.sqrt(Xi**2 + Yi**2)
        r = r / float(n)
        # Skaliranje tako da prosečno rastojanje bude sqrt(2)
        S = [[float(math.sqrt(2)) / r, 0, 0], [0, float(math.sqrt(2)) / r, 0], [0, 0, 1]]
        # Konačna matrica normalizacije
        return np.dot(S, G)

    # DLT algoritam sa normalizacijom tačaka
    def DLTsaNormalizacijom(self, originali, slike, tacneTacke):
        # Računanje matrica normalizacije originala i slika
        T = self.normalizacija(originali)
        TP = self.normalizacija(slike)
        # Normalizacija "tačnih" originala i slika (bez uljeza)
        n = len(originali)
        tacniOr = []
        tacneSl = []
        for (i, tacnaTacka) in zip(range(n), tacneTacke):
            if tacnaTacka == 1:
                origTacka = np.array([originali[i][0], originali[i][1], 1])
                preslTacka = np.array([slike[i][0], slike[i][1], 1])
                origTacka = np.dot(T, origTacka).tolist()
                preslTacka = np.dot(TP, preslTacka).tolist()
                tacniOr.append([origTacka[0] / origTacka[2], origTacka[1] / origTacka[2]])
                tacneSl.append([preslTacka[0] / preslTacka[2], preslTacka[1] / preslTacka[2]])
        # DLT algoritam
        PP = self.DLT(np.array(tacniOr), np.array(tacneSl))
        # Računanje konačne matrice preslikavanja
        P = np.dot(np.dot(np.linalg.inv(TP), PP), T)
        return self.normiranaMatrica(P)
    
if __name__ == "__main__":
    # Učitavanje slika
    slikaL = cv2.imread('slikaL.jpg')
    slikaD = cv2.imread('slikaD.jpg')
    # Formiranje panorame
    panorama = Panorama()
    (rezultat, preklapanje) = panorama.zalepi([slikaL, slikaD])
    # Prikaz rezultata
    cv2.imshow("Prva slika", slikaL)
    cv2.waitKey(0)
    cv2.imshow("Druga slika", slikaD)
    cv2.waitKey(0)
    cv2.imshow("Tacke preklapanja", preklapanje)
    cv2.waitKey(0)
    cv2.imshow("Panorama", rezultat)
    cv2.waitKey(0)
    cv2.destroyAllWindows()