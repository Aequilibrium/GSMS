#include "DetectorHit.h"

#include <geant/G4UnitsTable.hh>
#include <geant/G4VVisManager.hh>
#include <geant/G4Circle.hh>
#include <geant/G4Colour.hh>
#include <geant/G4VisAttributes.hh>

G4Allocator<GSMS::DetectorHit> GSMS::DetectorHitAllocator;

GSMS::DetectorHit::DetectorHit() {}

GSMS::DetectorHit::~DetectorHit() {}

GSMS::DetectorHit::DetectorHit(const GSMS::DetectorHit& right)
  : G4VHit()
{
  trackID   = right.trackID;
  chamberNb = right.chamberNb;
  edep      = right.edep;
  pos       = right.pos;
}

const GSMS::DetectorHit& GSMS::DetectorHit::operator=(const GSMS::DetectorHit& right)
{
  trackID   = right.trackID;
  chamberNb = right.chamberNb;
  edep      = right.edep;
  pos       = right.pos;
  return *this;
}

G4int GSMS::DetectorHit::operator==(const GSMS::DetectorHit& right) const
{
  return (this==&right) ? 1 : 0;
}

void GSMS::DetectorHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(pos);
    circle.SetScreenSize(2.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

void GSMS::DetectorHit::Print()
{
  G4cout << "  trackID: " << trackID << "  chamberNb: " << chamberNb
         << "  energy deposit: " << G4BestUnit(edep,"Energy")
	 << "  position: " << G4BestUnit(pos,"Length") << G4endl;
}
