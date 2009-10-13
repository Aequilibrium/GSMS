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