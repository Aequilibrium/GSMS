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
