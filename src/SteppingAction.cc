#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "G4Version.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"


// version dependent header files
#if G4VERSION_NUMBER != 1100
#include "g4root.hh" // for G4_10
#else
#include "G4AnalysisManager.hh" // for G4_11
#endif

namespace Brem
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//SteppingAction::SteppingAction(EventAction* eventAction)
//:fEventAction(eventAction)
//{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* , G4double initEnergy)
:fInitEnergy(initEnergy)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    //storing the tracklength and energy information.
    G4Track* track = step->GetTrack();
    
    // identify primary track
    if (track->GetTrackID()== 1){
        
        //          G4cout << "PID: " << track->GetDefinition()->GetParticleName() << G4endl;
        auto fKineticEnergy = track->GetKineticEnergy();
        auto trkLength = track ->GetTrackLength();
        auto ProcName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
        
        // Prepare analysis manager
        auto analysisManager = G4AnalysisManager::Instance();
        if(fKineticEnergy/CLHEP::MeV < 1){ track->SetTrackStatus(fStopAndKill);}
        else
        {  // save the data
            G4cout << "******************* Data is recorded **********************" << G4endl;
            G4cout << "fTrackLength: " << trkLength/CLHEP::cm << " cm, Kinetic Energy: " << fKineticEnergy/CLHEP::MeV << " MeV, Process Name: " << ProcName << G4endl;
            analysisManager->FillNtupleIColumn(0, track->GetTrackID());
            analysisManager->FillNtupleDColumn(1, fKineticEnergy/CLHEP::MeV);
            analysisManager->FillNtupleDColumn(2, (trkLength/CLHEP::cm)/ 18.85);
            analysisManager->FillNtupleSColumn(3, ProcName);
            analysisManager->AddNtupleRow();
        }
    }
    else if( track->GetTrackID() != 1 )
    {
        track->SetTrackStatus(fStopAndKill);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
