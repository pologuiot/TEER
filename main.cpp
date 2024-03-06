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

    VectorXd sol0;
    string file_name; 
    double dt, tfinal, t;  
    int nbr_iteration;

    // RECUPERER LES DONNEES INITIALES

    sol0.resize(2); sol0(0) = 0; sol0(1) = -392.8e-6;
    file_name = "position_particule_1.dat" ;
    dt = 0.01 ; t = 0.0 ; tfinal = 10 ;
    nbr_iteration = tfinal/dt;



    // INITIALISER LES PARTICULES

    Particule *part = new Particule(sol0,file_name); 
    part->Initialize(dt);
    part->SaveSolution(t, sol0);

    // vitesse du fluide 
    

    double u = part->fluidspeed(-192.7e-6, 5.5);
    cout <<"vitesse du fluide a t=5.5s = "<< u*1e6 << endl;

    // POUR T de 0 à Tfinal d'un pas de dt : Calculer la position de toutes les particules 
    
    for (int i=0; i<nbr_iteration; i++) 
    {
        t = t + dt ; 
        part->position(t) ;
        part->SaveSolution(t, sol0);
    }

    double initialHeight = -150e-6;
    double initialTime = 0;
    double initialValueX = 0;
    std::complex<double> initialValueXX = 97e-6;

    double totalSimulationTime = 10;
    double timeStep = 0.1;
    EulerScheme EulerScheme(initialHeight, initialTime, initialValueX, initialValueXX);
    std::ofstream outputFile("resultats_simulation.dat");

    while (EulerScheme.GetTime() <= totalSimulationTime) 
    {
        EulerScheme.Advance();
        outputFile << EulerScheme.GetTime() << " " << EulerScheme.GetX() << " " << EulerScheme.GetXX() << std::endl;
    }
    outputFile.close();

    delete part; 

    return 0; 
}