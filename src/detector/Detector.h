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
