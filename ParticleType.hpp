#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

class ParticleType{

   public:
    ParticleType(char name, double mass, int charge) : fName(name),
                                     fMass(mass), fCharge(charge){}
    char getName()const;
    double getMass()const;
    int getCharge()const;
    void Print();

    private:
    char* const fName_;
    double const fMass_;
    int const fCharge_;
    
};
#endif