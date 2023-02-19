#ifndef BremSteppingAction_h
#define BremSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4LogicalVolume;

/// Stepping action class
///

namespace Brem
{

class EventAction;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(EventAction* eventAction);
    SteppingAction(EventAction* eventAction, G4double initEnergy);
    ~SteppingAction() override;

    // method from the base class
    void UserSteppingAction(const G4Step* step) override;

  private:
    EventAction* fEventAction = nullptr;
    G4double fInitEnergy;
};

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
