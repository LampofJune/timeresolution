#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

// GEANT4 INCLUDES
#include "G4VUserDetectorConstruction.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4VSensitiveDetector.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4GenericMessenger.hh"
#include "G4RunManager.hh"
#include "G4PVReplica.hh"
#include "G4GenericMessenger.hh"

// USER CLASSES
#include "SensitiveDetector.hh"
#include "SensitiveDetector1.hh"

class G4VPhysicalVolume;
class G4MaterialPropertiesTable;

class DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        DetectorConstruction();
        ~DetectorConstruction();
    
        G4LogicalVolume *GetScoringOpticalPhotons() const { return fScoringOpticalPhotons;}
        
        G4LogicalVolume *GetScoringOpticalPhotons1() const { return fScoringOpticalPhotons1;}
        G4LogicalVolume *GetScoringEnergy() const { return fScoringEnergy;}
        G4LogicalVolume *GetScoringEnergy1() const { return fScoringEnergy1;}
        virtual G4VPhysicalVolume* Construct();
 

    private:
        G4Box *solidWorld;
        G4LogicalVolume *logicWorld, *fScoringOpticalPhotons, *fScoringEnergy, *fScoringOpticalPhotons1, *fScoringEnergy1;
        G4VPhysicalVolume *physWorld;
        G4OpticalSurface *teflonSurface, *AluminumSurface;

        G4Material *LaBr3, *Teflon, *worldMat, *Glass, *Aluminum, *water,*polyethylene_NEMA;

        void DefineMaterial();
        virtual void ConstructSDandField();
};

#endif

