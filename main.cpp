#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "Particle.hpp"
#include <array>

int main(){
const char* a = "Gigi";
const char* b = "Paperino";
ParticleType firstParticleType(b, 2., 6);
ResonanceType firstResonanceType(a, 3., 5, 7.);

firstParticleType.Print();
firstResonanceType.Print();

std::array<ParticleType *,2> particleArray;
particleArray[0] = &firstParticleType;
particleArray[1] = &firstResonanceType;

for(int i = 0; i < 2; ++i){
    particleArray[i]->Print();
}

}