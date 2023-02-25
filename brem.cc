#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "G4Version.hh"
// version dependent header files
#if G4VERSION_NUMBER != 1100
#include "G4MTRunManager.hh"  // for G4_10
#else
#include "G4RunManagerFactory.hh" // for G4_11
#endif

#include "G4SteppingVerbose.hh"
#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4Version.hh"

#include "Randomize.hh"

using namespace Brem;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
    G4UIExecutive* ui = nullptr;
    if ( argc == 1 ) { ui = new G4UIExecutive(argc, argv); }
    
//    auto* runManager =
//    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
    // version dependent function call
#if G4VERSION_NUMBER == 1100
    G4int precision = 4;
    G4SteppingVerbose::UseBestUnit(precision);
#endif
    
//    // Construct the default run manager
#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(2*(G4Threading::G4GetNumberOfCores()));
    G4cout << "Multithreaded" << G4endl;
#else
    G4RunManager* runManager = new G4RunManager;
    G4cout << "Single threaded" << G4endl;
#endif
    //
    // Set mandatory initialization classes
    //
    // Detector construction
    runManager->SetUserInitialization(new DetectorConstruction());
    
    // Physics list
    G4VModularPhysicsList* physicsList = new QBBC;
    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList);
    
    runManager->SetUserInitialization(new ActionInitialization());
    // Initialize visualization
    //
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();
    
    G4cout << "Version: " << G4VERSION_NUMBER << G4endl;
    // Detect interactive mode (if no arguments) and define UI session

    
    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    
    if ( ! ui ) {
//         batch mode
         G4String command = "/control/execute ";
         G4String fileName = argv[1];
         UImanager->ApplyCommand(command+fileName);
    }
    else {
        //interactive mode
        UImanager->ApplyCommand("/control/execute init_vis.mac");
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
