import cv2 as cv2
import numpy as np

def osmoteme(temena):
    
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
        y = np.array([y[0], y[1], 1])
        return y
    
    for t in temena:
        t.append(1)
    t5 = np.array(temena[0])
    t6 = np.array(temena[1])
    t7 = np.array(temena[2])
    t8 = np.array(temena[3])
    t1 = np.array(temena[4])
    t2 = np.array(temena[5])
    t3 = np.array(temena[6])
    
    y = beskonacnaTacka(t2, t1, t6, t5, t7, t8)
    yt3 = np.cross(y, t3)
    
    x = beskonacnaTacka(t7, t3, t6, t2, t5, t1)
    xt8 = np.cross(x, t8)
    
    t4 = np.cross(yt3, xt8)
    return [int(t4[0] / t4[2]), int(t4[1] / t4[2])]

def main():
    
    temena = [[32, 70], [195, 144], [195, 538], [30, 307], [251, 40], [454, 78], [455, 337]]
    #print(osmoteme(temena))
    
    temena = [[1347, 1056], [1189, 1204], [963, 1047], [1436, 850], [1255, 1001], [993, 841], [1182, 709]]
    print(osmoteme(temena))
    
main()