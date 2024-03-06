#ifndef _TIME_SCHEME_CPP

#include "function.h"
#include <fstream>
#include <string>
#include <complex>


class EulerScheme {

private:
    Eigen::VectorXd _position ;
    double _t;
    std::complex<double> _Vx;
    
    // Fonction pour calculer les dérivées
    void systemODE(Eigen::VectorXd position, double t, std::complex<double> Vx, double& dX, std::complex<double>& dVx);

    
public:
    // Constructeur
    EulerScheme(Eigen::VectorXd position, double initialTime, std::complex<double> initialValueVx);


    // Fonction pour avancer en temps avec la méthode d'Euler explicite
    void Advance();

    // Fonction pour obtenir la valeur de x
    double GetX() const;

    // Fonction pour obtenir la valeur de Vx
    double GetVx() const;

    // Fonction pour obtenir le temps
    double GetTime() const;
};


#define _TIME_SCHEME_H
#endif
