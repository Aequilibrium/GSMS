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

/*!\file DetectorHit.h
 */

#ifndef DETECTORHIT_H_
#define DETECTORHIT_H_

#include <geant/G4VHit.hh>
#include <geant/G4THitsCollection.hh>
#include <geant/G4Allocator.hh>
#include <geant/G4ThreeVector.hh>

namespace GSMS
{

class DetectorHit : public G4VHit
{
  public:

      DetectorHit();
     ~DetectorHit();
      DetectorHit(const DetectorHit&);
      const DetectorHit& operator=(const DetectorHit&);
      G4int operator==(const DetectorHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();

  public:
  
      void SetTrackID  (G4int track)      { trackID = track; };
      void SetChamberNb(G4int chamb)      { chamberNb = chamb; };  
      void SetEdep     (G4double de)      { edep = de; };
      void SetPos      (G4ThreeVector xyz){ pos = xyz; };
      
      G4int GetTrackID()    { return trackID; };
      G4int GetChamberNb()  { return chamberNb; };
      G4double GetEdep()    { return edep; };      
      G4ThreeVector GetPos(){ return pos; };
      
  private:
  
      G4int         trackID;
      G4int         chamberNb;
      G4double      edep;

      G4ThreeVector pos;
};

typedef G4THitsCollection<DetectorHit> DetectorHitsCollection;

extern G4Allocator<DetectorHit> DetectorHitAllocator;

inline void* DetectorHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) DetectorHitAllocator.MallocSingle();
  return aHit;
}

inline void DetectorHit::operator delete(void *aHit)
{
  DetectorHitAllocator.FreeSingle((DetectorHit*) aHit);
}

}; /* namespace GSMS*/

#endif /*DETECTORHIT_H_*/
