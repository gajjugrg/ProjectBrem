#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
//#include "g4root.hh" // for G4_10
#include "G4AnalysisManager.hh" // for G4_11

namespace B1
{

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  SteppingAction::SteppingAction(EventAction* /*eventAction*/)
    //:fEventAction(eventAction)
  {}

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  SteppingAction::~SteppingAction()
  {}

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void SteppingAction::UserSteppingAction(const G4Step* step)
  {
    // store total energy deposit of the current step in variable <edep>
    auto edep = step->GetTotalEnergyDeposit();
    G4cout << "Edep in current step (MeV): " << edep/CLHEP::MeV << G4endl;

    // refer the analysisManager of current session
    auto analysisManager = G4AnalysisManager::Instance();
    // Save the <edep> variable content in the first TTree leave.
    analysisManager->FillNtupleDColumn(0, edep);
    // Finish writing TTree for an event.
    analysisManager->AddNtupleRow();
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
