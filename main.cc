// GEANT4 GENERAL INCLUDES
#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include "G4RunManagerFactory.hh"
#include "G4Types.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4GeneralParticleSource.hh" 
#include "G4VisExecutive.hh"

// PHYSICS
#include "G4RadioactiveDecayPhysics.hh"
#include "FTFP_BERT.hh"

// OPTICAL PHYSICS
#include "G4OpticalPhysics.hh"

// USER CLASSES
#include "headers/DetectorConstruction.hh"
#include "headers/ActionInitialization.hh"

int main(int argc, char** argv)
{ 
    // with (-ui 1) or without (-ui 0) visualization
    int i = 0;
    int uisessiontype = 0;  
    while(++i < argc)
    {
        std::string opt(argv[i]);
        if (opt.compare("-ui") == 0) uisessiontype = std::stoi(argv[++i]);        
    }

    // single/multithread selection
    #ifdef G4MULTITHREADED
        int nofthreads = G4Thread::hardware_concurrency();
        G4MTRunManager *runManager = new G4MTRunManager();
        runManager->SetNumberOfThreads(nofthreads);
    #else
        G4RunManager* runManager = new G4RunManager();
    #endif    
  
    // physics list
    G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
    G4VModularPhysicsList* physicsList = new FTFP_BERT;

    physicsList->ReplacePhysics(new G4RadioactiveDecayPhysics());  
    physicsList->RegisterPhysics(opticalPhysics);

    // initialization
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(physicsList);
    runManager->SetUserInitialization(new ActionInitialization());
    runManager->Initialize();

    // vis manager
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    // ui manager
    G4UImanager *uiManager = G4UImanager::GetUIpointer();
    G4UIExecutive *uiExecutive = 0;

 if (argc!=1) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    uiManager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode : define UI session

    G4UIExecutive* ui = new G4UIExecutive(argc, argv);

    uiManager->ApplyCommand("/control/execute macros/vis.mac"); 

    uiManager->ApplyCommand("/control/execute macros/vis.mac"); 
    ui->SessionStart();
    delete ui;

  }
   
    delete visManager;
    delete runManager;
    return 0;
}  
   

