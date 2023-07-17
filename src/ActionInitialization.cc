#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

namespace Brem
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization()
  : fOutputFileNamePtr(nullptr)
{}

ActionInitialization::ActionInitialization(const G4String* outputFileNamePtr)
  : fOutputFileNamePtr(outputFileNamePtr)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{
	RunAction* runAction;
 if( fOutputFileNamePtr != nullptr)
  runAction = new RunAction(fOutputFileNamePtr);
 else 
   runAction = new RunAction();
	SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{
	SetUserAction(new PrimaryGeneratorAction());
    RunAction* runAction; 
	if (fOutputFileNamePtr != nullptr)
    runAction = new RunAction(fOutputFileNamePtr);
  else 
    runAction = new RunAction;
	SetUserAction(runAction);
	auto eventAction = new EventAction;
	SetUserAction(eventAction);
	SetUserAction(new SteppingAction(eventAction));
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
