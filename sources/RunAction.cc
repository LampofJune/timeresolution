
// GEANT4 INCLUDES
#include "G4ParticleDefinition.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AccumulableManager.hh"

// USER CLASSES
#include "../headers/RunAction.hh"

RunAction::RunAction(): G4UserRunAction() {

    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(10000);

    // create analysis manager: the choice of the output format is done via the specified file extension
    G4AnalysisManager*analysisManager = G4AnalysisManager::Instance();

    // create directories (note: merging ntuples is available only with root output)
    analysisManager->SetNtupleMerging(true);

    // creating ntuple    
    analysisManager->CreateNtuple("datamanager", "results");
    analysisManager->CreateNtupleDColumn("E");
    analysisManager->CreateNtupleIColumn("P");
    analysisManager->CreateNtupleIColumn("P1");
    analysisManager->CreateNtupleIColumn("P2");
    analysisManager->FinishNtuple();
}

RunAction::~RunAction(){}

void RunAction::BeginOfRunAction(const G4Run*)
{
    // Get analysis manager
    G4AnalysisManager*analysisManager = G4AnalysisManager::Instance();

    // Open an output file (.csv, .hdf5, .xml)
    G4String fileName = "result.root";  
    analysisManager->OpenFile(fileName);
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    G4int nofEvents = run->GetNumberOfEvent();
    if (nofEvents == 0) return;

    // print histogram statistics
    G4AnalysisManager*analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
