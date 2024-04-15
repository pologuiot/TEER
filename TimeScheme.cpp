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
TimeScheme::TimeScheme() : _sys(0)
{
}

// Destructeur
TimeScheme::~TimeScheme()
{
}

// -------- INITIALISATION DES VARIABLES --------

void TimeScheme::Initialize(double t0, double dt, Eigen::VectorXd & vitesse_init, Eigen::VectorXd & position_init, std::string name_file, Particule* sys)
{
    this->_dt = dt;
    this->_t = t0 ;
    this->_vitesse_init = vitesse_init;
    this->_position_init = position_init;
    this->_v_poseuille = vitesse_init;
    this->_teta = 0.0 ;
    //this->_v_couette = ?; //jsp c'est quoi les CL a t=0
    //this->_moment = ?;
    this->_position = position_init;
    this->_sys = sys;
    if (name_file.size() > 0)
    {
       this->_sys->InitializeFileName(name_file);
    }
}

// -------- FONCTIONS --------


// Enregistre la solution : fait appel à OdeSystem car la solution
// que l'on souhaite sauvegarder peut être différente de _v_poseuille SaveSolution
// le système
void TimeScheme::SaveSolution()
{
   this->_sys->SaveSolution(this->_t, this->_position, this->_v_poseuille, this->_teta);
}


// Fonction pour avancer en temps avec la méthode d'Euler explicite
void TimeScheme::AdvanceVitessePoiseuille()
{
    if (abs(this->_position(1)) < 200e-6) {
        this->_sys->BuildF(this->_position(1), this->_t, this->_v_poseuille);
        this->_v_poseuille += this->_dt*this->_sys->GetF();
        // this->_teta = fmod(this->_teta+2.0,360)  ; // fmod() -> modulo pour les doubles
        this->_t += this->_dt;

    }
    else {
        this->_teta = fmod(this->_teta+2.0,360)  ;
        this->_t += this->_dt ;
    }
}


// Calcul du coefficient S (shear) et h
 void TimeScheme::AdvanceShear()
 {   
     this->_Shear = (this->_sys->FluidSpeed(this->_position(1)+(5e-7),this->_t)-this->_sys->FluidSpeed(this->_position(1)-(5e-7),this->_t))/(10.0e-7) ;
     
     double S0 = this->_sys->FluidSpeed(0, this->_t);
     double l = -this->_Shear / S0 ;
     this->_h = this->_position(1) - l;
 }


 // Fonction pour avancer en temps la vitesse de couette (cisaillement)
 void TimeScheme::AdvanceVitesseCouette()
 {
     this->_v_couette(0) = this->_sys->VitesseCouette(this->_position(1), this->_Shear);
     this->_v_couette(1) = 0;
 }

 // Avance en temps le moment (cisaillement)
 void TimeScheme::AdvanceMomentCouette()
 {
     this->_moment(2) = this->_sys->MomentCouette(this->_h, this->_Shear);
     this->_moment(0) = 0;
     this->_moment(1) = 0;
 }

// Mise à jour de la position de la particule
void TimeScheme::AdvancePosition()
{
    this->_position += (this->_v_poseuille /*+ this->_v_couette*/) * this->_dt ;
    
    if (abs(this->_position(1)) >= 200e-6) {
        this->_v_poseuille(0) = 0.0 ;
        this->_v_poseuille(1) = 0.0 ;
    }
}





#define _TIME_SCHEME_CPP
#endif
