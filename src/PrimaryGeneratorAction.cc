#include "PrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4RandomDirection.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    // создаем источник частиц
    // источник испускает по одной частице
    particleGun = new G4ParticleGun(1);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* gamma = particleTable->FindParticle("gamma");
    // устанавливаем тип и энергию частиц, координаты положения источника
    particleGun->SetParticleDefinition(gamma);
    particleGun->SetParticleEnergy(100*keV);
    particleGun->SetParticlePosition(G4ThreeVector(0, 0, 0));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
    // задаем случайное направление излучения
    particleGun->SetParticleMomentumDirection(G4RandomDirection());
    // источник испускает одну частицу
    particleGun->GeneratePrimaryVertex(anEvent);
}
