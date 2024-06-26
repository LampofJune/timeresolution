// GEANT4 INCLUDES
#include "G4RunManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4Event.hh"
#include <bits/stdc++.h>
// USER CLASSES
#include "../headers/SensitiveDetector.hh"
#include "../headers/DetectorConstruction.hh"
#include "../headers/EventAction.hh"
//#include "../headers/SteppingAction.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name),time1(0.0){
    collectionName.insert("SDHitCollection");     
}

SensitiveDetector::~SensitiveDetector() {}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{

 const auto detConstruction = static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
 
  /*  G4LogicalVolume* volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    
    G4LogicalVolume *det = detConstruction->GetScoringOpticalPhotons();
  //  G4LogicalVolume *det1 = detConstruction->GetScoringOpticalPhotons1();
    G4int evt1 = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();*/
    G4Track* aTrack = aStep->GetTrack();
    const G4ParticleDefinition* particleDef = aTrack->GetDynamicParticle()->GetParticleDefinition();
//    outFile.open("timelyso.out", std::ofstream::app);
    
    if (particleDef == G4OpticalPhoton::Definition() ) {

        // colllect photon
        ++fOpticalPhotons;
         eventNumber = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
          photonTime = aTrack -> GetGlobalTime();
          time1+=aTrack -> GetGlobalTime();
        aTrack->SetTrackStatus(fStopAndKill);
    }
    
     return true;    
}
