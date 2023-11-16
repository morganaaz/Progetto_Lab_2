#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "Particle.hpp"

#include <iostream>
// includo <cstring> per la funzione strcmp
#include <cstring>
#include <cmath>

int Particle::fNParticleType = 0;

// essendo static è necessaria una def out of line
std::array<ParticleType *, Particle::fMaxNumParticleType> Particle::fParticleType;
// il tipo va specificato quando non è un costruttore

Particle::Particle(const char *name, double const FPx, double const FPy, double const FPz)
         : FPx_(FPx), FPy_(FPy), FPz_(FPz), fIndexParticle(FindParticle(name)) {
    //
    fIndexParticle = FindParticle(name);
    if (fIndexParticle==-1){
        std::cout << "No corresponding type found" << '\n';
    }
}
//
//creo una particella
Particle::Particle() : fIndexParticle(-2), FPx_(0), FPy_(0), FPz_(0) {}
int Particle::FindParticle(const char* findName){
    for (int i = 0; i < fNParticleType; i++){
        if(findName==(fParticleType[i]->getName()))
            return i;
    }
    //se non è trovata una compatibilità
    return -1;
}

//
//uso il polimorfismo di SetfIndex
void Particle::SetfIndex(const char* name){
    if ((Particle::FindParticle(name)) < 0){
        std::cout<<"Name not found"<<'\n';
        } else{
        fIndexParticle = FindParticle(name);
        }
}

void Particle::SetFIndex(int newIndex){
    if (newIndex < 0){
        std::cout<<"Index must be positive"<<'\n';
    } else{
        fIndexParticle = newIndex;
    }
}


/*int Particle::FindParticle(const char *name) //
                        //sost name con findn per chiarezza
    {
    int index = 13;
    static int fIndexParticle = FindParticle(findName);
    static int fNParticleType = 0;
    
    while (fNParticleType < fMaxNumParticleType)
    {
        // if(name==fParticleType[i]->getName()){
        //== compara gli indirizzi di memoria delle variabili, non il contenuto
        if (strcmp(findName, fParticleType[fNParticleType]->getName()) == findName)
        {
            index = fNParticleType;
            break;
        }
    
        ++fNParticleType;
    }
    */
    
    

    // return(index);
    if (fIndexParticle == 13)
    {
        std::cout << "No corresponding type found" << '\n';
    }

// APT prende l'output di FP e se risulta una nuova particella,
// l'aggiunge all'array
// non prende nulla in input
// se FP(name)==13

//cambiato l'input di AddParticle
void Particle::AddParticle(const char* newName, double mass,
                            int charge, double width)
{
    if (Particle::FindParticle(newName) < 0){
        if (fNParticleType < fMaxNumParticleType)
        {
            width == 0?
            fParticleType[fNParticleType] = new ParticleType(newName, mass, charge, width)
            : fParticleType[fNParticleType] = new ResonanceType(newName, mass, charge, width);
    
            fNParticleType++;

/*const char *newName = fParticleType[fIndex]->getName();
        if (FindParticle(newName) == 13)
        {
            fParticleType[fNParticleType++] = new ParticleType(
                fParticleType[fIndex]->getName(),
                fParticleType[fIndex]->getMass(),
                fParticleType[fIndex]->getCharge()
                // fParticleType[fIndex]->getWidth()
            );
*/
            std::cout<<"New particle added"<<'\n';
        } else{
            std::cout << "Error: max number of particles reached" << '\n';
        }
    }else{
        std::cout<< "Error: particle type already exists" << '\n';
    }
}



//ancora da vedere

int Particle::getfIndex() const { return fIndex; }

void Particle::SetfIndex(int index_) { fIndex = index_; };

void Particle::SetfIndex(const char *name) { fIndex = FindParticle(name); };

//void Particle::setFPx(double px) { double FPx_ = px; };
//void Particle::setFPy(double py) { double FPy_ = py; };
//void Particle::setFPz(double pz) { double FPz_ = pz; };

//spostato infondo
/*
void Particle::PrintArray() const
{
    for (int e = 0; e < 10; ++e)
    {
        std::cout << "Particle: " << e << '\n'
                  << "Name: " << fParticleType[e]->getName() << '\n'
                  << "Mass: " << fParticleType[e]->getMass() << '\n'
                  << "Charge: " << fParticleType[e]->getCharge() << '\n';
        //<< "Width: " << fParticleType[e].getWidth() << '\n';
    }
};

void Particle::PrintParticle() const
{
    std::cout << "Index: " << getfIndex() << '\n'
              << "Name: " << fParticleType[getfIndex()]->getName() << '\n';
}
*/

