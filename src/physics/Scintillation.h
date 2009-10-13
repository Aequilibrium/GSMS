/*!\file Scintillation.h
 * \brief Custom scintillation implementation
 */
#ifndef SCINTILLATION_H_
#define SCINTILLATION_H_

#include <geant/G4Scintillation.hh>

namespace GSMS
{

/*!\class Scintillation
 * \brief Custom scintillation implementation
 */
class Scintillation : public G4Scintillation
{
public:
	/*!\fn Scintillation(const G4String& processName, G4ProcessType processType)
	 * \param processName name of the process
	 * \param processType type of the process
	 */
	Scintillation(const G4String& processName = "Scintillation",
                                 G4ProcessType processType = fElectromagnetic) :
		G4Scintillation(processName,processType) {}

	/*!\fn ~Scintillation()
	 * \brief default destructor
	 */
	~Scintillation() {}

	/*!\fn G4VParticleChange* PostStepDoIt(const G4Track& aTrack,const G4Step&  aStep)
	 * \brief post-step actor
	 * \param aTrack track reference
	 * \param aStep step reference
	 * \return particle change pointer
	 */
	G4VParticleChange* PostStepDoIt(const G4Track& aTrack, 
			                const G4Step&  aStep);

//	void BuildThePhysicsTable();
};

};/*namespace GSMS*/

#endif /*SCINTILLATION_H_*/
