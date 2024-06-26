
// GEANT4 INCLUDES
#include "G4VisAttributes.hh"

// USER CLASSES
#include "../headers/DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction() { DefineMaterial(); }
DetectorConstruction::~DetectorConstruction() {}

void DetectorConstruction::DefineMaterial(){
    // define world material
    G4NistManager *nist = G4NistManager::Instance();
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    polyethylene_NEMA = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

    // define world material
    G4double energy[2] = {2.627*eV, 3.84*eV};
    G4double rindexWorld[2] = {1., 1.};
    G4MaterialPropertiesTable *worldMPT = new G4MaterialPropertiesTable();
    worldMPT->AddProperty("RINDEX", energy, rindexWorld, 2);
    worldMat->SetMaterialPropertiesTable(worldMPT);

    // define material scintillator
    G4double fraction[2] = {1.0, 1.0};
    G4double rindexLaBr3[2] = {1.9, 1.85};    

   Aluminum = nist->FindOrBuildMaterial("G4_Al");
   water = nist->FindOrBuildMaterial("G4_WATER");

	//Define elements for the GSO  crystal (scintillator) 
   G4Material*det = new G4Material("det",7.11*g/cm3, 4);
  //  G4Material* LYSO = new G4Material("LYSO", 7.11*g/cm3, 4);
  det->AddElement( nist->FindOrBuildElement("Lu"), 71.43*perCent);
  det->AddElement(nist->FindOrBuildElement("Y"), 4.03*perCent);
  det->AddElement(nist->FindOrBuildElement("Si"), 6.37*perCent);
  det->AddElement(nist->FindOrBuildElement("O"),18.14*perCent);
    
    LaBr3 = new G4Material("LaBr3",7.11*g/cm3 ,1);
    LaBr3->AddMaterial(det,100*perCent);
   // LaBr3->AddElement(nist->FindOrBuildElement("Ce"), 5*perCent);

    G4MaterialPropertiesTable *crystalMPT = new G4MaterialPropertiesTable();
    crystalMPT->AddProperty("RINDEX", energy, rindexLaBr3, 2);    
    crystalMPT->AddProperty("SCINTILLATIONCOMPONENT1", energy, fraction,2);

    crystalMPT->AddConstProperty("SCINTILLATIONYIELD", 30./keV);
    crystalMPT->AddConstProperty("RESOLUTIONSCALE",1);
    crystalMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 40.*ns);
    crystalMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 4.*ns);
    crystalMPT->AddConstProperty("SCINTILLATIONYIELD1", 1.);
    crystalMPT->AddConstProperty("SCINTILLATIONYIELD2", 0.);
    LaBr3->SetMaterialPropertiesTable(crystalMPT);

    // define reflector material
    Teflon = new G4Material("Teflon", 2.2*g/cm3, 2);
    Teflon->AddElement(nist->FindOrBuildElement("C"), 2);
    Teflon->AddElement(nist->FindOrBuildElement("F"), 4);

    AluminumSurface = new G4OpticalSurface("AluminumSurface");    
    AluminumSurface->SetType(dielectric_metal);
    AluminumSurface->SetFinish(ground);
    AluminumSurface->SetModel(unified);
    AluminumSurface->SetPolish(0);
    
    
//97.1. 97.43

    
    G4double reflectivityAluminum[2] = {98, 99};
    G4double rindexAluminum[2]= {1.35, 1.36};
    G4MaterialPropertiesTable *AluminumMPT = new G4MaterialPropertiesTable();
    AluminumMPT->AddProperty("REFLECTIVITY", energy, reflectivityAluminum, 2);
    AluminumMPT->AddProperty("RINDEX", energy, rindexAluminum, 2);
    AluminumSurface->SetMaterialPropertiesTable(AluminumMPT);

    // define detector material
    Glass = nist->FindOrBuildMaterial("G4_GLASS_PLATE");

    G4double reflectivityGlass[2] = {0.04, 0.04};
    G4double rindexGlass[2] = {1.5, 1.52};
    G4MaterialPropertiesTable* glassMPT = new G4MaterialPropertiesTable();
    glassMPT->AddProperty("RINDEX", energy, rindexGlass, 2);
    glassMPT->AddProperty("REFLECTIVITY", energy, reflectivityGlass, 2);
    Glass->SetMaterialPropertiesTable(glassMPT);
}

