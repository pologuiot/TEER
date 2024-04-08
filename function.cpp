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
Particule::Particule()
{
}

// Destructeur par défaut
Particule::~Particule()
{
}


// -------- FONCTIONS --------

// Initialisation du nom du fichier
void Particule::InitializeFileName(const std::string file_name)
{
  _file_out.open(file_name);
}

// Initialise les paramêtres de temps
void Particule::Initialize(double D, double mu_fluide, double m_part, double rho_fluide)
{
    this->_D = D;
    this->_mu_fluide = mu_fluide;
    this->_m_part = m_part;
    this->_rho_fluide = rho_fluide;
    this->_g = 9.81 ;
    this->_const_G = 50.33 ;
    this->_h = 400e-6 ; // distance entre les 2 parois
    this->_f.resize(2) ;
}


// Enregistre la solution dans le fichier
void Particule::SaveSolution(const double t, const VectorXd & position, const VectorXd & vitesse)
{
    this->_file_out << t;
    
    for (int i = 0 ; i < position.rows() ; ++i)
    {
        this->_file_out << " " << position(i) ;
    }
        
    for (int i = 0 ; i < vitesse.rows() ; ++i)
    {
        this->_file_out << " " << vitesse(i) ;
    }
    this->_file_out << std::endl;
}


// Renvoie le vecteur _f
const VectorXd & Particule::GetF() const
{
  return this->_f;
}

// Calcule la vitesse du fluide à (y,t) donné
double Particule::fluidspeed(double y, double t)
{
    double nu=7.31e-7;
    double omega=12;
    double xi = 0.27;
    double G=50.33;
    double rho=1000;
    double h=400e-6; 
    double alpha = sqrt(omega/(2*nu));

    double aa = (exp(alpha*y)+exp(-alpha*y))*cos(alpha*y);
    double bb = (exp(alpha*y)-exp(-alpha*y))*sin(alpha*y);
    double cc = (exp(alpha*h/2.0)+exp(-alpha*h/2.0))*cos(alpha*h/2.0);
    double dd = (exp(alpha*h/2.0)-exp(-alpha*h/2.0))*sin(alpha*h/2.0);

    // Expression calculé à la main 
    double u = (1/(rho*omega))*(-G*xi*sin(omega*t)*(1-(aa*cc+bb*dd)/(cc*cc+dd*dd))+G*xi*cos(omega*t)*((aa*dd-bb*cc)/(cc*cc-dd*dd))) + ((G*h*h)*(1-(2*y/h)*(2*y/h)))/(8*rho*nu) ;

    return u;
}


// Construction de la fonction f pour résoudre u' = f
void Particule::BuildF(double y, double t, const VectorXd & vitesse)
{
    _f(0) = ((3 * this->_mu_fluide * EIGEN_PI * this->_D)/this->_m_part) * (fluidspeed(y, t)- vitesse(0)) ;
    _f(1) = (this->_g * (this->_rho_fluide * (4./3. * EIGEN_PI * pow(this->_D/2, 3)) - this->_m_part) - (3.0 * this->_mu_fluide * EIGEN_PI * this->_D * vitesse(1))) / this->_m_part ; 

    // cout << " f(0) = " << _f(0) << endl ;
    // cout << " f(1) = " << _f(1) << endl ;
}

// Calcule la force de trainée
double Particule :: Force_trainée(double rho, double S, double u, double Cd)
{
    return 0;
}

// Calcule la force de Magnus
double Particule :: Force_magnus(double rho, double S, double u, double rot,double Cm)
{
    return 0;
}

#define _FUNCTION_CPP
#endif