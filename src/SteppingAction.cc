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

namespace Brem
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
          
      
      G4Track* track = step->GetTrack();
      
      if (track->GetTrackID()== 1){
        
          G4cout << "PID: " << track->GetDefinition()->GetParticleName() << G4endl;
          auto edep = step->GetTotalEnergyDeposit();
          auto trk  = track->GetTrackID();
          
          G4cout << "Track id is: " << trk << G4endl;
          G4cout << "Edep in current step (MeV): " << edep/CLHEP::keV << G4endl;
          G4cout << "Position X: " << track->GetPosition().getX()/CLHEP::cm << ", Y: " << track->GetPosition().getY()/CLHEP::cm << ", Z: " << track->GetPosition().getZ()/CLHEP::cm << G4endl;
          
          // refer the analysisManager of current session
          auto analysisManager = G4AnalysisManager::Instance();
          // Save the <edep> variable content in the first TTree leave.
          analysisManager->FillNtupleDColumn(0, edep);
          analysisManager->FillNtupleIColumn(1, trk);
          // Finish writing TTree for an event.
          analysisManager->AddNtupleRow();
      }
      if(track->GetTrackID() !=1){
          track->SetTrackStatus(fStopAndKill);
      }
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
