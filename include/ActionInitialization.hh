#ifndef BremActionInitialization_h
#define BremActionInitialization_h 1

#include "G4Types.hh"
#include "G4VUserActionInitialization.hh"

/// Action initialization class.

namespace Brem
{

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization();
    ~ActionInitialization() override;

    void BuildForMaster() const override;
    void Build() const override;

  private:
};

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
