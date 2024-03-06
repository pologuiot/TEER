import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

nom_fichier = "../C++/position_particule_1.dat"

# Fonction pour lire les données à partir du fichier
def lire_donnees(nom_fichier):
    temps = []
    positions_x = []
    positions_y = []

    with open(nom_fichier, 'r') as file:
        for line in file:
            t, pos_x, pos_y = map(float, line.split())
            temps.append(t)
            positions_x.append(pos_x)
            positions_y.append(pos_y)

    return temps, positions_x, positions_y

# Fonction de mise à jour de l'animation
def update(frame):
    plt.clf()
    plt.plot(positions_x[:frame], positions_y[:frame], label='Trajectoire de la particule')
    plt.xlabel('Position sur l\'axe x')
    plt.ylabel('Position sur l\'axe y')
    plt.title('Trajectoire de la particule')
    plt.legend()

# Lecture des données à partir du fichier
temps, positions_x, positions_y = lire_donnees(nom_fichier)

# Création de l'animation
animation = FuncAnimation(plt.gcf(), update, frames=len(temps), interval=100, repeat=False)

# Affichage de l'animation
plt.show()
