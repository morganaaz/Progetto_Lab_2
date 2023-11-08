#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "Particle.hpp"

#include <iostream>
//includo <cstring> per la funzione strcmp
#include <cstring>

int Particle::fNParticleType=0;

//essendo static è necessaria una def out of line
std::array<ParticleType*, Particle::fMaxNumParticleType> Particle::fParticleType;
//il tipo va specificato quando non è un costruttore
int Particle::FindParticle(const char* name){
                int index=13;
                static int fNParticleType=0;
                //while(i<10){
                while(fNParticleType<fMaxNumParticleType){
                    //if(name==fParticleType[i]->getName()){
                    //== compara gli indirizzi di memoria delle variabili, non il contenuto
                    if(strcmp(name, fParticleType[fNParticleType]-> getName())==0){
                        index=fNParticleType;
                        break;
                    }
                    ++fNParticleType;
                }
                //return(index);
                if (index==13){
                    std::cout<<"No corresponding type found"<<'\n';
                }
                return index;
};


//APT prende l'output di FP e se risulta una nuova particella,
//l'aggiunge all'array
//non prende nulla in input
//se FP(name)==13 
void Particle::AddParticleType(int fIndex){
    if(fNParticleType<fMaxNumParticleType){
        const char* newName = fParticleType[fIndex]->getName();
        if (FindParticle(newName)==13){
            fParticleType[fNParticleType++]= new ParticleType(
                fParticleType[fIndex]->getName(),
                fParticleType[fIndex]->getMass(),
                fParticleType[fIndex]->getCharge()
            );
            std::cout<<"New particle added"<<'\n';
        }
        else {
            std::cout<<"Particle type already exists"<<'\n';
        }
    }
    else {
        std::cout<<"Max number of particles reached"<<'\n';
    }
}

Particle::Particle(const char* name, double const fPx, double const fPy, double const fPz):
                   fPx_(fPx), fPy_(fPy), fPz_(fPz), fIndex(FindParticle(name)) {}


static void ArrayPrint(){
    
};
void ParticlePrint();
const double getFPx();
const double getFPy();
const double getFPz();
const double Mass();
const double Energy();
double InvMass(const ParticleType Particle);
void SetP(double px, double py, double pz);