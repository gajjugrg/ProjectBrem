#ifndef BremEventAction_h
#define BremEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

namespace Brem
{

class RunAction;

class EventAction : public G4UserEventAction
{
public:
    EventAction(/*RunAction* runAction*/);
    ~EventAction() override;
    
    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;
    
    void AddTrack(G4double le);
    inline G4double GetTrackLength(){ return fTrackLength; }
    
    
private:
//    RunAction* fRunAction = nullptr;
//    G4double  fEnergyDeposit = 0.;
//    G4int fTrackID = 0;
    G4double fTrackLength = 0.;

};

inline void EventAction::AddTrack(G4double le){
    fTrackLength += le;
}



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