/*
double Particle::getFPx() const{return FPx_;};
double Particle::getFPy() const{return FPy_;};
double Particle::getFPz() const{return FPz_;};
double Particle::Mass(double massIndex) const {
    return fParticleType[massIndex]->getMass();};
double Particle::Energy(double mass, double fpx, double fpy, double fpz) const{
    double module=sqrt(pow(fpx,2)+pow(fpy,2)+pow(fpz,2));
    double energy=sqrt(pow(mass,2)+pow(module,2));
    return energy;
}
*/

/* Particle P("P", 0.0, 0.0, 0.0);
//void SetP(double px, double py, double pz){};

double Particle::InvMass(const Particle particle, double particleEnergy, const Particle p, double pEnergy)const{
    double impulseX= particle.FPx_ + p.FPx_;
    double impulseY= particle.FPy_ + p.FPy_;
    double impulseZ= particle.FPz_ + p.FPz_;
    double sumE;
    double sumI=pow(impulseX,2)+pow(impulseY,2)+pow(impulseZ,2);
    double invMass=sqrt(pow(sumE,2)-pow(sumI,2))
    return invMass;
};
*/

void Particle::SetP(double px, double py, double pz){
    FPx_=px;
    FPy_=py;
    FPz_=pz;
}

//aggiunta da file Virtuale controllare variabili
int Particle::Decay2body(Particle &dau1,Particle &dau2) const {
  if(GetMass() == 0.0){
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }
  
  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if(fIParticle > -1){ // add width effect

    // gaussian random numbers

    float x1, x2, w, y1;
    
    double invnum = 1./RAND_MAX;
    do {
      x1 = 2.0 * rand()*invnum - 1.0;
      x2 = 2.0 * rand()*invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while ( w >= 1.0 );
    
    w = sqrt( (-2.0 * log( w ) ) / w );
    y1 = x1 * w;

    massMot += fParticleType[fIParticle]->GetWidth() * y1;

  }

  if(massMot < massDau1 + massDau2){
    printf("Decayment cannot be preformed because mass is too low in this channel\n");
    return 2;
  }
  
  double pout = sqrt((massMot*massMot - (massDau1+massDau2)*(massDau1+massDau2))*(massMot*massMot - (massDau1-massDau2)*(massDau1-massDau2)))/massMot*0.5;

  double norm = 2*M_PI/RAND_MAX;

  double phi = rand()*norm;
  double theta = rand()*norm*0.5 - M_PI/2.;
  dau1.SetP(pout*sin(theta)*cos(phi),pout*sin(theta)*sin(phi),pout*cos(theta));
  dau2.SetP(-pout*sin(theta)*cos(phi),-pout*sin(theta)*sin(phi),-pout*cos(theta));

  double energy = sqrt(fPx*fPx + fPy*fPy + fPz*fPz + massMot*massMot);

  double bx = fPx/energy;
  double by = fPy/energy;
  double bz = fPz/energy;

  dau1.Boost(bx,by,bz);
  dau2.Boost(bx,by,bz);

  return 0;
}
void Particle::Boost(double bx, double by, double bz)
{

  double energy = GetEnergy();

  //Boost this Lorentz vector
  double b2 = bx*bx + by*by + bz*bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx*fPx + by*fPy + bz*fPz;
  double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;

  fPx += gamma2*bp*bx + gamma*bx*energy;
  fPy += gamma2*bp*by + gamma*by*energy;
  fPz += gamma2*bp*bz + gamma*bz*energy;

}

void Particle::PrintArray() const{
    for (int e = 0; e < fNParticleType; ++e)
    {
        std::cout << "Particle: " << e << '\n'
                  << "Index: "<< fIndexParticle << '\n'
                  << "Name: " << fParticleType[e]->getName() << '\n'
                  << "Mass: " << fParticleType[e]->getMass() << '\n'
                  << "Charge: " << fParticleType[e]->getCharge() << '\n'
                                    
    }
};

void Particle::PrintParticle() const{
    for (int e = 0; e < fNParticleType; ++e)
    {
        std::cout << "Particle: " << e << '\n'
                  << "Index: "<< fIndexParticle << '\n'
                  << "Name: " << fParticleType[e]->getName() << '\n'
                  << "Px: " << FPx_ << '\n'
                  << "Py: " << FPy_ << '\n'
                  << "Pz: " << FPz_ << '\n';                  
    }
};
