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
/*!\file Waypoint.h
 * \brief Waypoint configuration
 */
#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "config/Config.h"
#include <geant/G4ThreeVector.hh>

namespace GSMS {

/*!\class Waypoint
 * \brief Waypoint configuration
 */
class Waypoint : public LogObjConfig
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
			& BOOST_SERIALIZATION_NVP(m_stance)
			& BOOST_SERIALIZATION_NVP(m_duration);
	}
protected:

	/*!\var m_stance
	 * \brief waypoint activity type
	 */
	std::string	m_stance;

	/*!\var m_duration
	 * \brief activity duration
	 */
	float	m_duration;

public:
	/*!\fn Waypoint()
	 * \brief Default constructor
	 */
	Waypoint() : LogObjConfig(),
		m_stance("Idle"), m_duration(0.0)
		{m_type = "Waypoint";
			}

	/*!\fn Waypoint(std::string stance, G4float duration, G4ThreeVector position)
	 * \brief Specific constructor
	 * \param stance source activity
	 * \param duration source name
	 * \param position coordinates
	 */
	Waypoint(std::string stance, G4float duration, G4ThreeVector position) :
		LogObjConfig(),
		m_stance(stance),
		m_duration(duration)
		{m_type = "Waypoint"; m_x = position.getX(), m_y = position.getY(), m_z = position.getZ();}

	/*!\fn ~Waypoint()
	 * \brief Default destructor
	 */
virtual	~Waypoint() {}

	/*!\fn unsigned int save(std::ofstream* stream)
	 * \brief Self-serializer
	 * \param stream output stream
	 * \return exit code
	 */
virtual unsigned int	save(std::ofstream* stream);

	/*!\fn float	get_duration()
	 * \brief obtain duration of the activity
	 * \return duration
	 */
inline	G4float get_duration() {return m_duration;}

	/*!\fn float	set_duration()
	 * \brief set duration of the activity
	 * \param G4float new duration
	 */
inline	void set_duration(G4float duration) {m_duration = duration;}

	/*!\fn std::string	get_stance()
	 * \brief obtain kind of activity
	 * \return stance
	 */
inline	std::string get_stance() {return m_stance;}

	/*!\fn void	set_stance()
	 * \brief set kind of activity
	 * \param std::string new stance
	 */
inline	void set_stance(std::string stance) {m_stance = stance;}

	/*!\fn G4ThreeVector	get_coords()
	 * \brief obtain coords
	 * \return coords
	 */
inline	G4ThreeVector get_coords() {return G4ThreeVector(m_x, m_y, m_z);}

	/*!\fn float	set_coords()
	 * \brief set coords
	 * \param G4ThreeVector new coords
	 */
inline	void set_coords(G4ThreeVector coords) {set_x(coords.getX()), set_y(coords.getY()), set_z(coords.getZ());}

};

}; //namespace GSMS

BOOST_CLASS_VERSION(GSMS::Waypoint,1)

#endif /*WAYPOINTCONFIG_H*/