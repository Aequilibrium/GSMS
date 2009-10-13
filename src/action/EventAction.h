//
// C++ Interface: EventAction
//
// Description: 
//
//
// Author: P.Voylov <pvoilov@aidoss.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

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