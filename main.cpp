#include <iostream>
#include <ctime>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "Randomize.hh"

using namespace std;

int main(int argc, char** argv)
{
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    CLHEP::HepRandom::setTheSeed(time(NULL));

    // construct the default run manager
    G4RunManager* runManager = new G4RunManager;
    // set mandatory initialization classes
    runManager->SetUserInitialization(new DetectorConstruction);
    runManager->SetUserInitialization(new PhysicsList);
    // set mandatory user action class
    runManager->SetUserAction(new PrimaryGeneratorAction);
    runManager->SetUserAction(new RunAction);

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    // initialize G4 kernel
    runManager->Initialize();
    // get the pointer to the UI manager and set verbosities
    G4UImanager* UI = G4UImanager::GetUIpointer();
    if ( argc > 1 ) {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UI->ExecuteMacroFile(fileName);
        //UI->ApplyCommand(command+fileName);
    }
    // job termination
    delete visManager;
    delete runManager;
    cout << "Hello World!" << endl;
    return 0;
}
