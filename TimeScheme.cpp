#ifndef _TIMESCHEME_CPP

#include "TimeScheme.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <complex>

using namespace std;
using namespace Eigen; 


// Constructeur

EulerScheme::EulerScheme(double initialheight, double initialTime, double initialValueX, complex<double> initialValueXX)
    : _y(initialheight), _t(initialTime), _X(initialValueX), _XX(initialValueXX) {}


// Fonction pour calculer les dérivées
void EulerScheme::systemODE(double y, double t, double X, std::complex<double> XX, double& dX, std::complex<double>& dXX)
{
    double G=50.33;
    double rho=1000;
    double nu=7.31e-7;
    double h=400e-6;
    double omega=12;
    double xi = 0.27;
    double mu= rho/nu;
    double D=1e-6;
    complex<double> i(0, 1) ;
    double S=3.14*(D/2)*(D/2);
    double delta = 12*S*mu/D;
    complex<double> omega0= i*omega/nu;
    double A = (G/(2.0*rho*nu))*(h*h/4.0 - y*y);
    complex<double> B = (G*xi/(i*rho*omega))*(1.0-cosh(omega0*y)/cosh(omega0*(h/2)));
    dX = XX.real(); 
    dXX = -delta * XX + delta * (A + B * exp(i*omega * t)); 
}

// Fonction pour avancer en temps avec la méthode d'Euler explicite
void EulerScheme::Advance() {
    double dt = 0.1;
    double dX;
    complex<double> dXX;

    // Calculer les dérivées à l'instant actuel
    systemODE(_y, _t, _X, _XX, dX, dXX);

    // Mettre à jour les variables avec la méthode d'Euler explicite
    _X += dt * dX;
    _XX += dt * dXX;

    // Mettre à jour le temps
    _t += dt;
}

// Fonction pour obtenir la valeur de X
double EulerScheme::GetX() const {
    return _X;
}

// Fonction pour obtenir la valeur de Y
double EulerScheme::GetXX() const {
    return _XX.real();
}

// Fonction pour obtenir le temps
double EulerScheme::GetTime() const {
    return _t;
}

#define _TIME_SCHEME_CPP
#endif