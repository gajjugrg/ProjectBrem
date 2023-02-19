#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"


// version dependent header files
#if G4VERSION_NUMBER != 1100
#include "g4root.hh" // for G4_10
#elif
#include "G4AnalysisManager.hh" // for G4_11
#endif

namespace Brem
{

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  SteppingAction::SteppingAction(EventAction* eventAction)
    :fEventAction(eventAction)
  {}

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  SteppingAction::SteppingAction(EventAction* eventAction, G4double initEnergy)
    :fEventAction(eventAction),
    fInitEnergy(initEnergy)
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
      
      // identify primary track
      if (track->GetTrackID()== 1){
        
//          G4cout << "PID: " << track->GetDefinition()->GetParticleName() << G4endl;
//          auto edep = step->GetTotalEnergyDeposit();
//          auto trkID  = track->GetTrackID();
          auto trkLength = track ->GetTrackLength();
          auto ProcName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

          //fEventAction->AddTrack(trkLength);
          //G4cout << "In the current step, track ID is: " << track->GetTrackID() << ", track length: " << trkLength << " was added to fTrackLength, which is currently: " << fEventAction->GetTrackLength() << G4endl;

          // Prepare analysis manager
          auto analysisManager = G4AnalysisManager::Instance();
          if(ProcName == "eBrem"){
            G4cout << "========================= A BREMSSTRAHLUNG EVENT ====================================" << G4endl;
            // save the data
            G4cout << "A bremsstrahlung from primary particle has been recorded." << G4endl;
            G4cout << "fTrackLength: " << trkLength << G4endl;
            analysisManager->FillNtupleDColumn(0, fInitEnergy);
            analysisManager->FillNtupleDColumn(1, trkLength/CLHEP::cm);
            analysisManager->AddNtupleRow();

            // kill the process
            track->SetTrackStatus(fStopAndKill);
          }
//
//          G4cout << "trkLength is: " << trkLength << " & Post Step Process is: "  << ProcName << G4endl;
//          G4cout << "Track id is: " << trkID << G4endl;
//          G4cout << "Edep in current step (MeV): " << edep/CLHEP::keV << G4endl;
//          G4cout << "Position X: " << track->GetPosition().getX()/CLHEP::cm << ", Y: " << track->GetPosition().getY()/CLHEP::cm << ", Z: " << track->GetPosition().getZ()/CLHEP::cm << G4endl;
//
//          // refer the analysisManager of current session
//          auto analysisManager = G4AnalysisManager::Instance();
//          // Save the <edep> variable content in the first TTree leave.
//          analysisManager->FillNtupleDColumn(0, edep);
//          analysisManager->FillNtupleIColumn(1, trkID);
//          analysisManager->FillNtupleDColumn(2,trkLength);
//          // Finish writing TTree for an event.
//          analysisManager->AddNtupleRow();
      }
      else if( track->GetTrackID() != 1 )
      {
          track->SetTrackStatus(fStopAndKill);
      }
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
