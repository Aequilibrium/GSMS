//
// C++ Interface: RunAction
//
// Description: 
//
//
// Author: P.Voylov <pvoilov@aidoss.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

/*!\file RunAction.h
 * \brief Action HC processor
 */
#ifndef RUNACTION_H
#define RUNACTION_H

#include "config/Config.h"
#include "action/Run.h"
#include <geant/G4UserRunAction.hh>

/*!\namespace GSMS
 * \brief Gamma-Scanner Modelling Suite namespace
 */
namespace GSMS {

/*!\class RunAction
 * \brief Action processor
 */
class RunAction : public G4UserRunAction
{
public:
	RunAction();
	~RunAction();

	G4Run*	GenerateRun();
virtual	void	BeginOfRunAction(const G4Run*);
virtual	void	EndOfRunAction(const G4Run*);
};

}

#endif /*RUNACTION_H*/