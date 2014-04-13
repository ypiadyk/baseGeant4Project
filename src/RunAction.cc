#include "RunAction.hh"
#include "TFile.h"

RunAction::RunAction()
{

}

RunAction::~RunAction()
{

}

void RunAction::BeginOfRunAction(const G4Run *)
{
    hist = new TH1D("hist", "hist", 1000, 0, 3000);
}

void RunAction::EndOfRunAction(const G4Run *)
{
    TFile* f = new TFile("spectrum.root", "recreate");
    hist->Write();
    f->Write();
    // new line
}
