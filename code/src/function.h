#ifndef _FUNCTION_H
#include <fstream>
#include <string>
#include "/home/paul/2A/TER/libraries/eigen/Eigen/Sparse" // mettre son propre chemin vers le dossier TER
#include "/home/paul/2A/TER/libraries/eigen/Eigen/Dense" // idem


class Particule 
{
protected :
    // Temps initial et Temps en cours et pas de Temps
    double _t0, _t, _dt;
    // Vecteur initial et vecteur solution
    Eigen::VectorXd _sol;
    // Écriture du fichier
    std::ofstream _file_out ;


public :
    // Constructeur
    Particule(Eigen::VectorXd sol0, std::string file_name);

    // Destructeur
    // Obligatoire dès qu'on a une fonction virtuelle !
    virtual ~Particule();

    // Initialise les paramêtres de temps
    void Initialize(double dt);

    // Calcul de la vitesse du fluide
    double fluid_speed(double y);

    
    // Calcul la position de la particule
    void position();

    // Sauvegarde la solution
    void SaveSolution(const double t, const Eigen::VectorXd & sol);

    // pour récupérer _dt 
    double Get_dt() const{return _dt;}

};





#define _FUNCTION_H
#endif