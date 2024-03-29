#include "function.h"
#include "TimeScheme.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>

using namespace std;
using namespace Eigen;


int main(int argc, char **argv) // argc et argv : paramêtres propre au terminal

    // argc est le nombre de paramêtre de la commande :
    // "./build/tp4_fd_2d_Debug ./Data/dataSmallCase.toml" >> argc = 2
    // "./build/tp4_fd_2d_Debug ./Data/dataSmallCase.toml prout" >> argc = 3

    // argv[i] est la ième chaine de caractère du ième paramêtre dans la commande
    // "./build/tp4_fd_2d_Debug ./Data/dataSmallCase.toml prout" >> argv[2] = prout

    // std::cout << "argc = " << argc << std::endl;
    // std::cout << "argv = " << argv[1] << std::endl;

    {

        
    // --------- INITIALISATION DES VARIABLES ---------
        
    VectorXd position_init, vitesse_init;
    string file_name("results.dat");
    Particule *part = new Particule(); // créer objet de type Particule
    EulerScheme *euler = new EulerScheme(); // créer objet de type EulerScheme
        
    // temps
    double dt(0.01), t0(0.0), tfinal(10) ;
    double nbr_iteration = tfinal/dt;
        
    // conditions initiales
    position_init.resize(2); position_init(0) = 0; position_init(1) = -192.7e-6;
    vitesse_init.resize(2); vitesse_init(0) = part->fluidspeed(position_init(1), t0) ; vitesse_init(1) = 0.;

    //constantes
    double D = 10e-7 ; double mu_fluide = 7.31e-4 ; double m_part = 10e-10; double rho_fluide = 1000. ; // A vérifier
    part->Initialize(D, mu_fluide, m_part, rho_fluide);
    
        
        
    // -------- BOUCLE EN TEMPS ---------
        
    euler->Initialize(t0, dt, vitesse_init, position_init, file_name, part) ; // Initialisation
    euler->SaveSolution() ; // Sauvegarde condition initiale
    
    for (int n = 0; n < nbr_iteration; n++)
    { // Boucle en temps
        euler->AdvanceVitesse();
        euler->AdvancePosition();
        euler->SaveSolution(); // écriture de position(0), position(1), vitesse(0), vitesse(1)
    }
    

    delete part;
    delete euler;

    return 0;
}
