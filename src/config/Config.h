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
/*!\file Config.h
 * \brief Primary configuration entities
 */
#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>

#include <geant/globals.hh>
#include <geant/G4ios.hh>

#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/base_object.hpp>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include "typedefs.h"

/*!\namespace GSMS
 * \brief Gamma-Scanner Modelling Suite namespace
 */
namespace GSMS {
/*!\class Config
 * \brief Base configuration unit
 */
class Config
{
	friend class boost::serialization::access;

	/*!\fn serialize(Archive & ar, const unsigned int version)
	 * \param ar output archive
	 * \param version archive version
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar	& BOOST_SERIALIZATION_NVP(m_type);
	}
protected:
	/*!\var std::string m_type
	 * \brief configuration type
	 */
	std::string		m_type;

public:
	/*!\fn Config()
	 * \brief default constructor
	 */
	Config() : m_type("Config") {}

	/*!\fn Config(std::string type)
	 * \brief specific constructor
	 * \param type configuration instance name
	 */
	Config(std::string type) : m_type(type) {}

	/*!\fn ~Config()
	 * \brief default destructor
	 */
virtual	~Config() {}

	/*!\fn unsigned int save(std::ofstream* stream)
	 * \brief self-serializer
	 * \param stream output stream
	 * \return exit code
	 */
virtual	unsigned int	save(std::ofstream* stream);

};

class LogObjConfig : public Config
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar	& BOOST_SERIALIZATION_BASE_OBJECT_NVP(Config)
			& BOOST_SERIALIZATION_NVP(m_x)
			& BOOST_SERIALIZATION_NVP(m_y)
			& BOOST_SERIALIZATION_NVP(m_z)
			& BOOST_SERIALIZATION_NVP(m_rho)
			& BOOST_SERIALIZATION_NVP(m_theta)
			& BOOST_SERIALIZATION_NVP(m_phi);
	}
protected:
	float		m_x;
	float		m_y;
	float		m_z;
	float		m_rho;
	float		m_theta;
	float		m_phi;
public:
	/*!\fn LogObjConfig()
	 * \brief default constructor
	 */
	LogObjConfig() : m_x(0.0),m_y(0.0),m_z(0.0),m_rho(0.0),m_theta(0.0),m_phi(0.0)
		{m_type = "LogObj";}

	/*!\fn LogObjConfig(float x, float y, float z, float rho, float theta, float phi)
	 * \brief specific constructor
	 * \param x X coordinate
	 * \param y Y coordinate
	 * \param z Z coordinate
	 * \param rho Rho angle
	 * \param theta Theta angle
	 * \param phi Phi angle
	 */
	LogObjConfig(float x, float y, float z, float rho=0.0, float theta=0.0, float phi=0.0) : m_x(x),m_y(y),m_z(z),m_rho(rho),m_theta(theta),m_phi(phi)
		{m_type = "LogObj";}

	/*!\fn ~LogObjConfig()
	 * \brief default destructor
	 */
virtual	~LogObjConfig() {}

	/*!\fn unsigned int save(std::ofstream* stream)
	 * \brief self-serializer
	 * \param stream output stream
	 * \return exit code
	 */
virtual	unsigned int	save(std::ofstream* stream);
};

class PhysObjConfig : public LogObjConfig
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar	& BOOST_SERIALIZATION_BASE_OBJECT_NVP(LogObjConfig)
			& BOOST_SERIALIZATION_NVP(m_shape)
			& BOOST_SERIALIZATION_NVP(m_material);
	}
protected:
	std::string	m_shape;
	std::string	m_material;
public:
	/*!\fn PhysObjConfig()
	 * \brief default constructor
	 */
	PhysObjConfig() : m_shape("Cyllinder"),m_material("CsI")
		{ m_type = "PhysObj";}

	/*!\fn PhysObjConfig(std::string shape, std::string material)
	 * \brief default constructor
	 * \param shape object shape
	 * \param material object material
	 */
	PhysObjConfig(std::string shape, std::string material = "CsI") : m_shape(shape),m_material(material)
		{m_type = "PhysObj";}

	/*!\fn ~PhysObjConfig()
	 * \brief default destructor
	 */
	~PhysObjConfig() {}

	/*!\fn unsigned int save(std::ofstream* stream)
	 * \brief self-serializer
	 * \param stream output stream
	 * \return exit code
	 */
virtual unsigned int	save(std::ofstream* stream);

};

}; //namespace GSMS

BOOST_CLASS_VERSION(GSMS::Config,1)
BOOST_CLASS_VERSION(GSMS::LogObjConfig,1)
BOOST_CLASS_VERSION(GSMS::PhysObjConfig,1)


#endif /*CONFIG_H*/

