#ifndef BremActionInitialization_h
#define BremActionInitialization_h 1

#include "G4Types.hh"
#include "G4VUserActionInitialization.hh"
#include "G4String.hh"

/// Action initialization class.

namespace Brem
{

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization();
    ActionInitialization(const G4String* outputFileNamePtr);
    ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    const G4String* fOutputFileNamePtr;
};

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
