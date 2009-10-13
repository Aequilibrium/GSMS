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