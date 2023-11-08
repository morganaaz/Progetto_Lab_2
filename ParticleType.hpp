#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <iostream>

class ParticleType{

   public:
    ParticleType(const char* name, const double mass, const int charge);
    const char* getName()const;
    double getMass()const;
    int getCharge()const;
    virtual void Print()const;

    private:
    const char* fName_;
    double const fMass_;
    int const fCharge_;
    
};
#endif
