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
/*!\file GlobalConfig.h
 * \brief Global configuration
 */
#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

#include "Config.h"

namespace GSMS {
/*!\class GlobalConfig
 * \brief Global configuration unit
 */
class GlobalConfig : public Config
{
	friend class boost::serialization::access;

	/*!\fn serialize(Archive & ar, const unsigned int version)
	 * \param ar output archive
	 * \param version archive version
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar	& BOOST_SERIALIZATION_BASE_OBJECT_NVP(Config)
			& BOOST_SERIALIZATION_NVP(m_time)
			& BOOST_SERIALIZATION_NVP(m_seed);
	}
protected:
	/*!\var G4double m_time
	 * \brief configuration type
	 */
	G4double		m_time;

	/*!\var long m_seed
	 * \brief random engine seed
	 */
	long			m_seed;
	
public:
	/*!\fn GlobalConfig()
	 * \brief default constructor
	 */
	GlobalConfig() : m_time(0.0),m_seed(0L) { m_type = "GlobalConfig";}

	/*!\fn GlobalConfig(std::string type)
	 * \brief specific constructor
	 * \param type configuration instance name
	 */
	GlobalConfig(G4double time, long seed) : m_time(time),m_seed(seed)
	{ m_type = "GlobalConfig";}

	/*!\fn ~GlobalConfig()
	 * \brief default destructor
	 */
virtual	~GlobalConfig() {}

	/*!\fn unsigned int save(std::ofstream* stream)
	 * \brief self-serializer
	 * \param stream output stream
	 * \return exit code
	 */
virtual	unsigned int	save(std::ofstream* stream);

	unsigned int	set_time(G4double*	time)
	{
		unsigned int result = GSMS_OK;
		if(time && (*time) == (*time))
			m_time = *time;
		else
			result = GSMS_ERR;
		return result;
	}

	unsigned int	get_time(G4double*	time)
	{
		unsigned int result = GSMS_OK;
		if(time)
			*time = m_time;
		else
			result = GSMS_ERR;
		return result;
	}
};

}; //namespace GSMS

BOOST_CLASS_VERSION(GSMS::GlobalConfig,1)


#endif /*CONFIG_H*/

