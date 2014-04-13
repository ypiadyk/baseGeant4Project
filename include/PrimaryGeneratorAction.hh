#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* anEvent);

private:
    G4ParticleGun* particleGun;

};

#endif // PRIMARYGENERATORACTION_HH
