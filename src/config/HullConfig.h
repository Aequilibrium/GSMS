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
/*!\file HullConfig.h
 * \brief Hull configuration entity
 */
#ifndef HULLCONFIG_H
#define HULLCONFIG_H

#include "Config.h"

namespace GSMS {

/*!\class HullConfig
 * \brief Hull configuration
 */
class HullConfig : public LogObjConfig
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
		ar	& BOOST_SERIALIZATION_BASE_OBJECT_NVP(LogObjConfig)
			& BOOST_SERIALIZATION_NVP(m_radius)
			& BOOST_SERIALIZATION_NVP(m_height);
	}
protected:
	/*!\var m_radius
	 * \brief hull radius
	 */
	G4double	m_radius;

	/*!\var m_height
	 * \brief height
	 */
	G4double	m_height;

public:
	/*!\fn HullConfig()
	 * \brief Default constructor
	 */
	HullConfig() :
		m_radius(0.0),
		m_height(0.0)
		{m_type = "HullConfig";}

	/*!\fn HullConfig(G4double radius,G4double height)
	 * \brief Specific constructor
	 * \param radius radius
	 * \param height height
	 */
	HullConfig(G4double radius, G4double height) :
		m_radius(radius),
		m_height(height)
		{m_type = "HullConfig";}

	/*!\fn ~HullConfig()
	 * \brief Default destructor
	 */
	~HullConfig() {}

	/*!\fn unsigned int save(std::ofstream* stream)
	 * \brief Self-serializer
	 * \param stream output stream
	 * \return exit code
	 */
virtual unsigned int	save(std::ofstream* stream);
};

}; //namespace GSMS

BOOST_CLASS_VERSION(GSMS::HullConfig,1)

#endif /*HULLCONFIG_H*/

