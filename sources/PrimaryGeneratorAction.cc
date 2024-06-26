// GEANT4 INCLUDES
#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "G4IonTable.hh"
#include "G4Geantino.hh"

// STANDARD INCLUDES
#include <bits/stdc++.h>

// USER CLASSES
#include "../headers/PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction(), fParticleGun(0) {
  
 fParticleGun  = new G4GeneralParticleSource();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
 
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

