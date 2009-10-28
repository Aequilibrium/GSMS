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
/*!\file Job.h
 * \brief Job configuration entity
 */
#ifndef JOB_H
#define JOB_H

#include "config/Config.h"
#include "generator/Source.h"
#include "config/Exposition.h"

namespace GSMS {

typedef	std::vector<Exposition>::iterator	ExpositionIterator;
typedef	std::vector<Source>::iterator	SourceIterator;

/*!\class Job
 * \brief Job configuration
 */
class Job : public Config
{
	friend class boost::serialization::access;
	/*!\fn serialize(Archive & ar, const unsigned int version)
	 * \brief Job serializer
	 * \param ar output archive
	 * \param version archive version
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar	& BOOST_SERIALIZATION_BASE_OBJECT_NVP(Config)
			& BOOST_SERIALIZATION_NVP(m_duration)
			& BOOST_SERIALIZATION_NVP(m_sources)
			& BOOST_SERIALIZATION_NVP(m_expositions);
	}

protected:
	/*!\var m_duration
	 * \brief experiment duration
	 */
	unsigned char	m_duration;

	/*!\var m_sources
	 * \brief sources' list
	 */
	std::vector<Source>	m_sources;

	/*!\var m_expositions
	 * \brief expositions' list
	 */
	std::vector<Exposition>	m_expositions;

public:
	/*!\fn Job()
	 * \brief Default constructor
	 */
	Job() : m_duration(0.0)
	{
		m_type = "Job";
//		Source	src;
//		m_sources.push_back(src);

		Exposition	exposition;
		m_expositions.push_back(exposition);
	}

	/*!\fn Job()
	 * \brief Specific constructor
	 */
	Job(G4double duration) : m_duration(duration)
	{
		m_type = "Job";
	}

	/*!\fn ~Job()
	 * \brief Default destructor
	 */
	~Job() {}

	/*!\fn unsigned int save(std::ofstream* stream)
	 * \brief Self-serializer
	 * \param stream output stream
	 * \return exit code
	 */
virtual unsigned int	save(std::ofstream* stream);

	/*!\fn SourceIterator	get_source_iterator()
	 * \brief Sources iterator
	 * \return iterator of sources vector
	 */
inline	SourceIterator	get_source_iterator() {
		SourceIterator	it = m_sources.begin();
		return it;
	}

	/*!\fn unsigned int	get_source_count()
	 * \brief Number of sources
	 * \return number of sources
	 */
inline	unsigned int	get_source_count() {
		return m_sources.size();
	}

	/*!\fn void	push_source(Source&	source)
	 * \brief Add source to the magazine
	 * \param source instance of a source
	 */
inline	void	push_source(Source&	source) {
		m_sources.push_back(source);
	}

	/*!\fn ExpositionIterator	get_exposition_iterator()
	 * \brief Expositions iterator
	 * \return iterator over expositions vector
	 */
inline	ExpositionIterator	get_exposition_iterator() {
		ExpositionIterator	it = m_expositions.begin();
		return it;
	}

	/*!\fn unsigned int	get_exposition_count()
	 * \brief Number of expositions
	 * \return number of expositions
	 */
inline	unsigned int	get_exposition_count() {
		return m_expositions.size();
	}

	/*!\fn void	push_exposition(Exposition&	exposition)
	 * \brief Add exposition to the magazine
	 * \param source instance of an exposition
	 */
inline	void	push_exposition(Exposition	exposition) {
		m_expositions.push_back(exposition);
	}

	/*!\fn Exposition&	get_active_exposition()
	 * \brief Obtain current (localtime-related) exposition
	 * \return active exposition
	 */
	Exposition&	get_active_exposition();

	/*!\fn Exposition*	get_active_exposition_ptr()
	 * \brief Obtain current (localtime-related) exposition pointer
	 * \return active exposition
	 */
	Exposition*	get_active_exposition_ptr();

};

}; //namespace GSMS

BOOST_CLASS_VERSION(GSMS::Job,1)

#endif /*JOBCONFIG_H*/

