
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h

// GEANT4 INCLUDES
#include "globals.hh"
#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

// STANDARD INCLUDES
#include <fstream>

class G4Event;
class G4GeneralParticleSource;
class PrimaryGeneratorMessenger;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
   public:
      PrimaryGeneratorAction();
      void ActivityValue();
      ~PrimaryGeneratorAction();

      void GeneratePrimaries(G4Event*) override;
    const G4GeneralParticleSource* GetParticleGun() const { return fParticleGun; }

 private:
      G4GeneralParticleSource* fParticleGun;
};

#endif
