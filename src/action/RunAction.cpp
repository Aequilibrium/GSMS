//
// C++ Implementation: RunAction
//
// Description: 
//
//
// Author: P.Voylov <pvoilov@aidoss.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "RunAction.h"
#include "detector/Digitizer.h"
#include "detector/Digi.h"
// 
#include <geant/G4DigiManager.hh>

GSMS::RunAction::RunAction()
{
}

GSMS::RunAction::~RunAction()
{
}

G4Run*	GSMS::RunAction::GenerateRun()
{
	return new Run;
}

void	GSMS::RunAction::BeginOfRunAction(const G4Run*)
{
//	G4DigiManager*	fDM = G4DigiManager::GetDMpointer();
//	Digitizer*	myDM = (Digitizer*)fDM->FindDigitizerModule("GSMSDigitizer");
}

void	GSMS::RunAction::EndOfRunAction(const G4Run* aRun)
{
	//const Run*	theRun = (const Run*)aRun;
	Run*	theRun = (Run*)aRun;

	std::vector<G4int>	spectrum;
	for(int i=0; i<1024; i++)
		spectrum.push_back(0L);

	for(int i=0; i< theRun->get_size(); i++)
	{
		G4double time = theRun->get_time(i);
		G4double ene = theRun->get_ene(i);
		G4int	chan = theRun->get_chan(i);
		//std::cout << time << "\t" << chan << "\t" << ene << std::endl;
		spectrum[chan]++;
	}

	if (theRun->get_size()) {
		for(int i=0; i<1024; i++)
			std::cout << spectrum[i] << "\t";
		std::cout << std::endl;
	}
}