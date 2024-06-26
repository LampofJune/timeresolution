// GEANT4 INCLUDES
#include "G4RunManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4Event.hh"

// USER CLASSES
#include "../headers/SensitiveDetector1.hh"
#include "../headers/DetectorConstruction.hh"
#include "../headers/EventAction.hh"
//#include "../headers/SteppingAction.hh"

SensitiveDetector1::SensitiveDetector1(G4String name) : G4VSensitiveDetector(name), time2(0.0){
    collectionName.insert("SDHitwwwCollection");     
}

SensitiveDetector1::~SensitiveDetector1() {}

G4bool SensitiveDetector1::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{

 const auto detConstruction = static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
 
    G4LogicalVolume* volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    
    G4LogicalVolume *det = detConstruction->GetScoringOpticalPhotons1();
  //  G4LogicalVolume *det1 = detConstruction->GetScoringOpticalPhotons1();
    G4int evt1 = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    G4Track* aTrack = aStep->GetTrack();
    const G4ParticleDefinition* particleDef = aTrack->GetDynamicParticle()->GetParticleDefinition();
//    outFile.open("timelyso.out", std::ofstream::app);
    
    if (particleDef == G4OpticalPhoton::Definition() ) {

        // colllect photon
        ++fOpticalPhotons1;
          photonTime2= aTrack -> GetGlobalTime();
          time2+=aTrack -> GetGlobalTime();
        aTrack->SetTrackStatus(fStopAndKill);
    }
    return true;
}