G4VPhysicalVolume* DetectorConstruction::Construct() {

    // define world
    G4double WorldSize= 150.*cm;

    solidWorld = new G4Box("solidWorld", WorldSize/2, WorldSize/2, WorldSize/2);
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    // general dimensions
    G4double crystal_length= 18.1*mm;
    G4double crystal_radius = 0.5*2.76*mm;
    G4double reflector_thickness = .5*mm;
    G4double detector_thickness = 1.*mm;
    G4double separation = 10*cm;
    // general positions
    G4ThreeVector positionReflector = G4ThreeVector(0.*cm, 0.*cm, separation);
    G4ThreeVector positionReflector1 = G4ThreeVector(0.*cm, 0.*cm, -1*separation);
    G4ThreeVector positionScintillator = G4ThreeVector(0.*cm, 0.*mm, +.5*reflector_thickness*mm-0.02*mm);
    G4ThreeVector positionDetector = G4ThreeVector(0.*cm, 0.*cm, (.5*crystal_length - .5*detector_thickness)*mm);

    // reflector    
    G4Tubs *solidReflector = new G4Tubs("Reflector", 0.*mm, (crystal_radius + reflector_thickness)*mm, (.5*crystal_length + reflector_thickness)*mm, 0.*deg, 360.*deg);
    G4LogicalVolume *logicReflector = new G4LogicalVolume(solidReflector, Aluminum, "Reflector");
    new G4PVPlacement(0, positionReflector, logicReflector, "Reflector", logicWorld, false, 0, true);


    G4VisAttributes *visReflector = new G4VisAttributes(G4Color::White());
    visReflector->SetForceWireframe(true);
    logicReflector->SetVisAttributes(visReflector);
    
    new G4LogicalSkinSurface("ReflectorLogicalSurface", logicReflector, AluminumSurface);
    
     // airbiox
    G4Tubs *airbox = new G4Tubs("airbox", 0.*mm, crystal_radius+0.1*mm, .5*crystal_length + .5*reflector_thickness+0.02*mm, 0.*deg, 360.*deg);
    G4LogicalVolume *logicair = new G4LogicalVolume(airbox, worldMat, "airbox");
    new G4PVPlacement(0, positionScintillator, logicair, "airbox", logicReflector, false, 0, true);
                                                                       
    // scintillator
    G4Tubs *solidScintillator = new G4Tubs("Scintillator", 0.*mm, crystal_radius, .5*crystal_length + .5*reflector_thickness, 0.*deg, 360.*deg);
    G4LogicalVolume *logicScintillator = new G4LogicalVolume(solidScintillator, LaBr3, "Scintillator");
    new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*cm, 0*cm), logicScintillator, "Scintillator", logicair, false, 0, true);


    G4VisAttributes *visScintillator = new G4VisAttributes(G4Color::Red());
    visScintillator->SetForceLineSegmentsPerCircle(25);
    visScintillator->SetForceAuxEdgeVisible(true);
    logicScintillator->SetVisAttributes(visScintillator);

    fScoringEnergy = logicScintillator;

    // detector    
    G4Tubs *solidDetector = new G4Tubs("Detector", 0.*mm, crystal_radius, .5*detector_thickness, 0.*deg, 360.*deg);
    G4LogicalVolume *logicDetector = new G4LogicalVolume(solidDetector, LaBr3, "Detector");
    new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*cm, +(.5*crystal_length -.5*detector_thickness)), logicDetector, "Detector", logicScintillator, false, 0, true);
    
    
    G4VisAttributes *visDetector = new G4VisAttributes(G4Color::Yellow());
    visDetector->SetForceLineSegmentsPerCircle(25);
    visDetector->SetForceAuxEdgeVisible(true);
    logicDetector->SetVisAttributes(visDetector);

    
    /////////////////////////////////////////
   
   
       // reflector    
    G4Tubs *solidReflector1 = new G4Tubs("Reflector1", 0.*mm, (crystal_radius + reflector_thickness)*mm, (.5*crystal_length + reflector_thickness)*mm, 0.*deg, 360.*deg);
    G4LogicalVolume *logicReflector1 = new G4LogicalVolume(solidReflector1, Aluminum, "Reflector1");
    new G4PVPlacement(0, positionReflector1, logicReflector1, "Reflector1", logicWorld, false, 0, true);


    G4VisAttributes *visReflector1 = new G4VisAttributes(G4Color::White());
    visReflector1->SetForceWireframe(true);
    logicReflector1->SetVisAttributes(visReflector1);
    
    new G4LogicalSkinSurface("ReflectorLogicalSurface1", logicReflector1, AluminumSurface);
                   
                       // airbiox
    G4Tubs *airbox1 = new G4Tubs("airbox1", 0.*mm, crystal_radius+0.1*mm, .5*crystal_length + .5*reflector_thickness+0.02*mm, 0.*deg, 360.*deg);
    G4LogicalVolume *logicair1 = new G4LogicalVolume(airbox1, worldMat, "airbox1");
    new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*mm, -(.5*reflector_thickness*mm-0.02*mm)), logicair1, "airbox1", logicReflector1, false, 0, true);
    
                                                        
    // scintillator
    G4Tubs *solidScintillator1 = new G4Tubs("Scintillator1", 0.*mm, crystal_radius, .5*crystal_length + .5*reflector_thickness, 0.*deg, 360.*deg);
    G4LogicalVolume *logicScintillator1 = new G4LogicalVolume(solidScintillator1, LaBr3, "Scintillator1");
    new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*mm, 0*mm), logicScintillator1, "Scintillator1", logicair1, false, 0, true);
    
  

  fScoringEnergy1 = logicScintillator1;
  
    G4VisAttributes *visScintillator1 = new G4VisAttributes(G4Color::Red());
    visScintillator1->SetForceLineSegmentsPerCircle(25);
    visScintillator1->SetForceAuxEdgeVisible(true);
    logicScintillator1->SetVisAttributes(visScintillator1);

   // fScoringEnergy1 = logicScintillator1;

    // detector    
    G4Tubs *solidDetector1 = new G4Tubs("Detector1", 0.*mm, crystal_radius, .5*detector_thickness, 0.*deg, 360.*deg);
    G4LogicalVolume *logicDetector1 = new G4LogicalVolume(solidDetector1, LaBr3, "Detector1");
    new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*cm, -(.5*crystal_length - .5*detector_thickness)), logicDetector1, "Detector1", logicScintillator1, false, 0, true);

