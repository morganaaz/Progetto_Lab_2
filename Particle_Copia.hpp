#ifndef PARTICLE_HPP
#define PARTICLE_HPP

//#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include <array>
#include <cmath> //

class Particle
{
public:
    Particle(const char *name, double const fPx, double const fPy, double const fPz);
    Particle();//

    //static void ArrayPrint();
    void ParticlePrint();

    double getFPx()const;
    double getFPy()const;
    double getFPz()const;
    int getfIndex() const;

    double Mass(double massIndex)const;
    double Energy(double mass, double fpx, double fpy, double fpz) const;
    double InvMass(const ParticleType Particle, const ParticleType p) const;
    
    void SetP(double px, double py, double pz)const;
    void SetfIndex(int index_);
    void SetfIndex(const char *name);
    //void PrintArray() const;
    //void PrintParticle() const;

    //static void AddParticleType(int);
    static void AddParticle(const char* name, double mass,
                            int charge, double width = 0);

    int Decay2body(Particle &dau1, Particle &dau2) const;
    void Boost(double bx, double by, double bz);

    static void PrintArray() const;
    void PrintParticle() const; 

    //void setFPx(double px);
    //void setFPy(double py);
    //void setFPz(double pz);

private:
    static const int fMaxNumParticleType = 10;
    static std::array<ParticleType *, fMaxNumParticleType> fParticleType;
    // definisco un array statico con fMNPT elementi di tipo PT, lo chiamo fPT
    static int fNParticleType; // ciclo while in cpp
    int fIndexParticle = -1; //
    int fIndex;
    static int FindParticle(const char *name);

    double const FPx_ = 0;
    double const FPy_ = 0;
    double const FPz_ = 0;
};
#endif