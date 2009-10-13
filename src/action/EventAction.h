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
/*!\file EventAction.h
 * \brief Event HC processor
 */
#ifndef EVENTACTION_H
#define EVENTACTION_H

#include "config/Config.h"
#include <geant/G4UserEventAction.hh>
#include <geant/G4THitsMap.hh>

/*!\namespace GSMS
 * \brief Gamma-Scanner Modelling Suite namespace
 */
namespace GSMS {

/*!\class EventAction
 * \brief Event processor
 */
class EventAction : public G4UserEventAction
{
	G4int	m_collID;

	G4double	get_total(const G4THitsMap<G4double>& map) const;
	G4double	find_minimum(const G4THitsMap<G4double>& map) const;

	G4THitsMap<G4double>	map;
	G4int			colID;

public:
	EventAction();
virtual	~EventAction();

	
virtual	void	BeginOfEventAction(const G4Event*);
virtual	void	EndOfEventAction(const G4Event*);
};

}

#endif /*EVENTACTION_H*/