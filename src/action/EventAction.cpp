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
#include "EventAction.h"
#include "detector/Digi.h"
#include "detector/Digitizer.h"

#include <geant/G4Event.hh>
#include <geant/G4EventManager.hh>
#include <geant/G4HCofThisEvent.hh>
#include <geant/G4VHitsCollection.hh>
#include <geant/G4VVisManager.hh>
#include <geant/G4SDManager.hh>
#include <geant/G4DigiManager.hh>

GSMS::EventAction::EventAction() : m_collID(-1) {
	G4DigiManager*	fDM = G4DigiManager::GetDMpointer();
	Digitizer*	myDM = new Digitizer("GSMSDigitizer");
	fDM->AddNewModule(myDM);
}

GSMS::EventAction::~EventAction() {

}

void	GSMS::EventAction::BeginOfEventAction(const G4Event*	evt) {
	G4int	evtNb = evt->GetEventID();
//	std::cerr << "Event: " << evtNb << std::endl;

	G4SDManager*	sdman = G4SDManager::GetSDMpointer();
	colID = sdman->GetCollectionID("crystal/eDep");

//	std::cerr << "Coll ID: " << colID << std::endl;
}

void	GSMS::EventAction::EndOfEventAction(const G4Event*	evt) {


	G4HCofThisEvent*	HCE = evt->GetHCofThisEvent();
	if(!HCE) return;


	G4THitsMap<G4double>* evtMap = (G4THitsMap<G4double>*)(HCE->GetHC(colID));

	G4DigiManager*	fDM = G4DigiManager::GetDMpointer();
	Digitizer*	myDM = (Digitizer*)fDM->FindDigitizerModule("GSMSDigitizer");
	myDM->Digitize();

/*
	map = *evtMap;

	std::cerr << "Size: " << map.GetMap()->size() << std::endl;

	G4double	tot = 0.0;
	std::map<G4int, G4double*>::iterator itr = map.GetMap()->begin();
	for(; itr != map.GetMap()->end();itr++)
	{
		tot = *(itr->second);
	}

	std::cerr << "eDep: " << tot << std::endl;
*/

//	std::cerr << "Hits Collection: " << m_collID << std::endl;
//	G4int	dCollID = fDM->GetDigiCollectionID("DigitsCollecton");
//	std::cerr << "Digits Collection: " << dCollID << std::endl;
//	DigitsCollection*	DC = (DigitsCollection*)fDM->GetDigiCollection(dCollID);

}