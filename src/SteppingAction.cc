#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "g4root.hh" // for G4_10
//#include "G4AnalysisManager.hh" // for G4_11

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
    G4Track* track = step->GetTrack();
    G4cout << "PID: " << track->GetDefinition()->GetParticleName() << G4endl;
    auto edep = step->GetTotalEnergyDeposit();
    G4cout << "Edep in current step (MeV): " << edep/CLHEP::keV << G4endl;
    G4cout << "Position X: " << track->GetPosition().getX()/CLHEP::cm << ", Y: " << track->GetPosition().getY()/CLHEP::cm << ", Z: " << track->GetPosition().getZ()/CLHEP::cm << G4endl;

    /*
    // a lesson for class

    class A
    {
      double A::SomeFunction()
      {
        ...
          return something;
      }
    };

    A a;
    a.SomeFunction(); // this okay
    a->SomeFunction(); // this is not allowed.
    A* a = new A();
    a.SomeFunction(); // this is not allowed.
    a->SomeFunction(); // this is okay.
    */

    // refer the analysisManager of current session
    auto analysisManager = G4AnalysisManager::Instance();
    // Save the <edep> variable content in the first TTree leave.
    analysisManager->FillNtupleDColumn(0, edep);
    // Finish writing TTree for an event.
    analysisManager->AddNtupleRow();
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
