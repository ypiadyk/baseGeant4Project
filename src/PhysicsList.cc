#include "PhysicsList.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
//#include "G4ParticleDefinition.hh"

PhysicsList::PhysicsList()
{
    defaultCutValue = 1*mm;
}

void PhysicsList::ConstructParticle()
{
    // Register Particles
    G4Gamma::GammaDefinition();
    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
}

void PhysicsList::ConstructProcess()
{
    // Turn On particles movement
    AddTransportation();
    // Standard Physics for Gamma particles
    ConstructEM();
}

void PhysicsList::SetCuts()
{
    SetCutsWithDefault();
}

// gamma
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
// e+/e-
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"
#include "G4eMultipleScattering.hh"

void PhysicsList::ConstructEM()
{
  // цикл по всем зарегистрированным частицам
  theParticleIterator->reset();
  while ( (*theParticleIterator)() ) {
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    // подключаем соответствующие процессы для гамма, электронов и позитронов:
    if (particleName == "gamma") {
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      pmanager->AddDiscreteProcess(new G4ComptonScattering);
      pmanager->AddDiscreteProcess(new G4GammaConversion);

    } else if (particleName == "e-") {
      pmanager->AddProcess(new G4eMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);

    } else if (particleName == "e+") {
      pmanager->AddProcess(new G4eMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);
      pmanager->AddProcess(new G4eplusAnnihilation,  0,-1,4);
    }
  }
}
