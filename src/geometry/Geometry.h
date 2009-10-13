/*!\file Geometry.h
 * \brief Geometry description
 */
#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "typedefs.h"

#include <geant/G4VUserDetectorConstruction.hh>
#include <geant/globals.hh>

#include <geant/G4OpBoundaryProcess.hh>
#include <geant/G4LogicalBorderSurface.hh>

//class	G4LogicalVolume;
class	G4VPhysicalVolume;
//class	G4Material;
//class	G4OpticalSurface;
//class	G4MaterialPropertiesTable;
//class	G4LogicalBorderSurface;

namespace GSMS
{

/*!\typedef _LPVP
 * \brief logical\&physical volume pair
 */
typedef std::pair<G4LogicalVolume*,G4VPhysicalVolume*>	_LPVP;

/*!\class Geometry
 * \brief Scenery geometry description
 */
class Geometry : public G4VUserDetectorConstruction 
{
	G4VPhysicalVolume*	m_world;

	/*!\var m_objects
	 * \brief objects storage
	 */
	std::map<std::string,_LPVP>		m_objects;

	/*!\fn unsigned int getObject(std::string name)
	 * \brief get object
	 * \param name object name
	 * \return object instance
	 */
	_LPVP*	getObject(std::string name)
	{
		if(m_objects.size() > 0 && name.length() > 0)
			return &m_objects[name];
		return NULL;
	}

	/*!\var m_materials
	 * \brief materials storage
	 */
	std::map<std::string,G4Material*>	m_materials;

	/*!\fn unsigned int defineMaterials()
	 * \brief creation of materials
	 * \return exit code
	 */
	unsigned int	defineMaterials();

	/*!\fn unsigned int getMaterial(std::string name)
	 * \brief get material
	 * \param name material name
	 * \return material ptr
	 */
	G4Material*	getMaterial(std::string name)
	{
		G4Material*	result = NULL;
		if(m_materials.size() > 0 && name.length() > 0)
			result = m_materials[name];
		return result;
	}

public:

	G4VPhysicalVolume* Construct();

	void	ReconstructCrystal() {}
	void	LoadGeometry() {}
	bool	Update();

	Geometry();
	~Geometry();

	unsigned int	getMaterial(std::string name,G4Material** material)
	{
		G4Material*	result = NULL;
		result = getMaterial(name);
		if(!result || !material)
			return GSMS_ERR;
		*material = result;
		return GSMS_OK;
	};
};

}; /*namespace GSMS*/

#endif /*GEOMETRY_H_*/
