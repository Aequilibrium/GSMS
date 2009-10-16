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
/*!\file GSMS.h
 * \brief Global GSMS configuration handler
 */
#ifndef GSMS_H_
#define GSMS_H_

#include "MaskConfig.h"
#include "GlobalConfig.h"
#include "Job.h"
#include "DetectorConfig.h"
#include "HullConfig.h"
#include "SceneConfig.h"

#include <geant/G4RunManager.hh>

#include "physics/PhysicsList.h"
#include "geometry/Geometry.h"
#include "generator/Generator.h"

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include "typedefs.h"

namespace GSMS
{
/*!\class GSMS
 *\brief Global GSMS configuration and controls
 */
class GSMS
{

/*!\var m_global
 * \brief global configuration
 */
static	GlobalConfig	m_global;

/*!\var m_job
 * \brief job configuration
 */
static	Job	m_job;

/*!\var m_mask
 * \brief mask configuration
 */
static	MaskConfig	m_mask;

/*!\var m_hull
 * \brief hull configuration
 */
static	HullConfig	m_hull;

/*!\var m_detector
 * \brief detector configuration
 */
static	DetectorConfig	m_detector;

/*!\var m_scene
 * \brief scene
 */
static	SceneConfig	m_scene;

/*!\var mp_physics
 * \brief physics list
 */
static	PhysicsList*	mp_physics;

/*!\var mp_geometry
 * \brief geometry
 */
static	Geometry*	mp_geometry;

/*!\var mp_generator
 * \brief generator
 */
static	Generator*	mp_generator;

/*!\var m_runmanager
 * \brief Geant run manager
 */
static	G4RunManager*	mp_runmanager;

/*!\var m_verbosity
 * \brief verbosity level
 */
static G4int	m_verbosity;

public:

	/*!\fn static void setVerbosity(G4int verbosity)
	 * \brief set verbosity level
	 * \param verbosity new verbosity
	 */
static	void	setVerbosity(G4int verbosity) {m_verbosity = verbosity;}

	/*!\fn static G4int getVerbosity()
	 * \brief get verbosity level
	 * \return verbosity
	 */
static	G4int	getVerbosity() {return m_verbosity;}


	/*!\fn static unsigned int serialize(std::string out)
	 * \brief serializer
	 * \param out output stream filename
	 * \return exit code
	 */
static	unsigned int	serialize(std::string filename);

	/*!\fn static unsigned int unserialize(std::ofstream* in)
	 * \brief unserializer
	 * \param filename input stream filename
	 * \return exit code
	 */
static	unsigned int	unserialize(std::string filename);

	/*!\fn unsigned int initRunManager()
	 * \brief model inititator
	 * \return exit code
	 */
static	unsigned int	initRunManager();

	/*!\fn unsigned int getMaterial(std::string name, G4Material** material)
	 * \brief get material pointer
	 * \param name material name
	 * \param material material pointer (out)
	 * \return exit code
	 */
static	unsigned int	getMaterial(std::string name,G4Material** material);

	/*!\fn unsigned int getWorld(G4VPhysicalVolume** wptr)
	 * \brief get world pointer
	 * \param wptr world pointer (out)
	 * \return exit code
	 */
static	unsigned int	getWorld(G4VPhysicalVolume** wptr) {return m_scene.getWorld(wptr);}

static	unsigned int	imprintDetector(G4VPhysicalVolume* world) {return m_detector.imprintDetector(world);}
static	unsigned int	imprintMask(G4VPhysicalVolume* world = NULL) {return m_mask.imprintMask(world);}
static	unsigned int	getTime(G4double* time) {return m_global.getTime(time);}
static	unsigned int	setTime(G4double* time) {return m_global.setTime(time);}

	/*!\fn Job&	get_job() {return m_job;}
	 * \brief get job instance pointer
	 * \return job object
	 */
static	Job&	get_job() {return m_job;}

};

}; /*namespace *GSMS*/

#endif /*GSMS_H_*/
