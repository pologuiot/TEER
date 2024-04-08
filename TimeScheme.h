#ifndef _TIME_SCHEME_CPP

#include "function.h"
#include <fstream>
#include <string>
#include <complex>


class TimeScheme {

private:
    
    // Vecteur initial
    Eigen::VectorXd _vitesse_init, _position_init;
    
    
protected:
    
    // Temps initial et Temps en cours et pas de Temps
    double _t, _dt;
    
    // Vecteurs solutions
    Eigen::VectorXd _v_poseuille, _v_couette, _moment, _position;
    
    //coefficient shear
    double _Shear;
    
    // Pointeur vers le système d'EDO
    Particule* _sys;
    
    
public:
    // Constructeur
    TimeScheme();
    
    // Destructeur
    ~TimeScheme();

    // Initialisation deS différentes variables
    void Initialize(double t0, double dt, Eigen::VectorXd & vitesse_init, Eigen::VectorXd & position_init, std::string name_file, Particule* sys);

    // Enregistre la solution un fichier
    void SaveSolution();
    
    // Fonction pour avancer en temps la vitesse de la particule pesante avec Euler explicite
    void AdvanceVitessePoiseuille();
    
    // Fonction pour avancer en temps la vitesse de couette (cisaillement)
    void AdvanceVitesseCouette();
    
    // Mise à jour du moment
    void AdvanceMomentCouette();
    
    // Mise à jour de la position de la particule
    void AdvancePosition();
    
    // Calcul du coefficient S (shear)
    void AdvanceShear();

};


#define _TIME_SCHEME_H
#endif
