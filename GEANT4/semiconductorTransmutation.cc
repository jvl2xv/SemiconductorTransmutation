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
// 

// REQUIRED GEANT HEADER FILES

#include "B4DetectorConstruction.hh"
#include "B4aActionInitialization.hh"
#include "TrackingAction.hh"
#include "G4SystemOfUnits.hh"
#include "PhysicsList.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "FTFP_BERT.hh"
#include "Randomize.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4ScoringManager.hh"
#include "G4PhysListFactory.hh"
#include "G4Box.hh"


// Additional physics
/*#include "PhysListEmStandard.hh"
#include "PhysListEmStandardSS.hh"
#include "PhysListEmStandardISS.hh"
#include "PhysListEmStandardNR.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmStandardPhysicsWVI.hh"
#include "G4EmStandardPhysicsGS.hh"
#include "G4EmStandardPhysicsSS.hh"
#include "G4RadioactiveDecay.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "LBE.hh"
#include "G4VModularPhysicsList.hh" */

#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmLowEPPhysics.hh"

#include "G4DecayPhysics.hh"

#include "G4HadronElasticPhysics.hh"
#include "G4HadronDElasticPhysics.hh"
#include "G4HadronHElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4IonPhysics.hh"

#include "QGSP_BERT.hh"





// REQUIRED C++ HEADER FILES FOR IO AND MATH

#include <math.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <cmath>

using namespace std;



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

