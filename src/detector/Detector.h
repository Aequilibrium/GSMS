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

/*!\file Detector.h
 */

#ifndef DETECTOR_H_
#define DETECTOR_H_

#include <geant/G4VSensitiveDetector.hh>
#include "DetectorHit.h"

class G4Step;
class G4HCofThisEvent;

namespace GSMS
{

class Detector : public G4VSensitiveDetector
{
  public:
      Detector(G4String);
     ~Detector();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);

      G4double GetEnergy() {return dEn;}

  private:
      DetectorHitsCollection* trackerCollection;

	G4double dEn;

};

}; /* namespace GSMS*/

#endif /*DETECTOR_H_*/
