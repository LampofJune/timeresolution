
#ifndef RunAction_h
#define RunAction_h

// GEANT4 INCLUDES
#include "globals.hh"
#include "G4UserRunAction.hh"

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    ~RunAction();
        
    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;
  
  private:
};

#endif
