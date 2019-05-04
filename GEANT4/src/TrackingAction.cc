#include "TrackingAction.hh"
#include "B4aEventAction.hh"
#include "B4aSteppingAction.hh"
#include "B4RunAction.hh"
#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
//#include "AIDA/AIDA.h"



#include "B4aSteppingAction.hh"
#include "B4aEventAction.hh"
#include "B4DetectorConstruction.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4VParticleChange.hh"
#include "B4RunAction.hh"
#include "G4Decay.hh"
//#include "G4RadioActiveDecay.hh"


#include "G4ElectronIonPair.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

#include "Randomize.hh"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdio.h> 
#include <math.h>


using namespace std;



TrackingAction::TrackingAction(B4aEventAction* EvAct, B4RunAction* run, G4String fileName)
:evAction(EvAct), Run(run)
{ 
fileName_a = fileName;
}


TrackingAction::~TrackingAction()
{ }

void TrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{

	const G4ParticleDefinition * particleDef = aTrack->GetParticleDefinition();
	G4String particleName = particleDef->GetParticleName();
	G4int atomicNumber = particleDef->GetAtomicNumber();

          //get event #
          G4int eID = 0;
          const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();
          if(evt) eID = evt->GetEventID();
          G4int trackID = aTrack->GetTrackID();





	if(atomicNumber > 1) {
          std::ostringstream commandOS;
          commandOS << "Shielding_63MeV_100000000_pencil_p5mm1cm1cm" << fileName_a << ".txt";
          
          G4double creationTime = aTrack->GetGlobalTime()/second;
        
        
          std::ofstream ofile;
          ofile.open (G4String(commandOS.str()), ios::out | ios::app);     // ascii file    
          ofile << aTrack->GetLogicalVolumeAtVertex()->GetMaterial()->GetName() << " " << eID << " " << aTrack->GetTrackID() << " " << particleName << " "  << creationTime  << endl;

          commandOS.str("");

        
		
        

          
       }


}


void TrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{

}



