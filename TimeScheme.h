#ifndef _TIME_SCHEME_CPP

#include "function.h"
#include <fstream>
#include <string>
#include <complex>


class EulerScheme {

private:
    
    // Vecteur initial
    Eigen::VectorXd _vitesse_init ;
    
    
protected:
    
    // Temps initial et Temps en cours et pas de Temps
    double _y, _t, _dt;
    
    // Vecteur solution
    Eigen::VectorXd _vitesse ;
    
    // Pointeur vers le système d'EDO
    Particule* _sys;
    
    
public:
    // Constructeur
    EulerScheme();
    
    // Destructeur
    ~EulerScheme();

    // Initialisation deS différentes variables
    void Initialize(double y, double t0, double dt, Eigen::VectorXd & vitesse_init, std::string name_file, Particule* sys);

    // Enregistre la solution un fichier
    void SaveSolution();
    
    // Fonction pour avancer en temps avec la méthode d'Euler explicite
    void Advance();

};


#define _TIME_SCHEME_H
#endif