//phantom

G4RotationMatrix* fieldRot = new G4RotationMatrix();
fieldRot->rotateX(90.*deg);


G4Tubs *phantomsolid = new G4Tubs("phantom", 0.*mm, .5*25*mm, .5*6*mm, 0.*deg, 360.*deg);	
	G4LogicalVolume* phantomlogic = new G4LogicalVolume(phantomsolid,polyethylene_NEMA,
														"phantom");
	
	//G4ThreeVector positionCrystal1 = G4ThreeVector(0.*cm,0.*cm,
       //                                           0.*cm);
	
	 new G4PVPlacement(fieldRot,G4ThreeVector(0*cm,0.*cm,     0.*cm),phantomlogic,"phantom",
														logicWorld,false,0,true);
		



    G4VisAttributes *visDetector1 = new G4VisAttributes(G4Color::Yellow());
    visDetector1->SetForceLineSegmentsPerCircle(25);
    visDetector1->SetForceAuxEdgeVisible(true);
    logicDetector1->SetVisAttributes(visDetector1);

    fScoringOpticalPhotons = logicDetector;
    fScoringOpticalPhotons1 = logicDetector1;

    return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
    SensitiveDetector* sensDet = new SensitiveDetector("/sensDet");
    G4SDManager *sdManager = G4SDManager::GetSDMpointer(); 
    sdManager->AddNewDetector(sensDet);
    fScoringOpticalPhotons->SetSensitiveDetector(sensDet);


  auto sensDet1 = new SensitiveDetector1("/sensDet1");
  sdManager->AddNewDetector(sensDet1);
  fScoringOpticalPhotons1->SetSensitiveDetector(sensDet1);
  

}
