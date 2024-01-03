#include <iostream>


int main()
{
    std::cout<<'\n';

    Int_t nGen = 100000;
    Int_t nParticlesPerGen = 100;
    Int_t dimArrayParticles = nParticlesPerGen + (Int_t)(0.2 * nParticlesPergen);
    Double_t theta, phi, p, x;
    gRandom-> SetSeed();

    Particle::AddParticleType("pi+",0.13957,1);
    Particle::AddParticleType("pi-",0.13957,-1);
    Particle::AddParticleType("k+",0.49367,1);
    Particle::AddParticleType("k-",0.49367,-1);
    Particle::AddParticleType("p+",0.93827,1);
    Particle::AddParticleType("p-",0.93827,-1);
    Particle::AddParticleType("k*",0.89166,0,0.050);

    //Creo gli istogrammi
    TH1F *hParticleType_distribution = new TH1F ("hParticleType_distribution", "Distribution of particle types",7, 0, 7);
    TH1F *hTheta_distribution = new TH1F ("hTheta_distribution", "Theta istribution (polar coordinate)",1000, 0, TMath::Pi());
    hTheta_distribution->SetMinimum(0);    
    hTheta_distribution->SetMaximum(nGen*.2);
    TH1F *hPhi_distribution = new TH1F ("hPhi_distribution", "Phi distribution (azimutal coordinate)",1000, 0, 2*TMath::Pi());
    hTheta_distribution->SetMinimum(0);    
    hTheta_distribution->SetMaximum(nGen*.2);
    TH1D *homentum_distribution = new TH1D("hMomentum_distribution", "Momentum distribution", 1000, 0, 10);
    TH1D *hTransverseMomentum_distribution = new TH1D ("hTransverseMomentum_distribution", "Transverse momentum distribution", 1000, 0, 10);
    TH1D *hEnergy_distribution = new TH1D ("hEnergy_distribution", "Energy distribution", 1000, 0, 10);
    TH1D *hTotInvaiantMass_distribution = new TH1D ("hTotInvaiantMass_distribution", "Invariant mass distribution of all generated particles", 80, 0, 2);
    TH1D *hInvaiantMassD_distribution = new TH1D ("hInvaiantMassD_distribution", "Invariant mass distribution of all particles with discordant charge", 80, 0, 2);
    TH1D *hInvaiantMassDPiK_distribution = new TH1D ("hInvaiantMassDPiK_distribution", "Invariant mass distribution of all pi-k particles with discordant charge", 80, 0, 2);
    TH1D *hInvaiantMassC_distribution = new TH1D ("hInvaiantMassC_distribution", "Invariant mass distribution of all particles with concordant charge", 80, 0, 2);
    TH1D *hInvaiantMassCPiK_distribution = new TH1D ("hInvaiantMassCPiK_distribution", "Invariant mass distribution of all pi-k particles with concordant charge", 80, 0, 2);
    TH1D *hInvariantMassDecay_distribution = new TH1D ("hInvariantMassDecay_distribution", "Invariant mass distribution of k* particles decay", 80, 0, 2);
    hInvariantMassDecay_distribution -> Sunw2();
    Particle simulation[dimArrayParticles];
    std::cout << "\nLoading simulation\n";
    
    for(Int_t i = 0; i < nGen; i++)
    {
        Int_t resonance = 0;
        for(Int_t j = 0; j < nParticlePerGen; j++)
        {
            x = gRandom -> Rndm();
            if(x < 0.4)
                simulation[j].SetIdentifier(0);
            else if(x < 0.8)
                simulation[j].SetIdentifier(1);
            else if(x < 0.85)
                simulation[j].SetIdentifier(2);
            else if(x < 0.90)
                simulation[j].SetIdentifier(3);
            else if(x < 0.945)
                simulation[j].SetIdentifier(4);
            else if(x < 0.99)
                simulation[j].SetIdentifier(5);
            else
            {
                simulation[j].SetIdentifier(6);
                if (x < 0.995)
                {
                    simulation[nParticlesPerGen + resonance].SetIdentifier(2);
                    ++resonance;
                    simulation[nParticlesPerGen + resonance].SetIdentifier(1);
                    ++resonance;
                    
                }
                else
                {
                    simulation[nParticlesPerGen + resonance].SetIdentifier(3);
                    ++resonance;
                    simulation[nParticlesPerGen + resonance].SetIdentifier(0);
                    ++resonance;                   
                }
                simulation[j].Decay2body(simulation[nParticlesPerGen + resonance - 2], simulation[nParticlesPerGen + resonance]);
            }
            hParticleTypes_distribution -> Fill(simulation[j].GetIdentifier());
            theta = gRandom -> Uniform(0, TMath::Pi());
            hTheta_distribution -> Fill(theta);
            phi = gRandom -> Uniform(0, 2*TMath::Pi());
            hPhi_distribution -> Fill(phi);
            p = gRandom -> Exp(1);
            hMomentum_distribution -> Fill(p);
            simulation[j].SetP(p*TMath::Sin(theta)*TMath::Cos(phi),
                               p*TMath::Sin(theta)*TMath::Sin(phi),
                               p*TMath::Cos(theta));
            hTrasverseMomentum_distribution -> Fill(sqrt(pow(simulation[j].GetPx(),2)
                                                    + pow(simulation[j].GetPy(),2)));
            hEnergy_distribution -> Fill(simulation[j].GetEnergy());            
        }
        for (Int_t particle_1 = 0; particle_1 < nParticlePerGen + resonance; particle_1++)
        {
            for (Int_t particle_2 = particle_1 + 1; particle_2 < nParticlesPerGen + resonance; particle_2++)
            {
                hTotInvariantMass_distribution -> Fill(simulation[particle_1].InvariantMass(simulation[particle_2]));
                if (simulation[particle_1].GetCharge()*simulation[particle_2].GetCharge() < 0.0)
                {
                    hInvariantMassD_distribution -> Fill(simulation[particle_1].InvariantMass(simulation[particle_2]));
                    if ((simulation[particle_1].GetIdentifier() <= 1 &&
                         simulation[particle_2].GetIdentifier() > 1 &&
                         simulation[particle_2].GetIdentifier() <= 3) ||
                        (simulation[particle_2].GetIdentifier() <= 1 &&
                         simulation[particle_1].getIdentifier() > 1 &&
                         simulation[particle_1].GetIdentifier() <= 3))

                    hInvariantMassDPiK_distribution -> Fill(simulation[particle_1].InvariantMass(simulation[particle_2]));
                }
                else if (simulation[particle_1].GetCharge()*simulation[particle_2].GetCharge() > 0.0)
                {
                    hInvariantMassC_distribution -> Fill(simulation[particle_1].InvariantMass(simulation[particle_2]));
                    if ((simulation[particle_1].GetIdentifier() <= 1 &&
                         simulation[particle_2].GetIdentifier() > 1 &&
                         simulation[particle_2].GetIdentifier() <= 3) ||
                        (simulation[particle_2].GetIdentifier() <= 1 &&
                         simulation[particle_1].GetIdentifier() > 1 &&
                         simulation[particle_1].GetIdentifier() <= 3))
                    hInvariantMassCPiK_distribution -> Fill(simulation[particle_1].InvariantMass(simulation[particle_2]));
                }
            }
        }
        for (Int_t particle_1 = 0; particle_1 < resonance; particle_1 = particle_1 + 2)
        {
            hInvariantMassDecay_distribution -> Fill(simulation[nParticlesPergen + particle_1].InvariantMass(simulation[nParticlesPerGen + 1 + particle_1]));
        }
    }
    TFile * theFile = new TFile("Particles_simulation.root","RECREATE");

    //Graphics
    hParticleType_distribution -> GetXaxis() -> SetTitle("Particle types ");
    hParticleType_distribution -> GetXaxis() -> SetBinLabel(1,"pi+");
    hParticleType_distribution -> GetXaxis() -> SetBinLabel(2,"pi-");
    hParticleType_distribution -> GetXaxis() -> SetBinLabel(3,"k+");
    hParticleType_distribution -> GetXaxis() -> SetBinLabel(4,"k-");
    hParticleType_distribution -> GetXaxis() -> SetBinLabel(5,"p+");
    hParticleType_distribution -> GetXaxis() -> SetBinLabel(6,"p-");
    hParticleType_distribution -> GetXaxis() -> SetBinLabel(7,"k*");
    hParticleType_distribution -> GetYaxis() -> SetTitle("Occurrences");
    hParticleType_distribution -> Write();

    hTheta_distribution -> GetXaxis() -> SetTitle("Theta (rad)");
    hTheta_distribution -> GetYaxis() -> SetTitle("Occurrences");
    hTheta_distribution -> Write();

    hPhi_distribution -> GetXaxis() -> SetTitle("Phi (rad)");
    hPhi_distribution -> GetYaxis() -> SetTitle("Occurrences");
    hPhi_distribution -> Write();

    hEnergy_distribution -> GetXaxis() -> SetTitle("Energy (GeV)");
    hEnergy_distribution -> GetYaxis() -> SetTitle("Occurrences");
    hEnergy_distribution -> Write();

    hMomentum_distribution -> GetXaxis() -> SetTitle("Momentum (GeV)");
    hMomentum_distribution -> GetYaxis() -> SetTitle("Occurrences");
    hMomentum_distribution -> Write();

    hTrasverseMomentum_distribution -> GetXaxis() -> SetTitle("Trasverse momentum (GeV)");
    hTrasverseMomentum_distribution -> GetYaxis() -> SetTitle("Occurrences");
    hTrasverseMomentum_distribution -> Write();

    hTotInvaiantMass_distribution -> GetXaxis() -> SetTitle("Invariant mass (GeV/c^2)");
    hTotInvaiantMass_distribution -> GetYaxis() -> SetTitle("Occurrences");
    hTotInvaiantMass_distribution -> Write();

    hInvaiantMassD_distribution -> GetXaxis() -> SetTitle("Invariant mass (GeV/c^2)");
    hInvaiantMassD_distribution -> GetYaxis() -> SetTitle("Occurrences");
    hInvaiantMassD_distribution -> Write();

    hInvaiantMassDPiK_distribution -> GetXaxis() -> SetTitle("Invariant mass (GeV/c^2)");
    hInvaiantMassDPiK_distribution -> GetYaxis() -> SetTitle("Occurrences");
    hInvaiantMassDPiK_distribution -> Write();

    hInvaiantMassC_distribution -> GetXaxis() -> SetTitle("Invariant mass (GeV/c^2)");
    hInvaiantMassC_distribution -> GetYaxis() -> SetTitle("Occurrences");
    hInvaiantMassC_distribution -> Write();

    hInvaiantMassCPiK_distribution -> GetXaxis() -> SetTitle("Invariant mass (GeV/c^2)");
    hInvaiantMassCPiK_distribution -> GetYaxis() -> SetTitle("Occurrences");
    hInvaiantMassCPiK_distribution -> Write();

    hInvaiantMassDecay_distribution -> GetXaxis() -> SetTitle("Invariant mass (GeV/c^2)");
    hInvaiantMassDecay_distribution -> GetYaxis() -> SetTitle("Occurrences");
    hInvaiantMassDecay_distribution -> Write();

    theFile -> Close();

    std::cout << "\nGeneration completed successfully\n";

}