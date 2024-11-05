'''
La classe HoughCircle implémente un accumulateur de Hough spécialisé pour détecter des cercles avec une approche optimisée.

Motivation :
Dans le cadre du projet PING², il est essentiel d’estimer la position d’une balle sur un plateau de jeu en utilisant 
un système de vision basé sur deux caméras placées dans les coins adjacents. La détection de la balle nécessite une 
méthode robuste pour distinguer sa forme circulaire des autres objets potentiellement présents sur le plateau.
En complément de caractéristiques comme la couleur et le mouvement, la transformée de Hough est ici utilisée pour
identifier la forme de la balle, caractérisée par sa circularité.

L’algorithme classique de la transformée de Hough pour les cercles est cependant coûteux en calculs, et les ressources 
nécessaires peuvent ne pas être justifiées dans notre contexte spécifique. Cette approche propose donc une optimisation
du calcul de l'accumulateur de Hough, ciblée pour notre application.

Fonctionnalité finale attendue :
Développement d'une fonction de vraisemblance capable de calculer la probabilité de présence d’un cercle de position et 
de rayon donnés sur le plateau. Cette fonction pourra être intégrée au filtre à particules pour améliorer l'estimation 
de la position de la balle.

Description de la méthode :

    Calcul des contours :
        a. Calcul du gradient de Sobel pour obtenir les composantes Gx et Gy (float32).
        b. Calcul de la magnitude du gradient G (float32).
        c. Seuil appliqué à la magnitude du gradient pour obtenir un masque binaire Gt (bool), représentant les contours
            significatifs.
        
    Calcul de l'accumulateur de Hough :
        a. Normalisation des gradients Gx et Gy pour obtenir N_Gx et N_Gy (float32), ce qui permet de connaître les directions 
            normales aux contours.
        b. Détermination des indices de l'accumulateur : Utilisation des directions normalisées pour calculer les indices 
            acc_xyr (float32) représentant les positions et le rayon des potentiels cercles.
        c. Classification des indices en "chunks" (sous-ensembles d'accumulateurs) pour optimiser la mémoire et permettre 
            un calcul ciblé. Les "chunks" sont des tableaux de coordonnées (array) correspondant aux pixels détectés.
    
    Fonction de vraisemblance likelihood(ballPose, additiveNoise) :
        a. Sélection de 4 chunks autour de la position estimée pour la balle.
        b. Calcul de la somme des distances gaussiennes des points dans ces chunks par rapport à ballPose, avec une pondération 
            pour la tolérance au bruit additive (float32).
        c. Normalisation de la réponse pour fournir une valeur de vraisemblance indicative.
        
Différences avec la méthode classique :

    Structure de l’accumulateur :
        L’accumulateur ici n’est pas une matrice de trois dimensions classique (x, y, r), mais une matrice tridimensionnelle de 
        "chunks", chacun contenant uniquement les indices des pixels pertinents. Cela permet une gestion de la mémoire plus efficace.
    
    Réduction de la mémoire : 
        En supposant que les contours occupent peu de pixels par rapport à l'image complète, cette approche utilise beaucoup moins 
        de mémoire que celle de l’accumulateur classique.
    
    Réduction de la redondance de calculs : 
    Les gradients calculés pour les contours sont réutilisés directement pour l’accumulateur sans recalculer de nouvelles informations.

    Optimisation du calcul de la transformation de Hough :
        Plutôt que d’incrémenter les valeurs dans une matrice, l'algorithme ne calcule que les coordonnées des pixels et les regroupe 
        dans des chunks. De plus, la détection des maximums dans l'accumulateur n'est pas requise, ce qui réduit encore les calculs.

    Calcul de vraisemblance ciblé :
        La fonction de vraisemblance ne traite que les chunks sélectionnés, au lieu de travailler sur l’ensemble de l’accumulateur, 
        ce qui réduit la complexité du calcul et le rend plus rapide.
'''