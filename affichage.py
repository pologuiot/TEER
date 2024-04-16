import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import math


nom_fichier = "results.dat"

# Fonction pour lire les données à partir du fichier
import math

def lire_donnees(nom_fichier):
    temps = []
    positions_x = []
    positions_y = []
    theta = []

    with open(nom_fichier, 'r') as file:
        for line in file:
            # Séparer la ligne en valeurs individuelles
            values = line.split()
            # Convertir les valeurs en float
            t, pos_x, pos_y, _, _, angle = map(float, values[:6])
            temps.append(t)
            positions_x.append(pos_x)
            positions_y.append(pos_y)
            # Convertir l'angle de degrés en radians et l'ajouter à la liste theta
            theta.append(math.radians(angle))

    return temps, positions_x, positions_y, theta


# Lecture des données à partir du fichier
temps, positions_x, positions_y, theta = lire_donnees(nom_fichier)

# Fonction de mise à jour de l'animation
def update(frame):
    plt.gca().clear()  # Effacer uniquement la trame actuelle
    
    # Tracer le premier point en rouge
    plt.scatter(positions_x[frame], positions_y[frame], color='blue', label='Position de la particule', s=100)  
    
    # Calculer la position du deuxième point (centré sur le premier)
    offset = 0.00000001 
    center_x = positions_x[frame] + offset * math.cos(theta[frame])
    center_y = positions_y[frame] + offset * math.sin(theta[frame])
    # Tracer le deuxième point centré sur le premier en bleu
    plt.scatter(center_x, center_y, color='red', label='Point M', s=50)  
    
    plt.xlim(min(positions_x), max(positions_x))  # Fixer les limites de l'axe x
    plt.ylim(min(positions_y), max(positions_y))  # Fixer les limites de l'axe y
    
    plt.xlabel('Position sur l\'axe x')
    plt.ylabel('Position sur l\'axe y')
    plt.title('Position de la particule')
    plt.legend()



# Création de l'animation
animation = FuncAnimation(plt.gcf(), update, frames=len(temps), interval=100, repeat=False)

# Affichage de l'animation
plt.show()
