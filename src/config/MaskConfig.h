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
/*!\file MaskConfig.h
 * \brief Mask configuration entity
 */
#ifndef MASKCONFIG_H
#define MASKCONFIG_H

#include "Config.h"

#include <geant/G4VPVParameterisation.hh>
#include <geant/G4AssemblyVolume.hh>

class	G4Box;
class	G4VPhysicalVolume;
class	G4Touchable;
class	G4Material;

namespace GSMS {

/*!\class MaskConfig
 * \brief Mask configuration
 */
class MaskConfig : public LogObjConfig
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
			& BOOST_SERIALIZATION_NVP(m_speed)
			& BOOST_SERIALIZATION_NVP(m_radius)
			& BOOST_SERIALIZATION_NVP(m_hullheight)
			& BOOST_SERIALIZATION_NVP(m_hulltype)
			& BOOST_SERIALIZATION_NVP(m_voffset)
			& BOOST_SERIALIZATION_NVP(m_ewidth)
			& BOOST_SERIALIZATION_NVP(m_eheight)
			& BOOST_SERIALIZATION_NVP(m_ethick)
			& BOOST_SERIALIZATION_NVP(m_emat)
			& BOOST_SERIALIZATION_NVP(m_etype)
			& BOOST_SERIALIZATION_NVP(m_ecount)
			& BOOST_SERIALIZATION_NVP(m_evector);
	}
protected:
	/*!\var m_speed
	 * \brief angular speed radians/sec
	 */
	G4double	m_speed;

	/*!\var m_radius
	 * \brief mask radius
	 */
	G4double	m_radius;

//hull
	/*!\var m_hullheight
	 * \brief hull height
	 */
	G4double	m_hullheight;

	/*!\var m_hulltype
	 * \brief hulltype
	 */
	std::string	m_hulltype;
	//cyllinder
	//rings

	/*!\var m_voffset
	 * \brief vertical offset
	 */
	G4double	m_voffset;

//elements
	/*!\var m_evector
	 * \brief mask configuration vector
	 */
	unsigned_int64	m_evector;

	/*!\var m_ecount
	 * \brief mask elements count
	 */
	unsigned char	m_ecount;

	/*!\var m_emat
	 * \brief mask material
	 */
	std::string	m_emat;

	/*!\var m_etype
	 * \brief mask element type
	 */
	std::string	m_etype;
	//straight
	//sector

	/*!\var m_ewidth
	 * \brief element width
	 */
	G4double	m_ewidth;

	/*!\var m_eheight
	 * \brief element height
	 */
	G4double	m_eheight;

	/*!\var m_ethick
	 * \brief element thickness
	 */
	G4double	m_ethick;

	G4AssemblyVolume*	m_assembly;

public:
	/*!\fn MaskConfig()
	 * \brief Default constructor
	 */
	MaskConfig() :	m_evector(0x121d47b6),
		m_ecount(31),
		m_speed(0.1),
		m_radius(23.*cm),
		m_ewidth(50.*mm),
		m_eheight(30.*cm),
		m_ethick(20.*mm),
		m_emat("Lead"),
		m_etype("Box")
		{m_type = "MaskConfig"; m_assembly = new G4AssemblyVolume;}

	/*!\fn MaskConfig(unsigned char count, unsigned_int64 vector)
	 * \brief Specific constructor
	 * \param elements count
	 * \param evector binary mask configuration
	 */
	MaskConfig(unsigned char ecount, unsigned_int64 evector) :
		m_evector(evector),
		m_ecount(ecount),
		m_radius(23.*cm),
		m_speed(0.1),
		m_ewidth(50.*mm),
		m_eheight(30.*cm),
		m_ethick(20.*mm),
		m_emat("Lead"),
		m_etype("Box")
		{m_type = "MaskConfig"; m_assembly = new G4AssemblyVolume;}

	/*!\fn ~MaskConfig()
	 * \brief Default destructor
	 */
	~MaskConfig() {}

	/*!\fn unsigned int save(std::ofstream* stream)
	 * \brief Self-serializer
	 * \param stream output stream
	 * \return exit code
	 */
virtual unsigned int	save(std::ofstream* stream);

	/*!\fn 	unsigned int imprintMask(G4VPhysicalVolume*	wptr)
	 * \bried dump mask geometry
	 * \param wptr world pointer
	 * \return exit code
	 */
	unsigned int	imprintMask(G4VPhysicalVolume*	wptr = NULL);

	bool	isTransparent(unsigned char index);

	unsigned int	getRadius(G4double* radius);
	unsigned int	setRadius(G4double* radius);
	unsigned int	getSpeed(G4double* speed);
	unsigned int	setSpeed(G4double* speed);
	unsigned int	getECount(unsigned char* ecount);
	unsigned int	setECount(unsigned char* ecount);
	unsigned int	getEHeight(G4double* eheight);
	unsigned int	setEHeight(G4double* eheight);
	unsigned int	getEWidth(G4double* ewidth);
	unsigned int	setEWidth(G4double* ewidth);
	unsigned int	getEThick(G4double* ethick);
	unsigned int	setEThick(G4double* ethick);
	unsigned int	getEMat(std::string*	emat);
	unsigned int	setEMat(std::string*	emat);
	unsigned int	getEType(std::string*	etype);
	unsigned int	setEType(std::string*	etype);
};

class MaskElement : public G4VPVParameterisation
{
		MaskConfig*	m_config;
public:
		MaskElement(MaskConfig* config) : m_config(config) {}

void		ComputeTransformation(
	const	G4int	copyNo,
		G4VPhysicalVolume* physVol
		) const;

void		ComputeDimensions(
		G4Box&	trackerLayer,
	const	G4int	copyNo,
		G4VPhysicalVolume* physVol
		) const;

G4Material*	ComputeMaterial(
	const	G4int	copyNo,
		G4VPhysicalVolume*,
		const G4VTouchable*	parentTouch=0
		);
};

}; /*namespace GSMS*/

BOOST_CLASS_VERSION(GSMS::MaskConfig,1)

#endif /*MASKCONFIG_H*/

