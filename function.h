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
    double _D, _R_vaisseau, _mu_fluide, _m_part, _rho_fluide, _g, _const_G, _h, _MomentCouette;
    // Écriture du fichier
    std::ofstream _file_out;


public :
    // Constructeur
    Particule();

    // Destructeur
    virtual ~Particule();
    
    // Initialiser le nom du fichier solution
    void InitializeFileName(const std::string file_name);
    
    // Sauvegarde la solution
    void SaveSolution(const double t, const Eigen::VectorXd & position, const Eigen::VectorXd & vitesse);

    // Initialise les paramêtres
    void Initialize(double D, double mu, double m_particule, double rho_fluide, double R_vaisseau);

    // Calcul de la vitesse du fluide
    double FluidSpeed(double y, double t); // vitesse du juste selon x
    
    // Dérivée de la vitesse du fluide à t fixé
    double FluidSpeedDerive(double y, double t); // juste selon x

    // Construction de la fonction f pour résoudre u' = f
    void BuildF(double y, double t, const Eigen::VectorXd & vitesse);
    
    // Pour récupérer _f
    const Eigen::VectorXd & GetF() const;
    
    // Calcule la vitesse de cisaillement transversal
    double VitesseCouette(double y, double Shear); //selon x

    // calcule le moment (vitesse angulaire) obtenu avec couette
    double MomentCouette(double y, double Shear); //selon z
    
    
    //Force de magnus
    //double Force_magnus(double rho, double S, double u, double rot,double Cm);

};





#define _FUNCTION_H
#endif
