#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include <array>

class Particle{
    public:
    Particle(const char* name, double const fPx, double const fPy, double const fPz);
    //
    static void AddParticleType(int);

    static void ArrayPrint();
    void ParticlePrint();
    const double getFPx();
    const double getFPy();
    const double getFPz();
    const double Mass();
    const double Energy();
    double InvMass(const ParticleType Particle);
    void SetP(double px, double py, double pz);
    

    private:
    static const int fMaxNumParticleType=10;
    static std::array<ParticleType *, fMaxNumParticleType> fParticleType;
    //definisco un array statico con fMNPT elementi di tipo PT, lo chiamo fPT
    static int fNParticleType; //ciclo while in cpp
    int fIndex;
    int FindParticle(const char* name);
    

    double const fPx_=0;
    double const fPy_=0;  
    double const fPz_=0;
    




};
#endif