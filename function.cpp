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
void Particule::Initialize(double R_part, double rho_part, double mu_fluide, double rho_fluide)
{
    this->_R_part = R_part;
    this->_rho_part = rho_part;
    this->_mu_fluide = mu_fluide;
    this->_rho_fluide = rho_fluide;
    this->_g = 9.81 ;
    this->_const_G = 50.33 ;
    this->_h = 400e-6 ; // distance entre les 2 parois
}


// Enregistre la solution dans le fichier
void Particule::SaveSolution(const double t, const VectorXd & position, const VectorXd & vitesse, const double teta)
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
    this->_file_out << " " << teta;

    this->_file_out << std::endl;
}


// Calcule la vitesse du fluide à (y,t) donné
double Particule::FluidSpeed(double y, double t)
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
    double u;
    
    u = (1/(rho*omega))*(-G*xi*sin(omega*t)*(1-(aa*cc+bb*dd)/(cc*cc+dd*dd))+G*xi*cos(omega*t)*((aa*dd-bb*cc)/(cc*cc-dd*dd))) + ((G*h*h)*(1-(2*y/h)*(2*y/h)))/(8*rho*nu) ;

    return u;
}



// Construction de la fonction f pour résoudre u' = f
void Particule::BuildF(double y, double t, const VectorXd & vitesse)
{
    _f = vitesse ;
    _f(0) = (9*this->_mu_fluide) / (2*this->_rho_part*pow(this->_R_part, 2)) * (FluidSpeed(y, t)- vitesse(0));
    _f(1) = 9*(this->_rho_fluide-this->_rho_part)/this->_rho_part - (9*this->_mu_fluide) / (2*this->_rho_part*pow(this->_R_part, 2)) * vitesse(1) ;
}


// Renvoie le vecteur _f
const VectorXd & Particule::GetF() const
{
  return this->_f;
}


// Calcule la vitesse de cisaillement transversal
double Particule::VitesseCouette(double h, double Shear)
{
    double v;
    double a = this->_R_part;
    
    if (h/a >= 1.)
    {
        v = Shear*h*(1-5.0/16.0 *pow(a/h, 3)) ;
    }
    else
    {
        v = Shear*h* 0.7431/(0.6376-0.2*log((h-a)/a));
    }
    return v; // selon x
}


// calcule le moment (vitesse angulaire) obtenu avec couette
double Particule::MomentCouette(double h, double Shear)
{
    double moment;
    double a = this->_R_part;
    if (h/a >= 1)
    {
        moment = Shear/2 *(1-5.0/16.0 *pow(a/h, 3)) ;
    }
    else
    {
        moment = Shear/2 * 0.8436/(0.6376-0.2*log((h-a)/a));
    }
    return moment; // selon z
}

#define _FUNCTION_CPP
#endif
