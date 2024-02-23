#ifndef _FUNCTION_CPP

#include "function.h"
#include <cmath>
#include <fstream>
#include <iostream>

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


// Calcul la position de la particule
void Particule::position()
{
    // Cas d'une particule non pesant :
        // X(n+1) = X(n) - vitesse_fluide*dt (particule qui va de droite à gauche = comme si elle reculait)
        // Y(n+1) = Y(n) (pas de changement de hauteur )

    _sol(0) = _sol(0) - fluid_speed(_sol(1))*_dt ;
    _sol(1) = _sol(1) ;
    // cout << _sol(0) << endl; 

}
 


#define _FUNCTION_CPP
#endif