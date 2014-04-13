#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "TH1D.h"

class RunAction : public G4UserRunAction
{
public:
  RunAction();
 ~RunAction();

public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

  TH1D* hist;
};

#endif // RUNACTION_HH
