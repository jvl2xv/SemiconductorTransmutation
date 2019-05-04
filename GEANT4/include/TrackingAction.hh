#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class B4aEventAction;
class B4RunAction;

class TrackingAction : public G4UserTrackingAction {

  public:  
    TrackingAction(B4aEventAction* EvAct, B4RunAction* run, G4String  fileName);
   ~TrackingAction();
   
    void  PreUserTrackingAction(const G4Track*);
    void PostUserTrackingAction(const G4Track*);
    void AddFissionToTrackCount() { FissionsInTrack += FissionsInTrack + 1; }
    

    G4String  fileName_a;


  private:
  
    B4aEventAction* evAction; 
    B4RunAction* Run; 

    G4double FissionsInTrack;
    G4double KineticEnergy;         // Declaring variables here allow them to persist 
    G4double Dlength;               // until the particle track is complete
    G4double DEnergy;

};


#endif
