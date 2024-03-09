#ifndef _TIMESCHEME_CPP

#include "TimeScheme.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <complex>

using namespace std;
using namespace Eigen;


// -------- CONSTRUCTEUR --------

// Constructeur par défaut (ne pas oublier de mettre votre pointeur à 0 !!)
EulerScheme::EulerScheme() : _sys(0)
{
}

// Destructeur
EulerScheme::~EulerScheme()
{
}

// -------- INITIALISATION DES VARIABLES --------

void EulerScheme::Initialize(double y, double t0, double dt, Eigen::VectorXd & vitesse_init, std::string name_file, Particule* sys)
{
    this->_y = y;
    this->_dt = dt;
    this->_t = t0 ;
    this->_vitesse_init = vitesse_init;
    this->_vitesse = vitesse_init;
    this->_sys = sys;
    if (name_file.size() > 0)
    {
       this->_sys->InitializeFileName(name_file);
    }
}

// -------- FONCTIONS --------


// Enregistre la solution : fait appel à OdeSystem car la solution
// que l'on souhaite sauvegarder peut être différente de _vitesse SaveSolution
// le système
void EulerScheme::SaveSolution()
{
   this->_sys->SaveSolution(this->_t, this->_vitesse);
}


// Fonction pour avancer en temps avec la méthode d'Euler explicite
void EulerScheme::Advance()
{
    this->_sys->BuildF(this->_y, this->_t, this->_vitesse);
    this->_vitesse += this->_dt*this->_sys->GetF();
    this->_t += this->_dt;
}



#define _TIME_SCHEME_CPP
#endif
