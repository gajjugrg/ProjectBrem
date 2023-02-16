#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
//#include "G4AnalysisManager.hh"  // G4_11
#include "g4root.hh"  // G4_10
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

namespace Brem
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(/*RunAction* runAction*/)
//: fRunAction(runAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{

    fEnergyDeposit = 0.;
    fTrackID = 0;
//    fTrackLength = 0.;
//    fProcessName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
    
    
    // Accumulate statistics
    //
    
    // get analysis manager

    auto analysisManager = G4AnalysisManager::Instance();
    
    // fill ntuple
    analysisManager->FillNtupleDColumn(0, fEnergyDeposit);
    analysisManager->FillNtupleIColumn(1, fTrackID);
//    analysisManager->FillNtupleDColumn(2, fTrackLength);
//    analysisManager->FillNtupleSColumn(3, fProcessName);
    analysisManager->AddNtupleRow();
    
}


}
