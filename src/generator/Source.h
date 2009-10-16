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
/*!\file Source.h
 * \brief Source configuration
 */
#ifndef SOURCE_H
#define SOURCE_H

#include "config/Config.h"
#include <geant/G4ThreeVector.hh>
#include <geant/G4SingleParticleSource.hh>
#include <geant/G4GeneralParticleSource.hh>

namespace GSMS {
/*!\class Source
 * \brief Source configuration
 */
class Source : public LogObjConfig
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
			& BOOST_SERIALIZATION_NVP(m_activity)
			& BOOST_SERIALIZATION_NVP(m_name)
			& BOOST_SERIALIZATION_NVP(m_gamma)
			& BOOST_SERIALIZATION_NVP(m_beta)
			& BOOST_SERIALIZATION_NVP(m_electron);
	}
protected:

	/*!\var m_activity
	 * \brief source activity
	 */
	float	m_activity;

	/*!\var m_name
	 * \brief source name
	 */
	std::string	m_name;

	/*!\var m_gamma
	 * \brief gamma spectrum with (Energy;Output) pair
	 */
	std::vector<std::pair<G4float, G4float> >	m_gamma;

	/*!\var m_beta
	 * \brief beta spectrum with (EnergyMax;Output) pair
	 */
	std::vector<std::pair<G4float, G4float> >	m_beta;

	/*!\var m_electron
	 * \brief electron spectrum with (Energy;Output) pair
	 */
	std::vector<std::pair<G4float, G4float> >	m_electron;

	/*!\var m_trajectory
	 * \brief trajectory with (Position;Speed;) pair
	 */


public:
	/*!\fn Source()
	 * \brief Default constructor
	 */
	Source() :
		LogObjConfig(),
		m_activity(1.0), m_name("undefined")
		{m_type = "SourceConfig"; //m_gamma.push_backinsert(std::pair<G4float,G4float>(1.0,100));}
			}

	/*!\fn Source(G4double activity)
	 * \brief Specific constructor
	 * \param activity source activity
	 * \param name source name
	 * \param X X coord
	 * \param Y Y coord
	 * \param Z Z coord
	 */
	Source(G4double activity, std::string name, G4ThreeVector coords) :
		LogObjConfig(),
		m_activity(activity),
		m_name(name)
		{m_type = "Source";
		set_x(coords.getX()),
		set_y(coords.getY()),
		set_z(coords.getZ());}

	/*!\fn ~Source()
	 * \brief Default destructor
	 */
virtual	~Source() {}

	/*!\fn unsigned int save(std::ofstream* stream)
	 * \brief Self-serializer
	 * \param stream output stream
	 * \return exit code
	 */
virtual unsigned int	save(std::ofstream* stream);

	/*!\fn std::map<G4float, G4float>::iterator	get_gamma_iterator()
	 * \brief obtain iterator for gamma lines
	 * \return iterator
	 */
inline	std::vector<std::pair<G4float, G4float> >::iterator	get_gamma_iterator() {
		std::vector<std::pair<G4float, G4float> >::iterator it = m_gamma.begin(); return it;}

	/*!\fn std::map<G4float, G4float>::iterator	get_beta_iterator()
	 * \brief obtain iterator for continuous beta spectra
	 * \return iterator
	 */
inline	std::vector<std::pair<G4float, G4float> >::iterator	get_beta_iterator() {
		std::vector<std::pair<G4float, G4float> >::iterator it = m_beta.begin(); return it;}

	/*!\fn std::map<G4float, G4float>::iterator	get_electron_iterator()
	 * \brief obtain iterator for discrete electron lines
	 * \return iterator
	 */
inline	std::vector<std::pair<G4float, G4float> >::iterator	get_electron_iterator() {
		std::vector<std::pair<G4float, G4float> >::iterator it = m_electron.begin(); return it;}

	/*!\fn float	get_activity()
	 * \brief obtain activity of the source
	 * \return activity
	 */
inline	float get_activity() {return m_activity;}

	/*!\fn void	set_activity()
	 * \brief set activity of the source
	 * \param float new activity
	 */
inline	void set_activity(float activity) {m_activity = activity;}

	/*!\fn std::string	get_name()
	 * \brief obtain name of the source
	 * \return name
	 */
inline	std::string get_name() {return m_name;}

	/*!\fn void	set_name()
	 * \brief set name of the source
	 * \param std::string new name
	 */
inline	void set_name(std::string name) {m_name = name;}


	/*!\fn G4ThreeVector	get_coords()
	 * \brief obtain source coords
	 * \return coords
	 */
inline	G4ThreeVector get_coords() {return G4ThreeVector(m_x, m_y, m_z);}

	/*!\fn float	set_coords()
	 * \brief set source coords
	 * \param G4ThreeVector new coords
	 */
inline	void set_coords(G4ThreeVector coords) {m_x = coords.getX(), m_y = coords.getY(), m_z = coords.getZ();}

	/*!\fn int	push_gamma()
	 * \brief add gamma line
	 * \param float	energy
	 * \param float	intensity
	 * \return index
	 */
inline	int push_gamma(float ene, float intensity) { m_gamma.push_back(std::pair<G4float, G4float>(ene, intensity));}

	/*!\fn void	generate_G4(G4GeneralParticleSource*);
	 * \brief creates G4SPS object with given parameters
	 * \param G4GeneralParticleSource*	target generator
	 */
void	generate_G4(G4GeneralParticleSource* tgt, G4double angle = 0.0);

	/*!\fn void	normalize_activities();
	 * \brief normalize activities
	 */
void	normalize_activities();

};

}; //namespace GSMS

BOOST_CLASS_VERSION(GSMS::Source,1)

#endif /*SOURCECONFIG_H*/

