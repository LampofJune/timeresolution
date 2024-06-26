#ifndef SensitiveDetector_hh
#define SensitiveDetector_hh

// GEANT4 GENERAL INCLUDES
#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4PhysicsOrderedFreeVector.hh"
#include "G4VProcess.hh"
#include "G4SDManager.hh"
#include "G4VHit.hh"
#include <fstream>
class SensitiveDetector : public G4VSensitiveDetector
{

public:  
    SensitiveDetector(G4String name);
    ~SensitiveDetector();

    void resetOpticalPhotons() { fOpticalPhotons = 0; }
    void resetTime() { time1 = 0; }
    G4int getOticalPhotons() { return fOpticalPhotons; }
    G4int getEventNum() { return eventNumber; }
    G4double getphot1() { return time1/s; }
    
    
    
private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
   std::ofstream outFile;
    G4int fOpticalPhotons;
      G4int eventNumber;
      G4double photonTime,time1;
};


#endif
