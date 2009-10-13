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

#include "SceneConfig.h"
#include <sys/stat.h>
#include <sys/types.h>

#include <geant/G4VSolid.hh>
#include <geant/G4Box.hh>
#include <geant/G4LogicalVolume.hh>
#include <geant/G4PVPlacement.hh>
#include <geant/G4ThreeVector.hh>

#include "config/GSMS.h"

unsigned int	GSMS::SceneConfig::save(std::ofstream* stream)
{
	SceneConfig*	pSceneConfig = this;
	boost::archive::xml_oarchive out(*stream);
	out << BOOST_SERIALIZATION_NVP(pSceneConfig);
}

unsigned int	GSMS::SceneConfig::initWorld()
{
	try
	{
		G4Material*	material = NULL;
		if(GSMS::GSMS::getMaterial(m_wmat,&material) != GSMS_OK)
			return GSMS_ERR;
		G4VSolid*	world_box = new G4Box("world_box",0.5*m_wwidth,0.5*m_wlength,0.5*m_wheight);
		G4LogicalVolume* world_log = new G4LogicalVolume(world_box, material,"world_log");
		mp_world = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), "world_phys", world_log, NULL, false, 0);
	}
	catch(...)
	{return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::SceneConfig::getWorld(G4VPhysicalVolume** world)
{
	if(!world)
		return GSMS_ERR;
	try
	{
		if(!mp_world)
			initWorld();
		*world = mp_world;
	}
	catch(...)
	{
		return GSMS_ERR;
	}
	return GSMS_OK;
}
