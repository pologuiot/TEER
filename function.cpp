#ifndef _FUNCTION_CPP

#include "function.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <complex>

using namespace std;
using namespace Eigen; 

// Constructeur par défaut
Particule::Particule(VectorXd sol0, string file_name) 
{
    this->_sol.resize(2); 
    this->_sol = sol0;
    _file_out.open(file_name);
}

// Destructeur par défaut
Particule::~Particule()
{
}

// Initialise les paramêtres de temps
void Particule::Initialize(double dt)
{
    this->_dt = dt;
}


// Enregistre la solution
void Particule::SaveSolution(const double t, const VectorXd & sol)
{
  this->_file_out << t;
  for (int i = 0 ; i < _sol.rows() ; ++i)
  {
    this->_file_out << " " << _sol(i);
  }
   this->_file_out << std::endl;
}

// Calcul la vitesse du fluide 
double Particule::fluid_speed(double y)
{
    return 97.61E-6 ; 
}
double Particule::fluidspeed(double y, double t)
{
    double G=50.33;
    double rho=1000;
    double nu=7.31e-7;
    double h=400e-6;
    double omega=12;
    double xi = 0.27;
    complex<double> i(0, 1) ;
    complex<double> omega0= i*omega/nu;
    complex<double> u = (G/(2.0*rho*nu))*(h*h/4.0 - y*y) + (G*xi/(i*rho*omega))*(1.0-cosh(omega0*y)/cosh(omega0*(h/2)))*exp(i*omega*t);
    return u.real();
}

double Particule :: Force_trainée(double rho, double S, double u, double Cd)
{
    return 0;
    //return 0.5*rho*u*u*S*Cd;
}

double Particule :: Force_magnus(double rho, double S, double u, double rot,double Cm)
{
    return 0;
    //return 0.5*rho*u*rot*S*Cm;
}


// Calcul la position de la particule
void Particule::position(double t)
{
    // Cas d'une particule non pesant :
        // X(n+1) = X(n) - vitesse_fluide*dt (particule qui va de droite à gauche = comme si elle reculait)
        // Y(n+1) = Y(n) (pas de changement de hauteur )

    _sol(0) = _sol(0) - fluidspeed(_sol(1),t)*_dt ;
    _sol(1) = _sol(1) ;
    // cout << _sol(0) << endl; 

}
 


#define _FUNCTION_CPP
#endif