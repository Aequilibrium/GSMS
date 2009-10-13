/***************************************************************************
 *   Copyright (C) 2009 by P.Voylov                                        *
 *   pvoilov@aidoss.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
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