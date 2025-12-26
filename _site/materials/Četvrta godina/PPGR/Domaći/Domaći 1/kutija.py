import cv2 as cv2
import numpy as np

temena = []

def beskonacnaTacka(t1, t2, t3, t4, t5, t6):
    
    s12 = np.cross(t1, t2)
    s34 = np.cross(t3, t4)
    s56 = np.cross(t5, t6)
    
    y1 = np.cross(s12, s34)
    y2 = np.cross(s34, s56)
    y3 = np.cross(s12, s56)
    y1 = np.array([y1[0] / y1[2], y1[1] / y1[2]])
    y2 = np.array([y2[0] / y2[2], y2[1] / y2[2]])
    y3 = np.array([y3[0] / y3[2], y3[1] / y3[2]])
    
    y = (y1 + y2 + y3) / 3
    return np.array([y[0], y[1], 1])

def osmoteme():
    
    t1 = temena[0]
    t2 = temena[1]
    t3 = temena[2]
    t5 = temena[3]
    t6 = temena[4]
    t7 = temena[5]
    t8 = temena[6]
    
    y = beskonacnaTacka(t2, t1, t6, t5, t7, t8)
    yt3 = np.cross(y, t3)
    
    x = beskonacnaTacka(t7, t3, t6, t2, t5, t1)
    xt8 = np.cross(x, t8)
    
    t4 = np.cross(yt3, xt8)
    return [int(t4[0] / t4[2]), int(t4[1] / t4[2])]

def klik(event, x, y, fl, pm):

    if event == cv2.EVENT_RBUTTONDOWN:
        t4 = osmoteme()
        print(t4)
        #cv2.putText(slika, '(' + str(t4[0]) + ', ' + str(t4[1]) + ')', (t4[0], t4[1]), cv2.FONT_HERSHEY_DUPLEX, 0.7, (0, 255, 0), 1)
        cv2.putText(slika, '.', (t4[0], t4[1]), cv2.FONT_HERSHEY_DUPLEX, 0.7, (0, 255, 0), 1)
        cv2.imshow('Kutija', slika)

    if event == cv2.EVENT_LBUTTONDOWN:
        temena.append(np.array([x, y, 1]))
        cv2.putText(slika, '(' + str(x) + ', ' + str(y) + ')', (x, y), cv2.FONT_HERSHEY_DUPLEX, 0.7, (0, 0, 255), 1)
        cv2.imshow('Kutija', slika)

if __name__ == "__main__":
    
    slika = cv2.imread('desna.jpg')
    cv2.imshow('Kutija', slika)
    cv2.setMouseCallback("Kutija", klik)
    cv2.waitKey(0)