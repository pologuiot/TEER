#ifndef _TIME_SCHEME_CPP

#include "function.h"
#include <fstream>
#include <string>
#include <complex>


class EulerScheme {

private:
    double _y;
    double _t;
    double _X;
    std::complex<double> _XX;

    // Fonction pour calculer les dérivées
    void systemODE(double y, double t, double X, std::complex<double> XX, double& dX, std::complex<double>& dXX);


public:
    // Constructeur
    EulerScheme(double initialheight, double initialTime, double initialValueX, std::complex<double> initialValueXX);


    // Fonction pour avancer en temps avec la méthode d'Euler explicite
    void Advance();

    // Fonction pour obtenir la valeur de X
    double GetX() const;

    // Fonction pour obtenir la valeur de XX
    double GetXX() const;

    // Fonction pour obtenir le temps
    double GetTime() const;
};


#define _TIME_SCHEME_H
#endif
