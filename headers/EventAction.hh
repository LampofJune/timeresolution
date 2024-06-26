#ifndef EventAction_h
#define EventAction_h

// GEANT4 INCLUDES
#include "globals.hh"
#include "G4UserEventAction.hh"
#include "G4Accumulable.hh"
#include <fstream>
// USER CLASSES
#include "RunAction.hh"
#include "SensitiveDetector.hh"
#include "SensitiveDetector1.hh"

class EventAction : public G4UserEventAction
{
    public:
        EventAction(RunAction* runAction);
        ~EventAction();

        void BeginOfEventAction(const G4Event*) override;
        void EndOfEventAction(const G4Event*) override;
        void AddEdep(G4double edep) { fEdep += edep; }
        void AddEdep1(G4double edep1) { fEdep1 += edep1; }
        
    private:        
        SensitiveDetector *sDetector;
        SensitiveDetector1 *sDetector1;
        RunAction* fRunAction = nullptr;
        G4double   fEdep = 0.;
        G4double   fEdep1 = 0.;
        G4int evt;
        G4double time;
        std::ofstream outFile;
        
};

#endif
