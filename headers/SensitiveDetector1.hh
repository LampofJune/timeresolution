#ifndef SensitiveDetector1_hh
#define SensitiveDetector1_hh

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

class SensitiveDetector1 : public G4VSensitiveDetector
{

public:  
    SensitiveDetector1(G4String name);
    ~SensitiveDetector1();

    void resetOpticalPhotons1() { fOpticalPhotons1 = 0; }
        void resetTime1() { time2 = 0.; }
    G4int getOticalPhotons1() { return fOpticalPhotons1; }
     G4double getphot2() { return time2/s; }
    
private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);

    G4int fOpticalPhotons1;
    G4double time2,photonTime2;
};


#endif
