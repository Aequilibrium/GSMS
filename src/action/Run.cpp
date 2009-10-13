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
#include "Run.h"
#include <geant/G4Event.hh>
#include <geant/G4HCofThisEvent.hh>
#include <geant/G4SDManager.hh>
#include "detector/Digitizer.h"
#include "detector/Digi.h"
#include <geant/G4DigiManager.hh>

GSMS::Run::Run()
{
	
//	G4SDManager*	sdman = G4SDManager::GetSDMpointer();
//	colIDSum = sdman->GetCollectionID("crystal/eDep");
}

GSMS::Run::~Run()
{
}

void	GSMS::Run::RecordEvent(const G4Event* evt)
{

	G4DigiManager*	digiMan = G4DigiManager::GetDMpointer();

	int DCID = -1;
	DCID = digiMan->GetDigiCollectionID("GSMSDigitizer/DigitsCollection");
	DigitsCollection*	DC = (DigitsCollection*)digiMan->GetDigiCollection(DCID);

	if(DC)
		for(int i=0; i< DC->GetSize(); i++)
		{
			G4double	time = (*DC)[i]->get_time();
			G4double	ene = (*DC)[i]->get_ene();
			G4int		chan = (*DC)[i]->get_channel();
			//std::pair<G4double, G4int>	score(time, channel);
			m_time.push_back(time);
			m_ene.push_back(ene);
			m_chan.push_back(chan);
		}
}
/*
G4double	GSMS::Run::get_total(const G4THitsMap<G4double>& map) const
{
	G4double	tot = 0.0;
	std::map<G4int, G4double*>::iterator itr = map.GetMap()->begin();
	for(; itr != map.GetMap()->end();itr++)
	{
		tot += *(itr->second);
	}
	return tot;
}

G4double	GSMS::Run::find_minimum(const G4THitsMap<G4double>& map) const
{
	G4double	val = DBL_MAX;
	std::map<G4int, G4double*>::iterator itr = map.GetMap()->begin();
	for(; itr != map.GetMap()->end();itr++)
	{
		if(val > *(itr->second)) val = *(itr->second);
	}

	return val;
}

*/