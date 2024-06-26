// USER CLASSES
#include "../headers/ActionInitialization.hh"
#include "../headers/EventAction.hh"
#include "../headers/PrimaryGeneratorAction.hh"
#include "../headers/RunAction.hh"
#include "../headers/SteppingAction.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {}
ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
  SetUserAction(new RunAction());
}

void ActionInitialization::Build() const {
  PrimaryGeneratorAction* primary = new PrimaryGeneratorAction();
  
  RunAction* runaction = new RunAction();
  EventAction* eventaction = new EventAction(runaction);
  SteppingAction *stepaction = new SteppingAction(eventaction);

  SetUserAction(primary);
  SetUserAction(runaction);  
  SetUserAction(eventaction);
  SetUserAction(stepaction);  
}
