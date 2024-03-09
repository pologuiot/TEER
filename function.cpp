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
}


// Enregistre la solution dans le fichier
void Particule::SaveSolution(const double t, const VectorXd & vitesse)
{
    this->_file_out << t;
    for (int i = 0 ; i < vitesse.rows() ; ++i)
    {
        this->_file_out << " " << vitesse(i);
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
    complex<double> i(0, 1) ;
    complex<double> omega0= i*omega/nu;
    complex<double> u = (this->_const_G / (2.0 * this->_rho_fluide *nu) ) * (this->_h * this->_h / 4.0 - y * y) + (this->_const_G * xi / (i * this->_rho_fluide * omega )) * (1.0 - cosh(omega0 * y) / cosh(omega0 * (this->_h / 2))) * exp(i * omega * t);
    return u.real();
}


// Construction de la fonction f pour résoudre u' = f
void Particule::BuildF(double y, double t, const VectorXd & vitesse)
{
    _f = vitesse ;
    _f(0) = (12 * this->_mu_fluide * EIGEN_PI * this->_D)/this->_m_part * (fluidspeed(y, t)- vitesse(0)) ;
    _f(1) = (this->_g * (this->_rho_fluide * (4/3 * EIGEN_PI * pow(this->_D/2, 3)) - this->_m_part) + 12 * this->_mu_fluide * EIGEN_PI * this->_D * vitesse(1)) / this->_m_part ;
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
