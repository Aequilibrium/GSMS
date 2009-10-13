//
// C++ Interface: Digitizer
//
// Description: 
//
//
// Author: P.Voylov <pvoilov@aidoss.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef DIGITIZER_H_
#define	DIGITIZER_H_

#include <geant/G4THitsMap.hh>

#include <geant/G4VDigitizerModule.hh>
#include "detector/Digi.h"
#include <geant/globals.hh>

namespace GSMS {

class Digitizer : public G4VDigitizerModule {

public:
	Digitizer(G4String name);
	~Digitizer();

	void	Digitize();
	void	set_DNU(G4int	dnu) {m_dnu = dnu;}

private:
	G4int			m_dnu;
	DigitsCollection*	m_coll;

	G4double		m_stime;
	G4double		m_etime;
	G4double		m_intensity;

};

}

#endif