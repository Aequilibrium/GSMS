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

/*!\file Generator.h
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <geant/G4GeneralParticleSource.hh>
#include <geant/G4VUserPrimaryGeneratorAction.hh>

#include "generator/SourceLib.h"
#include "generator/Source.h"

namespace GSMS {

class Generator : public G4VUserPrimaryGeneratorAction
{
	G4GeneralParticleSource*	mp_gps;
public:
	Generator();
	~Generator();
	void	GeneratePrimaries(G4Event*	anEvent); 
	void	Update();
};

}; /*namespace GSMS*/

#endif /*GENERATOR_H_*/
