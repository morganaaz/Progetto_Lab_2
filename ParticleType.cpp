#include "ParticleType.hpp"
#include <iostream>

//const tutte le variabili
ParticleType::ParticleType(const char* name, const double mass, const int charge) : fName_((char* const)name),
                                     fMass_(mass), fCharge_(charge){}
const char* ParticleType::getName()const {return fName_;}
double ParticleType::getMass()const {return fMass_;}
int ParticleType::getCharge()const {return fCharge_;}
void ParticleType::Print()const  {
    std::cout<<"Particle Name:\n"<<getName()<<'\n';
    std::cout<<"Particle Mass:\n"<<getMass()<<'\n';
    std::cout<<"Particle Charge:\n"<<getCharge()<<'\n';
}
