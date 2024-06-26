// GEANT4 INCLUDES
#include "G4Event.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4AccumulableManager.hh"
#include <bits/stdc++.h>
// USER CLASSES
#include "../headers/DetectorConstruction.hh"
#include "../headers/EventAction.hh"
#include "../headers/SensitiveDetector.hh"
#include "../headers/SensitiveDetector1.hh"

EventAction::EventAction(RunAction* runAction): fRunAction(runAction){}


EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event*) {
    fEdep = 0.;

    const auto detConstruction = static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    G4LogicalVolume *fScoringOpticalPhotons = detConstruction->GetScoringOpticalPhotons();
    G4LogicalVolume *fScoringOpticalPhotons1 = detConstruction->GetScoringOpticalPhotons1();
    sDetector = dynamic_cast<SensitiveDetector*>(fScoringOpticalPhotons->GetSensitiveDetector());
    sDetector->resetOpticalPhotons();
   sDetector->resetTime();    
   sDetector1 = dynamic_cast<SensitiveDetector1*>(fScoringOpticalPhotons1->GetSensitiveDetector());
   sDetector1->resetOpticalPhotons1();
     sDetector1->resetTime1();
    evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID(); 
}

void EventAction::EndOfEventAction(const G4Event*) {
    if(fEdep <= 0) return;
    
    
     if(sDetector1->getOticalPhotons1()!=0)
 {
  outFile.open("single2.out", std::ofstream::app);
        
 outFile <<sDetector1->getphot2() <<" "<<sDetector1->getOticalPhotons1()<<" "<<evt<< std::endl;
 outFile.close();}
 
 
    
     outFile.open("single1.out", std::ofstream::app);
    if( sDetector->getOticalPhotons() !=0){  
 outFile <<sDetector->getphot1()/sDetector->getOticalPhotons() <<" "<<sDetector->getOticalPhotons()<<" "<<evt<< std::endl;
 outFile.close();}
 


    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->FillNtupleDColumn(0, fEdep);
    man->FillNtupleIColumn(1, sDetector->getOticalPhotons());
    man->FillNtupleIColumn(2, sDetector1->getOticalPhotons1());
    man->FillNtupleIColumn(3, sDetector->getphot1());
    man->AddNtupleRow();
    
    
    
}