namespace {
  void PrintUsage() {
    G4cerr << " Usage: " << G4endl;
    // now -m macro stores the a of the loop to append to file to avoid overlapping lines
    G4cerr << " myMesh [-m macro ] [-u UIsession] [-t nThreads]" << G4endl;
    G4cerr << "   note: -t option is available only for multi-threaded mode."
           << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Evaluate arguments

  if ( argc > 7 ) {
    PrintUsage();
    return 1;
  }
  
  G4String macro;
  G4String session;
#ifdef G4MULTITHREADED
  G4int nThreads = 1;
#endif
  for ( G4int i=1; i<argc; i=i+2 ) {
    if      ( G4String(argv[i]) == "-m" ) macro = argv[i+1];
    else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
#ifdef G4MULTITHREADED
    else if ( G4String(argv[i]) == "-t" ) {
      nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
    }
#endif
    else {
      PrintUsage();
      return 1;
    }
  }  
  
  // Detect interactive mode (if no macro provided) and define UI session
  
  G4UIExecutive* ui = 0;
  if ( ! macro.size() ) {
    ui = new G4UIExecutive(argc, argv, session);
  }

  // Choose the Random engine
  
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
  // Construct the default run manager (multithread)
  
  #ifdef G4MULTITHREADED
    G4MTRunManager * runManager = new G4MTRunManager;
    if ( nThreads > 0 ) { 
      runManager->SetNumberOfThreads(nThreads);
    }  
  #else
    G4RunManager * runManager = new G4RunManager;
  #endif



  // Initialize the required clases 
  
  // UI create a mesh if you want to use this
  G4ScoringManager* scoringManager = G4ScoringManager::GetScoringManager();
  // Register the physics list
  G4int verbose = 1;
  G4PhysListFactory factory;

  // PHYSICS 1
  G4VModularPhysicsList* physicsList = factory.GetReferencePhysList("Shielding");

  // PHYSICS 2
  //G4VModularPhysicsList* physicsList = factory.GetReferencePhysList("FTF_BIC_EMY");
  //physicsList->RegisterPhysics( new G4RadioactiveDecayPhysics() );


  // PHYSICS 3
  //G4VModularPhysicsList* physicsList = factory.GetReferencePhysList("QGSP_INCLXX_HP");
  //physicsList->RegisterPhysics( new G4RadioactiveDecayPhysics() );
  


  //physicsList->RegisterPhysics( new PhysListEmStandardNR );
  //physicsList->RegisterPhysics( new PhysListEmStandardISS );

  
  //G4VModularPhysicsList*  physicsList  = factory.GetReferencePhysList("QBBC");
  
  

  //physicsList->ReplacePhysics(new PhysListEmStandardISS);
  //physicsList->RegisterPhysics(new G4EmStandardPhysics_option4());
  //physicsList->RegisterPhysics(new PhysListEmStandardSS());
  //physicsList->RegisterPhysics(new PhysListEmStandardNR());
  //PhysicsList* physicsList = new PhysicsList();
  //physicsList->SetCuts();
  //physicsList->AddPhysicsList("standardNR");
    //QGSP_BERT *physicsList = new QGSP_BERT;
    //LBE *physicsList = new LBE;
    //physicsList->RegisterPhysics( new G4RadioactiveDecayPhysics );
    //physicsList->RegisterPhysics(new G4EmStandardPhysics_option4());
    //physicsList->RegisterPhysics(new PhysListEmStandardSS());
    //physicsList->RegisterPhysics(new PhysListEmStandardNR());
    //G4VPhysicsConstructor*   physicsList = new PhysListEmStandardNR();


 

 
  runManager->SetUserInitialization(physicsList);
  //physicsList->DumpList();


  // Register the pointer to the visualization manager
  G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  // To run use this instead of a macro, use the -m specifier and say that the macro name is julieRun
  if ( macro.size() ) {
    if (true) {

      // initialize a random seed
      srand(time(NULL));

        
      // initialize building a string (for c++ UI stuff)
      G4String command = "";
      std::ostringstream commandOS;


     for (G4int matNum=0; matNum < 8; matNum = matNum + 1) {

        

     
        B4DetectorConstruction* detConstruction = new B4DetectorConstruction();
        //detConstruction->DefineVolumes();
        detConstruction->SetParameters(matNum);
        detConstruction->Construct();
        runManager->SetUserInitialization(detConstruction);


        // set the action initialization
        B4aActionInitialization* actionInitialization = new B4aActionInitialization(detConstruction, macro);
        // register the action initialization
        runManager->SetUserInitialization(actionInitialization);


        // initialization commands for geant (just applying what would be in the macro file)
        UImanager->ApplyCommand("/run/reinitializeGeometry");


        // initialization commands for geant (just applying what would be in the macro file)
        UImanager->ApplyCommand("/run/initialize");
        UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1 ");
        UImanager->ApplyCommand("/vis/disable");
        UImanager->ApplyCommand("/run/verbose 0");
        UImanager->ApplyCommand("/event/verbose 0");
        UImanager->ApplyCommand("/process/verbose 0");
        UImanager->ApplyCommand("/vis/verbose 0");
        UImanager->ApplyCommand("/tracking/verbose 0");

        // set particle colors (in case vis is desired, not necessary for me)
        UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID");
        UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set neutron red");
        UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set e- yellow");
        UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set gamma blue");

          G4double posX = 0.0;
          G4double posY = 0.0;
          G4double posZ = 0.0;

          // Z A Q E 

          // https://web-docs.gsi.de/~wolle/FISSION/cf252/node2.html 
          // charge: https://www.tandfonline.com/doi/pdf/10.1080/00223131.2012.677127
                // charge = A_fragment*Z_compound/A_compound

          //command = "/gps/ion 98 252 0 0.0 ";

          // LIGHT
          /*command = "/gps/ion 44 109 43 0.0 ";
          UImanager->ApplyCommand(command);
          cout << command << endl;
          command = "/gps/energy 103.5 MeV";
          UImanager->ApplyCommand(command);
          cout << command << endl; */
          
          // HEAVY
          
          //command = "/gps/ion 56 143 55 0.0 ";
          //UImanager->ApplyCommand(command);
          //cout << command << endl;
          //command = "/gps/energy 78.3 MeV";
          //UImanager->ApplyCommand(command);
          //cout << command << endl; 


          command = "/gps/particle proton";
          UImanager->ApplyCommand(command);
          cout << command << endl;
          command = "/gps/energy 63.0 MeV";
          UImanager->ApplyCommand(command);
          cout << command << endl;




          command = "/gps/position 0 0 -5.0 cm";
          UImanager->ApplyCommand(command);
          cout << command << endl;

          command = "/gps/pos/type Point";
          UImanager->ApplyCommand(command);
          cout << command << endl;


          command = "/gps/direction 0 0 1";
          UImanager->ApplyCommand(command);
          cout << command << endl;
          

          /*command = "/run/setCutForAGivenParticle proton 0.1 mm";
          UImanager->ApplyCommand(command);
          cout << command << endl; */

          command = "/run/initialize";
          UImanager->ApplyCommand(command);
          cout << command << endl;

          command = "/run/particle/dumpCutValues";
          UImanager->ApplyCommand(command);
          cout << command << endl;



          std::random_device rd;
          std::mt19937 gen(rd());
          std::uniform_int_distribution<> dis(0, 1000000000);

          G4int rand1 = dis(gen);
          G4int rand2 = dis(gen);

          cout << "My random numbers were " << rand1 << " " << rand2 << endl;
          commandOS << "/random/setSeeds " << rand1 << " " << rand2;
          UImanager->ApplyCommand(G4String(commandOS.str()));
          commandOS.str("");



          commandOS << "/run/beamOn 100000000";
          UImanager->ApplyCommand(G4String(commandOS.str()));
          cout << G4String(commandOS.str()) << endl;
          commandOS.str("");


}
    
  }
    else {
    // batch mode
    G4String command = "/control/execute ";
    UImanager->ApplyCommand(command+macro); }
  }
  else  {  

      G4String command = "";
      std::ostringstream commandOS;


        // if I want to see the geometry, run without the command line argument

        B4DetectorConstruction* detConstruction = new B4DetectorConstruction();
        detConstruction->DefineVolumes();
        // register the detector
        runManager->SetUserInitialization(detConstruction);
        // set the action initialization
        B4aActionInitialization* actionInitialization = new B4aActionInitialization(detConstruction, macro);
        // register the action initialization
        runManager->SetUserInitialization(actionInitialization);

        G4double posX = 0.0;
          G4double posY = 0.0;
          G4double posZ = 0.0;

          command = "/gps/particle alpha";
          UImanager->ApplyCommand(command);

          command = "/gps/pos/type Surface";
          UImanager->ApplyCommand(command);

          command = "/gps/pos/shape Cylinder";
          UImanager->ApplyCommand(command);

          commandOS << "/gps/pos/centre " << posX << " " << posY << " " << posZ << " " << " cm";
          UImanager->ApplyCommand(G4String(commandOS.str()));
          commandOS.str("");

          command = "/gps/pos/radius 2.0 cm";
          UImanager->ApplyCommand(command);

          command = "/gps/pos/halfz 0.5 mm";
          UImanager->ApplyCommand(command);

          command = "/gps/ang/type iso";
          UImanager->ApplyCommand(command);

          command = "/gps/energy 5.486 MeV";
          UImanager->ApplyCommand(command);

          commandOS << "/run/beamOn 5000000";
          UImanager->ApplyCommand(G4String(commandOS.str()));
          commandOS.str("");

          command = "/run/setCutForAGivenParticle proton 0.001 mm";
          UImanager->ApplyCommand(command);
          cout << command << endl;

          command = "/run/initialize";
          UImanager->ApplyCommand(command);
          cout << command << endl;



    // interactive mode : define UI session
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    if (ui->IsGUI()) {
      UImanager->ApplyCommand("/control/execute gui.mac");
    }
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !

  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
