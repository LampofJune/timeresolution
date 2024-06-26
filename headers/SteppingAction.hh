#ifndef SteppingAction_h
#define SteppingAction_h

// GEANT4 GENERAL INCLUDES
#include "globals.hh"
#include "G4UserSteppingAction.hh"

// USER CLASSES
#include "EventAction.hh"

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(EventAction*);
    ~SteppingAction();

    void UserSteppingAction(const G4Step*) override;

  private:
    EventAction* fEventAction;
};

#endif
