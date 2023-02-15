#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4AnalysisManager.hh"

class G4Run;

namespace B1
{

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    ~RunAction() override;

    void BeginOfRunAction(const G4Run*) override;
    void   EndOfRunAction(const G4Run*) override;
    
    
private:

};

}

#endif

