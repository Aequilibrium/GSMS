#include "Detector.h"

#include <geant/G4HCofThisEvent.hh>
#include <geant/G4Event.hh>
#include <geant/G4Step.hh>
#include <geant/G4VProcess.hh>
#include <geant/G4ThreeVector.hh>
#include <geant/G4SDManager.hh>
#include <geant/G4ios.hh>

GSMS::Detector::Detector(G4String name):G4VSensitiveDetector(name)
{
  G4String HCname;
  if(name == "innerSD")
	HCname = "inner";
  else
	HCname = "outer";

  collectionName.insert(HCname = G4String("trackerCollection" + HCname));
//  G4cout << "Construct: " << HCname << G4endl;
}

GSMS::Detector::~Detector(){ }

void GSMS::Detector::Initialize(G4HCofThisEvent* HCE)
{

  G4String HCname = "trackerCollection";
  if(GetName() == "innerSD")
    HCname = HCname + "inner";
  else
    HCname = HCname + "outer";

  trackerCollection = new DetectorHitsCollection
                          (SensitiveDetectorName, HCname); 

  static G4int HCID = -1;
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID( HCname); }
  HCE->AddHitsCollection( HCID, trackerCollection ); 

}

G4bool GSMS::Detector::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{

  G4double edep = aStep->GetPostStepPoint()->GetKineticEnergy();
//  char edepc[12];
//  char edepcpr[12];
//  sprintf(edepc,"%f",edep);
//  edep = aStep->GetPreStepPoint()->GetKineticEnergy();
//  sprintf(edepcpr,"%f",edep);

G4String sMatPsName = aStep->GetPostStepPoint()->GetMaterial()->GetName();
G4String sMatPrName = aStep->GetPreStepPoint()->GetMaterial()->GetName();
//G4ParticleDefinition* particleType = aStep->GetTrack()->GetDefinition();
//G4String particleName = particleType->GetParticleName();

/*
//if(GetName() == "innerSD")
//{

	G4String sPrName = "undefined";
	G4String sPsName = "undefined";
	

	if(aStep->GetPreStepPoint()->GetProcessDefinedStep())
		sPrName = aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName();

	if(aStep->GetPostStepPoint()->GetProcessDefinedStep())
		sPsName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

		char	xpr[20]; sprintf(xpr,"%.3f;", aStep->GetPreStepPoint()->GetPosition().x());
		char	ypr[20]; sprintf(ypr,"%.3f;", aStep->GetPreStepPoint()->GetPosition().y());
		char	zpr[20]; sprintf(zpr,"%.3f - ", aStep->GetPreStepPoint()->GetPosition().z());
		char	xps[20]; sprintf(xps,"%.3f;", aStep->GetPostStepPoint()->GetPosition().x());
		char	yps[20]; sprintf(yps,"%.3f;", aStep->GetPostStepPoint()->GetPosition().y());
		char	zps[20]; sprintf(zps,"%.3f;", aStep->GetPostStepPoint()->GetPosition().z());

		sCrystalInfo = sCrystalInfo + GetName() + ": " + particleName + "_" + sMatPrName + "-" + sPrName + "-" + edepcpr + "; " + sMatPsName + "-" + sPsName + "-" + edepc + "; " +
		G4String(xpr) + G4String(ypr) + G4String(zpr) +
		G4String(xps) + G4String(yps) + G4String(zps) +
		"\n";
//};
*/

//if(	(sMatPsName != sMatPrName) &&
//	particleName == "gamma" &&
if
	(
	(( GetName() == "innerSD" ) && (sMatPsName == "MgO")) ||
	(( GetName() == "outerSD" ) && (sMatPsName == "CsI" || sMatPsName == "NaI" || sMatPsName == "BGO"))
	)
{

/*  sTrackInfo = 	sTrackInfo + 
		GetName() + 
		"_" + 
		sMatPrName + 
		"_" + 
		sMatPsName + 
		"_" + 
		aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() + 
		+ G4String(edepc) + "\n";
*/

  DetectorHit* newHit = new DetectorHit();
  newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
  newHit->SetChamberNb(aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber());
  newHit->SetEdep     (edep);
  newHit->SetPos      (aStep->GetPostStepPoint()->GetPosition());

  trackerCollection->insert( newHit );
}
 
  return true;
}

void GSMS::Detector::EndOfEvent(G4HCofThisEvent*)
{

     G4int NbHits = trackerCollection->entries();

	dEn = 0.0;

     for (G4int i=0;i<NbHits;i++)
	dEn += (*trackerCollection)[i]->GetEdep();


}
