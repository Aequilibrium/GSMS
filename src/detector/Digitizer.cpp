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
