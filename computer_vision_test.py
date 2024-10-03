import cv2
import numpy as np

cam = cv2.VideoCapture(0)

def preprocess(frame):
    ret = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    cv2.normalize(ret, ret, 0, 255, cv2.NORM_MINMAX) #un peu risqué
    ret = cv2.medianBlur(ret,5)
    return ret

def edge_detection(preprocessed, threshold = 10):
    Sx = cv2.Scharr(preprocessed, cv2.CV_64F, 1, 0)
    Sy = cv2.Scharr(preprocessed, cv2.CV_64F, 0, 1)
    S = cv2.magnitude(Sx,Sy)
    ei = np.argwhere(S > threshold*42).T
    Sx = Sx[ei[0],ei[1]] / S[ei[0],ei[1]]
    Sy = Sy[ei[0],ei[1]] / S[ei[0],ei[1]]
    return Sx, Sy, ei

def sobel_to_houg(Sx,Sy,ei, radius):
    acc_x_a = Sy * radius + ei[0]
    acc_x_b =-Sy * radius + ei[0]
    acc_y_a = Sx * radius + ei[1]
    acc_y_b =-Sx * radius + ei[1]
    acc_x = np.concatenate((acc_x_a, acc_x_b))
    acc_y = np.concatenate((acc_y_a, acc_y_b))
    return np.array([acc_x, acc_y])

def buid_dense(samples, in_shape, acc_size_sub = 10):
    accumulator = np.zeros((in_shape[0]//acc_size_sub,in_shape[1]//acc_size_sub), dtype=np.uint8)
    for i in range(samples.shape[1]):
        x, y = samples[0, i], samples[1, i]
        x = int(np.round(x))
        y = int(np.round(y))
        
        # Appliquer la saturation (clipping) si des limites sont spécifiées
        if x>-1 and x<in_shape[0] and y>-1 and y<in_shape[1]:
            accumulator[x//acc_size_sub, y//acc_size_sub] += 10
    return accumulator
    
while True:
    ret, frame = cam.read()
    # Détection des contours avec votre méthode
    preprocessed = preprocess(frame)
    Sx, Sy, edges = edge_detection(preprocessed)
    r = 80
    ho = sobel_to_houg(Sx, Sy, edges, r)
    acc = buid_dense(ho,(frame.shape[0],frame.shape[1]),4)
    
    
    # Affichage des résultats
    cv2.imshow('Original Frame', frame)
    cv2.imshow('preprocessed Frame', preprocessed)
    cv2.imshow('hough space at r = '+str(r), cv2.resize(acc,(frame.shape[1],frame.shape[0]),interpolation = cv2.INTER_LINEAR))

    # Press 'q' to exit the loop
    if cv2.waitKey(1) == ord('q'):
        break

# Release the capture and writer objects
cam.release()
cv2.destroyAllWindows()