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
        
    VectorXd position;
    string file_name;
    double dt, tfinal, t;
    int nbr_iteration;

    position.resize(2); position(0) = 0; position(1) = -192.7e-6; //position (x,y) de la particule
    dt = 0.01 ; t = 0.0 ; tfinal = 10 ;
    nbr_iteration = tfinal/dt;
        
    double initialTime = 0;
    std::complex<double> initialValueVx = 97e-6;
        
    double totalSimulationTime = 10;
    double timeStep = 0.1;

    Particule *part = new Particule(position,file_name); // créer objet de type Particule
    part->Initialize(dt);

        
        
    //  --------- TEST VITESSE FLUIDE A t = 5.5 ---------
    
    double u = part->fluidspeed(-192.7e-6, 5.5);
    cout << "vitesse du fluide a t=5.5s = " << u*1e6 << endl;
        
        

    // Pour T de 0 à Tfinal d'un pas de dt : Calculer la position de toutes les particules


    EulerScheme EulerScheme(position, initialTime, initialValueVx);
    std::ofstream outputFile("resultats_simulation.dat");

//    while (EulerScheme.GetTime() <= totalSimulationTime)
//    {
//        EulerScheme.Advance();
//        outputFile << EulerScheme.GetTime() << " " << EulerScheme.GetX() << " " << EulerScheme.GetVx() << std::endl;
//    }
        
        
    outputFile.close();

    delete part;

    return 0;
}
