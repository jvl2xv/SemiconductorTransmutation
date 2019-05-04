//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B4DetectorConstruction.cc 87359 2014-12-01 16:04:27Z gcosmo $
// 
/// \file B4DetectorConstruction.cc
/// \brief Implementation of the B4DetectorConstruction class 

#include "B4DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


#include "G4Region.hh"



// CADMESH //
#include "G4String.hh"
#include "G4ThreeVector.hh"
#include "G4TessellatedSolid.hh"
#include "G4TriangularFacet.hh"
#include "G4Tet.hh"
#include "G4AssemblyVolume.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4UIcommand.hh"

// GEANT4 //
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AssemblyVolume.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"

#include "G4RegionStore.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* B4DetectorConstruction::fMagFieldMessenger = 0; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::B4DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::~B4DetectorConstruction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4DetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4DetectorConstruction::DefineMaterials()
{ 
  // Lead material defined using NIST Manager
  G4NistManager* nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_Pb");
  

  // Print materials
  //G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4DetectorConstruction::DefineVolumes()
{
  // Geometry parameters

  G4NistManager* nistManager = G4NistManager::Instance();

  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density; 

  // Get materials
  //G4Material* G4_water = nistManager->FindOrBuildMaterial("G4_WATER");
  G4Material* G4_Ar = nistManager->FindOrBuildMaterial("G4_Ar");
  G4Material* G4_air = nistManager->FindOrBuildMaterial("G4_AIR");
  G4Material* G4_Aluminum = nistManager->FindOrBuildMaterial("G4_Al");
  G4Material* G4_Graphite = nistManager->FindOrBuildMaterial("G4_GRAPHITE");
  G4Material* G4_Polyethylene = nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* G4_StainlessSteel = nistManager->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Material* G4_Water = nistManager->FindOrBuildMaterial("G4_WATER");
  G4Material* G4_Zirconium = nistManager->FindOrBuildMaterial("G4_Zr"); 
  G4Material* G4_Helium = nistManager->FindOrBuildMaterial("G4_He"); 
  G4Material* G4_Galactic =  nistManager->FindOrBuildMaterial("G4_Galactic"); 
  G4Material* G4_Silicon = nistManager->FindOrBuildMaterial("G4_Si");
  G4Material* G4_Kapton = nistManager->FindOrBuildMaterial("G4_KAPTON");
  G4Material* G4_Lead = nistManager->FindOrBuildMaterial("G4_Pb");
  

  density = 7.43*(g / cm3); // http://www.stsci.edu/hst/wfc3/documents/ISRs/WFC3-2009-44.pdf
  G4double fracMass;
  G4int natoms;
  G4Material* HgCdTe_material = new G4Material ("HgCdTe_material", density, 3); 
  G4Element* elHg = new G4Element ("Mercury", "Hg", 80, 200.59*g/mole);
  G4Element* elCd = new G4Element ("Cadmium", "Cd", 48, 112.411*g/mole);
  G4Element* elTe = new G4Element ("Tellerium", "Te", 52, 127.6*g/mole);
  HgCdTe_material->AddElement(elHg, fracMass=(100.0*.7/2.0)*perCent);
  HgCdTe_material->AddElement(elCd, fracMass=(100.0*.3/2.0)*perCent);
  HgCdTe_material->AddElement(elTe, fracMass=(100.0*1.0/2.0)*perCent);

  density = 5.67945*(g / cm3); // http://www.semiconductors.co.uk/propiiiv5653.htm
  G4Material* InAsSb_material = new G4Material ("InAsSb_material", density, 3); 
  G4Element* elIn = new G4Element ("Indium", "In", 49, 114.818*g/mole);
  G4Element* elAs = new G4Element ("Arsenic", "As", 33, 74.9216*g/mole);
  G4Element* elSb = new G4Element ("Antimony", "Sb", 51, 121.76*g/mole);
  InAsSb_material->AddElement(elIn, fracMass=(100.0*1.0/2.0)*perCent);
  InAsSb_material->AddElement(elAs, fracMass=(100.0*.91/2.0)*perCent);
  InAsSb_material->AddElement(elSb, fracMass=(100.0*.09/2.0)*perCent);

  density = 6.64*(g / cm3); // http://www.semiconductors.co.uk/propiiiv5653.htm
  G4Material* InSbBi_material_HighBi = new G4Material ("InSbBi_material_HighBi", density, 3); 
  G4Element* elBi = new G4Element ("Bismuth", "Bi", 83, 208.9804*g/mole);
  InSbBi_material_HighBi ->AddElement(elIn, fracMass=(100.0*1.0/2.0)*perCent);
  InSbBi_material_HighBi ->AddElement(elSb, fracMass=(100.0*.5/2.0)*perCent);
  InSbBi_material_HighBi ->AddElement(elBi, fracMass=(100.0*.5/2.0)*perCent);
  
  density = 5.87*(g / cm3); // http://www.semiconductors.co.uk/propiiiv5653.htm
  G4Material* InSbBi_material_LowBi  = new G4Material ("InSbBi_material_LowBi", density, 3); 
  InSbBi_material_LowBi->AddElement(elIn, fracMass=(100.0*1.0/2.0)*perCent);
  InSbBi_material_LowBi->AddElement(elSb, fracMass=(100.0*.95/2.0)*perCent);
  InSbBi_material_LowBi->AddElement(elBi, fracMass=(100.0*.05/2.0)*perCent);

  density = 5.68*(g / cm3); //http://www.ioffe.ru/SVA/NSM/Semicond/InAs/basic.html
  G4Material* InAs_material  = new G4Material ("InAs_material", density, 2); 
  InAs_material->AddElement(elIn, fracMass=(100.0*.5)*perCent);
  InAs_material->AddElement(elAs, fracMass=(100.0*.5)*perCent);


  density = 5.77*(g / cm3); //http://www.ioffe.ru/SVA/NSM/Semicond/InSb/basic.html
  G4Material* InSb_material  = new G4Material ("InSb_material", density, 2); 
  InSb_material->AddElement(elIn, fracMass=(100.0*.5)*perCent);
  InSb_material->AddElement(elSb, fracMass=(100.0*.5)*perCent);

  

  G4Material* GaAs_material = nistManager->FindOrBuildMaterial("G4_GALLIUM_ARSENIDE"); 
  GaAs_material->SetName("GaAs_material");


  G4Material* SuperDenseBeryllium = new G4Material ("SuperDenseBeryllium", 4.01*(g / cm3), 1); 
  G4Element* elBe = new G4Element ("Beryllium", "Be", 4, a=9.01*g/mole);
  SuperDenseBeryllium->AddElement(elBe, natoms=1);

  G4Material* G4_Bi = nistManager->FindOrBuildMaterial("G4_Bi"); 

  G4Material* Si_material = nistManager->FindOrBuildMaterial("G4_Si"); 
  Si_material->SetName("Si_material");

  // Define air of required density


      G4Material* materials [8] = {InAs_material, HgCdTe_material, InAsSb_material, InSbBi_material_HighBi, InSbBi_material_LowBi, GaAs_material, Si_material, InSb_material};

    



  
  //     
  // World
  //

  
 
  G4Box* world_solid
    = new G4Box("World", 100.0*cm, 100.0*cm, 100.0*cm); // its size
                         
  G4LogicalVolume* world_logical
    = new G4LogicalVolume(
                 world_solid,           // its solid
                 G4_Galactic,  // its material
                 "World");         // its name
                                   
  G4VPhysicalVolume* world_physical
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 world_logical,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  
  G4double half_width = ((1.0)/2.0)*cm;
  G4double half_thickness = ((0.5)/2.0)*mm;

  


  G4Material* semiconductor_material = materials[matNum];

     
  G4Box* Semiconductor_solid
    = new G4Box("semiconductor_sample",half_width,half_width, half_thickness);  // half-thickness
  G4LogicalVolume* Semiconductor_logical
    = new G4LogicalVolume(
                 Semiconductor_solid,      // its solid
                 semiconductor_material,     // its material
                 "semiconductor_sample");         // its name                                 
  G4VPhysicalVolume* Semiconductor_physical
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0.,0., 0.),  
                 Semiconductor_logical,           // its logical volume                         
                 "semiconductor_sample",       // its name
                 world_logical,    // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 









 /* G4Box* detectorWall_solid
    = new G4Box("detector", 1.9*m, 1.9*m, 0.01*cm); // its size, half-thicknesses (thickness is 5 mm), the 10 cm is arbitrary but matches the cargo, 30 mm depth
                         
  G4LogicalVolume* detectorWall_logical
    = new G4LogicalVolume(
                 detectorWall_solid,           // its solid
                 G4_Lead,  // its material
                 "detector");         // its name
                                   
  G4VPhysicalVolume* detectorWall_physical
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0.0*m,0.0*m,-1.9*m),  // at (0,0,0)
                 detectorWall_logical,          // its logical volume                         
                 "detector",          // its name
                 world_logical,   // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps */
  


  
 


  return world_physical;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4DetectorConstruction::ConstructSDandField()
{ 
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue = G4ThreeVector();
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}


 void B4DetectorConstruction::SetParameters(G4int mn) 
    {
        matNum = mn;
    }





  














//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
