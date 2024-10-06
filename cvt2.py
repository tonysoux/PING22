import cv2
import numpy as np

cam = cv2.VideoCapture('ball_on_board.mp4')

fgbg = cv2.createBackgroundSubtractorMOG2(history=500, varThreshold=50, detectShadows=True)
def track_moving_objects(frame, min_size=2000, max_size=4000, hist_size=180):
    fgmask = fgbg.apply(frame)
    _, fgmask = cv2.threshold(fgmask, 200, 255, cv2.THRESH_BINARY)
    contours, _ = cv2.findContours(fgmask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    ret = [cnt for cnt in contours if min_size < cv2.contourArea(cnt) < max_size]
    hist = []
    for c in ret:
        x, y, w, h = cv2.boundingRect(c)
        roi_mask = fgmask[y:y+h, x:x+w]
        roi = frame[y:y+h, x:x+w]
        hist.append(cv2.calcHist([roi], [0], roi_mask, [hist_size], [0, hist_size]))
        cv2.imshow('ROI', roi)
        cv2.imshow('Mask', roi_mask)
    
    
    return ret, hist

ball_hist = None
alpha = 0.9
def ball_histogram(frame, margin = 0.5, draw_ROI = True, draw_hist = True):
    center_x, center_y = frame.shape[1] // 2, frame.shape[0] // 2
    roi_size = (int(frame.shape[1] * margin), int(frame.shape[0] * margin))
    x_start, y_start = center_x - roi_size[0] // 2, center_y - roi_size[1] // 2
    x_end, y_end = center_x + roi_size[0] // 2, center_y + roi_size[1] // 2
    
    roi = frame[y_start:y_end, x_start:x_end]

    
    cnt,hist = track_moving_objects(roi)
    cnt = [np.array([[x + x_start, y + y_start] for x, y in c.reshape(-1, 2)]) for c in cnt]
    
    global ball_hist
    if len(cnt) == 1:
        if ball_hist is None:
            ball_hist = hist[0]
        else:
            ball_hist = alpha * ball_hist + (1 - alpha) * hist[0]
        if draw_ROI:
            cv2.rectangle(frame, (x_start, y_start), (x_end, y_end), (0, 255, 0), 2)
            cv2.drawContours(frame, cnt, -1, (0, 255, 0 ), 2)
        if draw_hist and ball_hist is not None:
            visualize_histogram(ball_hist)
    return cnt, ball_hist
    

def visualize_histogram(hist):
    """
    Fonction pour visualiser l'histogramme des teintes (H) sous forme d'image colorée.
    hist : histogramme des couleurs (canal H) calculé en espace HSV.
    """
    h_bins = hist.shape[0]  # Nombre de bins (dans ce cas, 180 bins pour la teinte)
    hist_img = np.zeros((100, h_bins, 3), dtype=np.uint8)  # Image de visualisation de l'histogramme

    # Normaliser l'histogramme pour que la hauteur corresponde à l'image
    hist = cv2.normalize(hist, hist, 0, hist_img.shape[0], cv2.NORM_MINMAX)
    # print(h_bins)
    for h in range(h_bins):
        # Déterminer la hauteur de la barre pour cette teinte
        bin_val = int(hist[h])
        # Générer la couleur HSV correspondant à la teinte h
        # print(int(h*255/h_bins),bin_val)
        color = np.array([[[int(h*255/h_bins), 255, 255]]], dtype=np.uint8)
        # Convertir de HSV à BGR pour la visualisation
        color_bgr = cv2.cvtColor(color, cv2.COLOR_HSV2RGB)
        # print(color_bgr)
        # Dessiner la barre dans l'image histogramme
        cv2.line(hist_img, (h, hist_img.shape[0]), (h, hist_img.shape[0] - bin_val), color_bgr[0, 0].tolist(), 1)

    # Afficher l'image de l'histogramme
    cv2.imshow('Histogram Visualization', hist_img)

#display it
while True:
    ret, frame = cam.read()
    if not ret:
        break
    # track_moving_objects(frame)
    ball_histogram(frame)
    
    # if bh is not None:
    #     visualize_histogram(bh)
        
    cv2.imshow('Original Frame', frame)

    # Press 'q' to exit the loop
    if cv2.waitKey(1) == ord('q'):
        break