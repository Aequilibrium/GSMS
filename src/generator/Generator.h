/*!\file Generator.h
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <geant/G4GeneralParticleSource.hh>
#include <geant/G4VUserPrimaryGeneratorAction.hh>

#include "generator/SourceLib.h"
#include "generator/Source.h"

namespace GSMS {

class Generator : public G4VUserPrimaryGeneratorAction
{
	G4GeneralParticleSource*	mp_gps;
public:
	Generator();
	~Generator();
	void	GeneratePrimaries(G4Event*	anEvent); 
	void	Update();
};

}; /*namespace GSMS*/

#endif /*GENERATOR_H_*/
