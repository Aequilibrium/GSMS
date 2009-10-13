//
// C++ Implementation: Digitizer
//
// Description: 
//
//
// Author: P.Voylov <pvoilov@aidoss.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "Digitizer.h"

#include <geant/G4EventManager.hh>
#include <geant/G4Event.hh>
#include <geant/G4SDManager.hh>
#include <geant/G4DigiManager.hh>
#include <geant/G4Poisson.hh>
#include <geant/G4ios.hh>

#include <vector>

GSMS::Digitizer::Digitizer(G4String	name) : G4VDigitizerModule(name), m_dnu(10), m_stime(0.0), m_etime(10.0) {
	G4String	colName = "DigitsCollection";
	
	collectionName.push_back(colName);
}

GSMS::Digitizer::~Digitizer() {}

void	GSMS::Digitizer::Digitize() {

	m_coll = new DigitsCollection("GSMSDigitizer", "DigitsCollection");

	G4DigiManager*	digiMan = G4DigiManager::GetDMpointer();

	G4int	hCollID = digiMan->GetHitsCollectionID("eDep");

	G4THitsMap<G4double>* evtMap = NULL;
	evtMap = (G4THitsMap<G4double>*)(digiMan->GetHitsCollection(hCollID));

	if(!evtMap) return;

	
	std::map<G4int, G4double*>::iterator itr = evtMap->GetMap()->begin();
	for(; itr != evtMap->GetMap()->end(); itr++) {

		G4double	eneDep = *(itr->second);
		G4double	eneChan = 0;
//		if (eneChan > 10.)
//		{
			double dResCs137 = 0.085;//ResolutionScale;
			G4double dResA = std::sqrt(0.662)*dResCs137;
			double dRes = dResA/std::sqrt(eneDep);//ResolutionScale;
			
			G4double sigma = dRes*eneDep/2.355;
//			std::cerr << "Mean: " << eneDep << ", Sigma: " << sigma << ", Res: " << dRes;
			eneChan = G4RandGauss::shoot(eneDep,sigma) / 3 * 1024;
//			std::cerr << ", Value: "  << eneChan << std::endl;
//		}
//		else
//		{
//			eneChan = G4int(G4Poisson(eneChan));
//		};

//		std::cerr << ", Channel: "  << eneChan;

		G4double	time = G4UniformRand() * (m_etime - m_stime);

		if(eneChan >= m_dnu)
		{
			Digi*	digi = new Digi;
			digi->set_time(time);
			digi->set_channel(int(eneChan));
			digi->set_ene(eneDep);
			m_coll->insert(digi);
		}
	}

	StoreDigiCollection(m_coll);
}
