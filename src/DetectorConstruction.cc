#include "DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"

#include <iostream>

using namespace std;

DetectorConstruction::DetectorConstruction()
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
    // ---- Materials ----

    // Some variables for better code readability
    G4String name, symbol;
    G4double z, a, density, fractionmass;
    G4int ncomponents, natoms;

    // Define a Simple Material
    G4Material* lAr = new G4Material(name="liquidArgon", z=18.0, a=39.95*g/mole, density=1.390*g/cm3);

    // Define a Molecule
    G4Element* elH = new G4Element(name="Hydrogen", symbol="H", z=1.0, a=1.01*g/mole);
    G4Element* elO = new G4Element(name="Oxygen", symbol="O", z=8.0, a=16.00*g/mole);
    G4Material* H2O = new G4Material(name="Water", density=1.000*g/cm3, ncomponents=2);
    H2O->AddElement(elH, natoms=2);
    H2O->AddElement(elO, natoms=1);

    // Define a Mixture by Fractional Mass
    G4Element* elN = new G4Element(name="Nitrogen", symbol="N", z=7.0, a=14.01*g/mole);
    G4Material* Air = new G4Material(name="Air ", density=1.290*mg/cm3, ncomponents=2);
    Air->AddElement(elN, fractionmass=70*perCent);
    Air->AddElement(elO, fractionmass=30*perCent);

    // Define a Material from the Geant4 Material Database
    G4NistManager* man = G4NistManager::Instance();
    G4Material* H2O_db = man->FindOrBuildMaterial("G4_WATER");
    G4Material* Air_db = man->FindOrBuildMaterial("G4_AIR");
    G4Material* NaI_db = man->FindOrBuildMaterial("G4_SODIUM_IODIDE");
    G4Material* Al_db = man->FindOrBuildMaterial("G4_Al");
    G4Material* Galactic_db = man->FindOrBuildMaterial("G4_Galactic");

    // Define a Material from the Base Material
    G4Material* water1 = new G4Material("Water_1.05", density=1.05*mg/cm3, H2O_db);
    G4Material* water2 = man->BuildMaterialWithNewDensity("Water_1.03", "G4_WATER", density=1.03*mg/cm3);

    // Print Material Information
    cout << "Start Printing Materials:" << endl;
    cout << H2O;
    cout << *(G4Material::GetMaterialTable());
    cout << "Stop Printing Materials." << endl;

    // Access to Geant4 material database
    // Commands need to be excecuted with UImanager:
    //
    // /material/nist/printElement Fe \\ print element by name
    // /material/nist/printElementZ 13 \\ print element by atomic number
    // /material/nist/listMaterials type \\ print materials type = [simple | compound | hep | all]
    // /material/g4/printElement elmName \\ print instantiated element by name
    // /material/g4/printMaterial matName \\ print instantiated material by name



    // ---- Volumes ----

    G4double world_hx, world_hy, world_hz;
    G4Box* worldBox = new G4Box("World", world_hx=3.0*m, world_hy=1.0*m, world_hz=1.0*m);
    G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, Galactic_db, "World");
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLog, "World", 0, false, 0);
    worldLog->SetVisAttributes(G4VisAttributes::Invisible);

    G4double innerRadius = 0.*cm;
    G4double outerRadius = 3.*cm;
    G4double hz = 9.*cm;
    G4double startAngle = 0.*deg;
    G4double spanningAngle = 360.*deg;
    G4Tubs* detectorTube = new G4Tubs("Detector", innerRadius, outerRadius, hz, startAngle, spanningAngle);
    G4LogicalVolume* detectorLog = new G4LogicalVolume(detectorTube, NaI_db, "Detector");


    G4double axisLength = 1*m;
    G4double axisThickness = 0.1*m;
    G4Box* xAxis = new G4Box("xAxis", 0.5*axisLength, 0.5*axisThickness, 0.5*axisThickness);
    G4LogicalVolume* xAxisLog = new G4LogicalVolume(xAxis, Galactic_db, "xAxis");
    G4Box* yAxis = new G4Box("yAxis", 0.5*axisThickness, 0.5*axisLength, 0.5*axisThickness);
    G4LogicalVolume* yAxisLog = new G4LogicalVolume(yAxis, Galactic_db, "yAxis");
    G4Box* zAxis = new G4Box("zAxis", 0.5*axisThickness, 0.5*axisThickness, 0.5*axisLength);
    G4LogicalVolume* zAxisLog = new G4LogicalVolume(zAxis, Galactic_db, "zAxis");

    G4VPhysicalVolume* xAxisPhys = new G4PVPlacement(0, G4ThreeVector(0.5*axisLength, 0, 0), xAxisLog, "xAxis", worldLog, false, 0);
    xAxisLog->SetVisAttributes(G4VisAttributes(G4Colour::Red()));
    G4VPhysicalVolume* yAxisPhys = new G4PVPlacement(0, G4ThreeVector(0, 0.5*axisLength, 0), yAxisLog, "yAxis", worldLog, false, 0);
    yAxisLog->SetVisAttributes(G4VisAttributes(G4Colour::Green()));
    G4VPhysicalVolume* zAxisPhys = new G4PVPlacement(0, G4ThreeVector(0, 0, 0.5*axisLength), zAxisLog, "zAxis", worldLog, false, 0);
    zAxisLog->SetVisAttributes(G4VisAttributes(G4Colour::Blue()));


    G4double pos_x = 1.0*meter;
    G4double pos_y = 0.0*meter;
    G4double pos_z = 0.0*meter;
    G4RotationMatrix* rotZ = new G4RotationMatrix;
    G4RotationMatrix* rotX = new G4RotationMatrix;
    G4RotationMatrix* rotZ2 = new G4RotationMatrix;
    rotZ->rotateZ(30*deg);
    rotX->rotateZ(30*deg);
    rotZ2->rotateZ(30*deg);
//    G4Transform3D ZX(rotZ, rotX);
//    G4Transform3D ZXZ2(rotZ, rotX);

    // no rotation, translation position, its logical volume, its name, its mother (logical) volume, no boolean operations, its copy number
    G4VPhysicalVolume* detectorPhys = new G4PVPlacement(0, G4ThreeVector(pos_x, pos_y, pos_z), detectorLog, "Tracker", worldLog, false, 0);

    return worldPhys;
}
