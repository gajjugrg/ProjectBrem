#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
// #include "Run.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
    // set printing event number per each event
      G4RunManager::GetRunManager()->SetPrintProgress(1);
    // inform the runManager to save random number seed
    //G4RunManager::GetRunManager()->SetRandomNumberStore(false);
      // Get analysis manager
      auto analysisManager = G4AnalysisManager::Instance();
      
      // Create directories
      //analysisManager->SetHistoDirectoryName("histograms");
      //analysisManager->SetNtupleDirectoryName("ntuple");
      analysisManager->SetVerboseLevel(1);
      analysisManager->SetNtupleMerging(true);
      

      // Creating ntuple
      //
      analysisManager->CreateNtuple("brem", "Edep and TrackL");
      analysisManager->CreateNtupleDColumn("fEnergyDeposit");
//      analysisManager->CreateNtupleDColumn("fEnergyIni");
//      analysisManager->CreateNtupleDColumn("fTrackLength");
//      analysisManager->CreateNtupleSColumn("fProcess");
    
      analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{
    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    // open an outputfile
    G4String fileName = "bremOutput.root";
    

    analysisManager->OpenFile(fileName);
    G4cout << "Using " << analysisManager->GetType() << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
}
