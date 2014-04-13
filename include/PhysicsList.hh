#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class PhysicsList : public G4VUserPhysicsList
{
public:
    PhysicsList();

    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();

    void ConstructEM();
};

#endif // PHYSICSLIST_HH
