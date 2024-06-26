
// GEANT4 CLASSES
#include "G4Event.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"

// USER CLASSES
#include "../headers/SteppingAction.hh"
#include "../headers/DetectorConstruction.hh"

SteppingAction::SteppingAction(EventAction* event): G4UserSteppingAction(), fEventAction(event) {}
SteppingAction::~SteppingAction() {}


void SteppingAction::UserSteppingAction(const G4Step* step)
{
    const G4ParticleDefinition* particleDef = step->GetTrack()->GetDynamicParticle()->GetParticleDefinition();    
      
   // const auto detConstruction = static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  //  G4LogicalVolume *fScoringEnergy = detConstruction->GetScoringEnergy();
  //  G4LogicalVolume *fScoringEnergy1 = detConstruction->GetScoringEnergy1();

    // get volume of the current step
  //  G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  
  
	G4String volumeName = step->GetPreStepPoint()->GetPhysicalVolume()->GetName();

    // check if we are in scoring volume
    if (volumeName == "Scintillator" || volumeName == "Scintillator1") {

  //  if (volumeName != "Scintillator1"|| particleDef == G4OpticalPhoton::Definition()) return ;
    // collect energy deposited in this step
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edepStep); }   
}
