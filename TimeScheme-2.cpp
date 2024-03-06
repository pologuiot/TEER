#ifndef _TIMESCHEME_CPP

#include "TimeScheme.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <complex>

using namespace std;
using namespace Eigen;


// -------- CONSTRUCTEUR --------

EulerScheme::EulerScheme(Eigen::VectorXd position, double initialTime, std::complex<double> initialValueVx)
    : _position(position), _t(initialTime), _Vx(initialValueVx) {}


// -------- FONCTIONS RECUPERATION DONNEES --------

// Fonction pour obtenir la valeur de X
double EulerScheme::GetX() const {
    return _position(0);
}

// Fonction pour obtenir la valeur de Vx
double EulerScheme::GetVx() const {
    return _Vx.real();
}

// Fonction pour obtenir le temps
double EulerScheme::GetTime() const {
    return _t;
}


// -------- FONCTIONS CALCULATOIRES --------

// Fonction pour calculer les dérivées
void EulerScheme::systemODE(Eigen::VectorXd position, double t, std::complex<double> Vx, double& dX, std::complex<double>& dVx)
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
    double A = (G/(2.0*rho*nu))*(h*h/4.0 - position(1)*position(1));
    complex<double> B = (G*xi/(i*rho*omega))*(1.0-cosh(omega0*position(1))/cosh(omega0*(h/2)));
    dX = Vx.real();
    dVx = -delta * Vx + delta * (A + B * exp(i*omega * t));
}

// Fonction pour avancer en temps avec la méthode d'Euler explicite
void EulerScheme::Advance() {
    double dt = 0.1;
    double dX;
    complex<double> dVx;

    // Calculer les dérivées à l'instant actuel
    systemODE(_position, _t, _Vx, dX, dVx);

    // Mettre à jour les variables avec la méthode d'Euler explicite
    _position(1) += dt * dX;
    _Vx += dt * dVx;

    // Mettre à jour le temps
    _t += dt;
}


#define _TIME_SCHEME_CPP
#endif
