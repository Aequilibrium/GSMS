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
/*!\file Hull.h
 * \brief Hull configuration entity
 */
#ifndef HULL_H
#define HULL_H

#include "Config.h"
#include <geant/G4ThreeVector.hh>

class	G4VPhysicalVolume;
class	G4Touchable;
class	G4Material;

namespace GSMS {

/*!\class Hull
 * \brief Hull configuration
 */
class Hull : public LogObjConfig
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
			& BOOST_SERIALIZATION_NVP(m_height)
			& BOOST_SERIALIZATION_NVP(m_thickness)
			& BOOST_SERIALIZATION_NVP(m_gap)
			& BOOST_SERIALIZATION_NVP(m_hat_height)
			& BOOST_SERIALIZATION_NVP(m_top_radius);
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

	/*!\var m_thickness
	 * \brief thickness
	 */
	G4double	m_thickness;

	/*!\var m_gap
	 * \brief air gap
	 */
	G4double	m_gap;

	/*!\var m_hat_height
	 * \brief height of the cone hat
	 */
	G4double	m_hat_height;

	/*!\var m_top_radius
	 * \brief upper radius of the cone hat
	 */
	G4double	m_top_radius;


public:
	/*!\fn Hull()
	 * \brief Default constructor
	 */
	Hull() : LogObjConfig(),
		m_radius(-1.0),
		m_height(-1.0),
		m_thickness(1.0*mm),
		m_gap(2.0*cm),
		m_hat_height(15.*cm),
		m_top_radius(12.*cm)
		{m_type = "HullConfig";}

	/*!\fn Hull(G4double radius,G4double height)
	 * \brief Specific constructor
	 * \param radius radius
	 * \param height height
	 */
	Hull(G4double radius, G4double height) :
		LogObjConfig(),
		m_radius(radius),
		m_height(height),
		m_thickness(1.0*mm),
		m_gap(2.0*cm),
		m_hat_height(0.*cm),
		m_top_radius(0.*cm)
		{m_type = "HullConfig";}

	/*!\fn ~Hull()
	 * \brief Default destructor
	 */
	~Hull() {}

	/*!\fn unsigned int save(std::ofstream* stream)
	 * \brief Self-serializer
	 * \param stream output stream
	 * \return exit code
	 */
virtual unsigned int	save(std::ofstream* stream);

	/*!\fn 	unsigned int imprint(G4VPhysicalVolume*	wptr)
	 * \bried dump hull geometry
	 * \param wptr world pointer
	 * \return exit code
	 */
	unsigned int	imprint(G4VPhysicalVolume*	wptr = NULL);

	double	get_delta_phi(G4ThreeVector	coords);
	double	get_delta_theta(G4ThreeVector	coords);
	double	get_dist(G4ThreeVector	coords);

};

}; //namespace GSMS

BOOST_CLASS_VERSION(GSMS::Hull,1)

#endif /*HULL_H*/

