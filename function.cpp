#ifndef _FUNCTION_CPP

#include "function.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <complex>

using namespace std;
using namespace Eigen;


// -------- CONSTRUCTEURS --------

// Constructeur par défaut
Particule::Particule(VectorXd position, string file_name)
{
    this->_position.resize(2);
    this->_position = position;
    _file_out.open(file_name);
}

// Destructeur par défaut
Particule::~Particule()
{
}


// -------- FONCTIONS --------

// Initialise les paramêtres de temps
void Particule::Initialize(double dt)
{
    this->_dt = dt;
}


// Enregistre la position (x,y) dans un fichier
void Particule::SaveSolution(const double t, const VectorXd & position)
{
  this->_file_out << t;
  for (int i = 0 ; i < _position.rows() ; ++i)
  {
    this->_file_out << " " << _position(i);
  }
   this->_file_out << std::endl;
}


// Calcule la vitesse du fluide à (y,t) donné
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

// Calcule la force de trainée
double Particule :: Force_trainée(double rho, double S, double u, double Cd)
{
    return 0;
    //return 0.5*rho*u*u*S*Cd;
}

// Calcule la force de Magnus
double Particule :: Force_magnus(double rho, double S, double u, double rot,double Cm)
{
    return 0;
    //return 0.5*rho*u*rot*S*Cm;
}
 


#define _FUNCTION_CPP
#endif
