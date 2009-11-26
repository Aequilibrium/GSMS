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
/*!\file DetectorConfig.h
 * \brief Detector configuration entity
 */
#ifndef DETECTORCONFIG_H
#define DETECTORCONFIG_H

#include "Config.h"
#include <geant/G4VPhysicalVolume.hh>

namespace GSMS {
/*!\class DetectorConfig
 * \brief Detector configuration
 */
class DetectorConfig : public PhysObjConfig
{
	friend class boost::serialization::access;

	/*!\fn serialize(Archive & ar, const unsigned int version)
	 * \brief Mask serializer
	 * \param ar output archive
	 * \param version archive version
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar	& BOOST_SERIALIZATION_BASE_OBJECT_NVP(PhysObjConfig)
			& BOOST_SERIALIZATION_NVP(m_radius)
			& BOOST_SERIALIZATION_NVP(m_mirror_thick)
			& BOOST_SERIALIZATION_NVP(m_shirt_thick)
			& BOOST_SERIALIZATION_NVP(m_resolution);
		if(m_shape == "Cyllinder")
			ar & BOOST_SERIALIZATION_NVP(m_height);

	}
protected:

	/*!\var m_resolution
	 * \brief crystal resolution
	 */
	G4float	m_resolution;

	/*!\var m_radius
	 * \brief crystal radius
	 */
	G4float	m_radius;

	/*!\var m_height
	 * \brief crystal height (for cyllinder, prism)
	 */
	G4float	m_height;

	/*!\var m_mirror_thick
	 * \brief mirror thickness
	 */
	G4float	m_mirror_thick;

	/*!\var m_shirt_thick
	 * \brief shirt thickness
	 */
	G4float	m_shirt_thick;

public:
	/*!\fn DetectorConfig(G4double resolution)
	 * \brief Specific constructor
	 * \param resolution crystal resolution
	 */
	DetectorConfig(std::string material = "CsI",G4float resolution = 0.085) :
		m_resolution(resolution)
		{
			m_type = "DetectorConfig";
			m_material = material;
			m_radius =		25.0*mm;
			m_height =		100.0*mm;
			m_mirror_thick =	1.0*mm;
			m_shirt_thick =		3.0*mm;
		}

	/*!\fn ~DetectorConfig()
	 * \brief Default destructor
	 */
	~DetectorConfig() {}

	/*!\fn unsigned int save(std::ofstream* stream)
	 * \brief Self-serializer
	 * \param stream output stream
	 * \return exit code
	 */
virtual	unsigned int	save(std::ofstream* stream);

	/*!\fn unsigned int imprint(G4VPhysicalVolume* world)
	 * \brief build detector in world
	 * \param world world ptr
	 */
	unsigned int imprint(G4VPhysicalVolume* world = NULL);

};

}; //namespace GSMS

BOOST_CLASS_VERSION(GSMS::DetectorConfig,1)

#endif /*DETECTORCONFIG_H*/

