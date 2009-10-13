//
// C++ Implementation: EventAction
//
// Description: 
//
//
// Author: P.Voylov <pvoilov@aidoss.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

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