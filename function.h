#ifndef _FUNCTION_H
#include <fstream>
#include <string>
#include "/net/netud/m/lmagnier001/TEER/libraries/eigen/Eigen/Sparse" // mettre son propre chemin vers le dossier TER
#include "/net/netud/m/lmagnier001/TEER/libraries/eigen/Eigen/Dense" // idem


class Particule
{
protected :
    // Fonction f
    Eigen::VectorXd _f;
    // Constantes
    double _D, _mu_fluide, _m_part, _rho_fluide, _g, _const_G, _h ;
    // Écriture du fichier
    std::ofstream _file_out;


public :
    // Constructeur
    Particule();

    // Destructeur
    virtual ~Particule();
    
    // Initialiser le nom du fichier solution
    void InitializeFileName(const std::string file_name);
    
    // Pour récupérer _f
    const Eigen::VectorXd &  GetF()  const;
    
    // Sauvegarde la solution
    void SaveSolution(const double t, const Eigen::VectorXd & vitesse);

    // Initialise les paramêtres
    void Initialize(double D, double mu, double m_particule, double rho_fluide);

    // Calcul de la vitesse du fluide
    double fluidspeed(double y, double t);

    // Force de trainée
    double Force_trainée(double rho, double S, double u, double Cd);

    //Force de magnus
    double Force_magnus(double rho, double S, double u, double rot,double Cm);

    
    // Construction de la fonction f pour résoudre u' = f
    void BuildF(double y, double t, const Eigen::VectorXd & vitesse);

};

#define _FUNCTION_H
#endif
