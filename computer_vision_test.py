# import cv2
# import numpy as np
# from scipy.sparse import coo_matrix
# from scipy.sparse import csr_matrix
# from sklearn.neighbors import KernelDensity


# # Open the default camera
# cam = cv2.VideoCapture(0)

# # Get the default frame width and height
# frame_width = int(cam.get(cv2.CAP_PROP_FRAME_WIDTH))
# frame_height = int(cam.get(cv2.CAP_PROP_FRAME_HEIGHT))


# import numpy as np
# import cv2
# from scipy.sparse import csr_matrix

# def prepare_sobel(gray_frame):
#     edges = cv2.Canny(gray_frame,100,200)
#     non_zero_edges_indices = np.nonzero(edges)
#     sobel_x = cv2.Sobel(gray_frame, cv2.CV_64F, 1, 0, ksize=5)  # Gradient en X
#     sobel_y = cv2.Sobel(gray_frame, cv2.CV_64F, 0, 1, ksize=5)  # Gradient en Y
#     sobel = coo_matrix((sobel_y[non_zero_edges_indices],sobel_x[non_zero_edges_indices]),non_zero_edges_indices)
#     magnitude_inv = (sobel[0].power(2) + sobel[1].power(2)).power(-0.5)
#     sobel = sobel.multiply(magnitude_inv)

#     return sobel

# def hough(dx, dy, edges, radius):
#     edges_indices_y, edges_indices_x = np.nonzero(edges)
    
#     acc_x_a = dx[edges_indices_y, edges_indices_x] * radius + edges_indices_x
#     acc_x_b =-dx[edges_indices_y, edges_indices_x] * radius + edges_indices_x
#     acc_y_a = dy[edges_indices_y, edges_indices_x] * radius + edges_indices_y
#     acc_y_b =-dy[edges_indices_y, edges_indices_x] * radius + edges_indices_y
#     acc_x = np.concatenate((acc_x_a, acc_x_b),axis=1)
#     acc_y = np.concatenate((acc_y_a, acc_y_b),axis=1)
#     return np.asarray(np.concatenate((acc_x, acc_y)))
#     # acc_x = np.clip(acc_x, 0, frame.shape[1] - 1)
#     # acc_y = np.clip(acc_y, 0, frame.shape[0] - 1)
#     binary_image = np.zeros(frame.shape, dtype=np.uint8)
#     binary_image[acc_y.astype(int), acc_x.astype(int)] = 255
#     return binary_image
    
#     # if acc_xy.shape[1] < 1 :
#     #     return frame
    
#     # kde = KernelDensity(bandwidth=0.1*r, kernel='gaussian')  # Ajuster le paramètre 'bandwidth'
#     # kde.fit(acc_xy.T)

#     # image_height, image_width = frame.shape[0]//10, frame.shape[1]//10

#     # # Créer une grille de points couvrant l'image
#     # x = np.linspace(0, image_width, image_width)
#     # y = np.linspace(0, image_height, image_height)
#     # xx, yy = np.meshgrid(x, y)
#     # grid_points = np.vstack([xx.ravel(), yy.ravel()]).T

#     # # Evaluer la densité sur cette grille
#     # density_log = kde.score_samples(grid_points)
#     # density = np.exp(density_log)  # Convertir la densité de l'échelle log
#     # density = density.reshape((image_height, image_width))
#     # density = cv2.resize(density, (frame.shape[1],frame.shape[0]), interpolation = cv2.INTER_NEAREST)
#     # # Normaliser la densité pour avoir des valeurs entre 0 et 255 (pour afficher en niveaux de gris)
#     # density_image_normalized = cv2.normalize(density, None, 0, 255, cv2.NORM_MINMAX)
#     # density_image_normalized = density_image_normalized.astype(np.uint8)
#     # print(density_image_normalized.shape)
#     # return density_image_normalized

# while True:
#     ret, frame = cam.read()

#     gray_image = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
#     edges = cv2.Canny(gray_image,100,200)
#     sobel_x = cv2.Sobel(gray_image, cv2.CV_64F, 1, 0, ksize=5)  # Gradient en X
#     sobel_y = cv2.Sobel(gray_image, cv2.CV_64F, 0, 1, ksize=5)  # Gradient en Y
#     sobel_x = coo_matrix(cv2.bitwise_and(sobel_x, sobel_x, mask=edges))
#     sobel_y = coo_matrix(cv2.bitwise_and(sobel_y, sobel_y, mask=edges))
#     magnitude_inv = (sobel_x.power(2) + sobel_y.power(2)).power(-0.5)
#     sobel_x = sobel_x.multiply(magnitude_inv)
#     sobel_y = sobel_y.multiply(magnitude_inv)
#     masked_image = cv2.bitwise_and(gray_image, gray_image, mask=edges)

#     # gray_image[80:280, 150:330] = hough(sobel_x,sobel_y,20,edges).toarray().astype(int)
#     cv2.imshow('Camera', hough(sobel_x,sobel_y,50,edges,frame))
    
#     # Press 'q' to exit the loop
#     if cv2.waitKey(1) == ord('q'):
#         break

# # Release the capture and writer objects
# cam.release()
# cv2.destroyAllWindows()

import cv2
import numpy as np
from scipy.sparse import coo_matrix
from scipy.sparse import csr_matrix
from sklearn.neighbors import KernelDensity


# Open the default camera
cam = cv2.VideoCapture(0)

# Get the default frame width and height
frame_width = int(cam.get(cv2.CAP_PROP_FRAME_WIDTH))
frame_height = int(cam.get(cv2.CAP_PROP_FRAME_HEIGHT))


import numpy as np
import cv2
from scipy.sparse import coo_matrix

cam = cv2.VideoCapture(0)

def prepare_sobel(gray_frame):
    edges = cv2.Canny(gray_frame,100,200)
    non_zero_edges_indices = np.array(np.nonzero(edges))
    sobel_x = cv2.Sobel(gray_frame, cv2.CV_64F, 1, 0, ksize=5)  # Gradient en X
    sobel_y = cv2.Sobel(gray_frame, cv2.CV_64F, 0, 1, ksize=5)  # Gradient en Y
    sobel_x = coo_matrix(sobel_x[non_zero_edges_indices[1],non_zero_edges_indices[0]],non_zero_edges_indices)
    sobel_y = coo_matrix(sobel_y[non_zero_edges_indices[1],non_zero_edges_indices[0]],non_zero_edges_indices)
    return sobel_x, sobel_y

while True:
    ret, frame = cam.read()

    gray_image = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    print(prepare_sobel(gray_image).shape)
    
    if cv2.waitKey(1) == ord('q'):
        break

cam.release()
cv2.destroyAllWindows()
