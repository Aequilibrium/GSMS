//
// C++ Interface: Run
//
// Description: 
//
//
// Author: P.Voylov <pvoilov@aidoss.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

/*!\file Run.h
 * \brief Run object
 */
#ifndef RUN_H
#define RUN_H

#include "config/Config.h"
#include <geant/G4Run.hh>
#include <geant/G4THitsMap.hh>

/*!\namespace GSMS
 * \brief Gamma-Scanner Modelling Suite namespace
 */
namespace GSMS {

/*!\class Run
 * \brief Run object
 */
class Run : public G4Run
{
public:
	Run();
virtual	~Run();

virtual	void	RecordEvent(const G4Event*);

private:


//	G4double	get_total(const G4THitsMap<G4double>& map) const;
//	G4double	find_minimum(const G4THitsMap<G4double>& map) const;

//	G4THitsMap<G4double>	mapSum;
//	G4int			colIDSum;

//	G4THitsMap<G4double>	mapMin;
//	G4int			colIDMin;

	std::vector<G4double>	m_ene;
	std::vector<G4double>	m_time;
	std::vector<G4int>	m_chan;
	
public:
const	G4double	get_time(int idx)	{return m_time[idx];}
const	G4int		get_chan(int idx)	{return m_chan[idx];}
const	G4double	get_ene(int idx)	{return m_ene[idx];}
const	int		get_size()		{return m_time.size();}
};

}

#endif /*RUNACTION_H*/