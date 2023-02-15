#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

namespace B1
{

class RunAction;

class EventAction : public G4UserEventAction
{
public:
    EventAction(/*RunAction* runAction*/);
    ~EventAction() override;
    
    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;
    
    
private:
//    RunAction* fRunAction = nullptr;
    G4double  fEnergyDeposit = 0.;

};



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


