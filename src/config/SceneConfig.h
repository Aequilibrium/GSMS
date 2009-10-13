/***************************************************************************
 *   Copyright (C) 2009 by P.Voylov   *
 *   pvoilov@aidoss.com   *
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
/*!\file SceneConfig.h
 * \brief Scene configuration entity
 */
#ifndef SCENECONFIG_H
#define SCENECONFIG_H

#include "Config.h"
#include <geant/G4LogicalVolume.hh>
#include <geant/G4VPhysicalVolume.hh>

namespace GSMS {
/*!\class SceneConfig
 * \brief Scene configuration
 */
class SceneConfig : public Config
{
	friend class boost::serialization::access;
	/*!\fn serialize(Archive & ar, const unsigned int version)
	 * \brief Scene serializer
	 * \param ar output archive
	 * \param version archive version
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar	& BOOST_SERIALIZATION_BASE_OBJECT_NVP(Config)
			& BOOST_SERIALIZATION_NVP(m_wwidth)
			& BOOST_SERIALIZATION_NVP(m_wlength)
			& BOOST_SERIALIZATION_NVP(m_wheight)
			& BOOST_SERIALIZATION_NVP(m_wmat)
			& BOOST_SERIALIZATION_NVP(m_objects);
	}

protected:

	/*!\var m_objects
	 * \brief objects' list
	 */
	std::vector<PhysObjConfig>	m_objects;

	/*!\var m_wwidth
	 * \brief world width
	 */
	G4float	m_wwidth;

	/*!\var m_length
	 * \brief world length
	 */
	G4float	m_wlength;

	/*!\var m_wheight
	 * \brief world height
	 */
	G4float	m_wheight;

	/*!\var m_wmat
	 * \brief world material
	 */
	std::string	m_wmat;

	/*!\var mp_world
	 * \brief world pointer
	 */
	G4VPhysicalVolume*	mp_world;

	/*!\fn unsigned int initWorld()
	 * \brief initiate world
	 * \return exit code
	 */
	unsigned int	initWorld();

public:
	/*!\fn SceneConfig()
	 * \brief Default constructor
	 */
	SceneConfig() : m_wwidth(100.0*m),m_wlength(100.0*m),m_wheight(100.0*m),m_wmat("Air"),mp_world(NULL)
	{
		m_type = "SceneConfig";
		PhysObjConfig	obj;
		m_objects.push_back(obj);
	}

	/*!\fn ~SceneConfig()
	 * \brief Default destructor
	 */
	~SceneConfig()
	{
	}

	/*!\fn unsigned int save(std::ofstream* stream)
	 * \brief Self-serializer
	 * \param stream output stream
	 * \return exit code
	 */
virtual unsigned int	save(std::ofstream* stream);

	/*!\fn unsigned int getWorld(G4VPhysicalVolume* world)
	 * \brief initiate world
	 * \param world world pointer (out)
	 * \return exit code
	 */
	unsigned int	getWorld(G4VPhysicalVolume** world);

};

}; //namespace GSMS

BOOST_CLASS_VERSION(GSMS::SceneConfig,1)

#endif /*SCENECONFIG_H*/

