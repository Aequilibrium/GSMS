/*!\file PhysicsList.h
 * \brief GSMS physics definitions
 */
#ifndef PHYSICSLIST_H_
#define PHYSICSLIST_H_

#include <geant/G4VUserPhysicsList.hh>
#include <geant/globals.hh>
#include "Scintillation.h"

namespace GSMS
{

/*!\class PhysicsList
 * \brief GSMS physics list
 */
class PhysicsList: public G4VUserPhysicsList
{
	/*!\var VerboseLevel
	 * \brief verbosity level
	 */
	G4int VerboseLevel;

	/*!\var OpVerboseLevel
	 * \brief verbosity level
	 */
	G4int OpVerbLevel;

	/*!\var cutForGamma
	 * \brief special cuts for gamma
	 */
	G4double cutForGamma;

	/*!\var cutForElectron
	 * \brief special cuts for electron
	 */
	G4double cutForElectron;

	/*!\var cutForPositron
	 * \brief special cuts for positron
	 */
	G4double cutForPositron;

	/*!\var cutForProton
	 * \brief special cuts for proton
	 */
	G4double cutForProton;

	/*!\var cutForAlpha
	 * \brief special cuts for alpha
	 */
	G4double cutForAlpha;

	/*!\var cutForGenericIon
	 * \brief special cuts for generic ion
	 */
	G4double cutForGenericIon;

public:

	/*!\fn PhysicsList()
	 * \brief default constructor
	*/
	PhysicsList();

	/*!\fn ~PhysicsList()
	 * \brief default destructor
	*/
	~PhysicsList();

	/*!\fn void ConstructParticle()
	 * \brief particle creator
	*/
virtual	void ConstructParticle();

	/*!\fn void ConstructProcess()
	 * \brief process creator
	*/
virtual	void ConstructProcess();

	/*!\fn void SetCuts()
	 * \brief cuts setup
	*/
virtual	void SetCuts();

};

}; /*namespace GSMS*/

#endif /*PHYSICSLIST_H_*/
