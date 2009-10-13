#include "Scintillation.h"

#include <geant/G4ios.hh>

namespace GSMS
{

G4double	GetCurve(G4double l1,G4double l2,G4double t)
{
	return l1/(l1-l2)*(exp(-l2*t)-exp(-l1*t));
}

G4double	Nm2MeV(G4double	arg)
{
	G4double dResult = arg;

	G4double	hc = 299.792458*4.136;
 	dResult = hc/arg/1000000.0*MeV;//MeV

	return dResult*MeV;
}

}; /*namespace GSMS*/

G4VParticleChange* GSMS::Scintillation::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
{

//extern G4double dCrystalRes;
//extern G4double dStylben;
//extern G4double dCrystal;

	aParticleChange.Initialize(aTrack);

	const G4DynamicParticle* aParticle = aTrack.GetDynamicParticle();
	const G4Material* aMaterial = aTrack.GetMaterial();

	G4MaterialPropertiesTable* aMaterialPropertiesTable =
                               aMaterial->GetMaterialPropertiesTable();

	if (!aMaterialPropertiesTable)
		return G4VRestDiscreteProcess::PostStepDoIt(aTrack, aStep);

	if (!aMaterialPropertiesTable->ConstPropertyExists("SCINTILLATIONYIELD"))
		return G4VRestDiscreteProcess::PostStepDoIt(aTrack, aStep);

	G4StepPoint*	pPreStepPoint  = aStep.GetPreStepPoint();
	G4StepPoint*	pPostStepPoint = aStep.GetPostStepPoint();

	G4ThreeVector	x0 = pPreStepPoint->GetPosition();
	G4ThreeVector	p0 = aStep.GetDeltaPosition().unit();
	G4double	t0 = pPreStepPoint->GetGlobalTime();
	G4double	dTemp = aMaterial->GetTemperature();

	G4double	TotalEnergyDeposit = aStep.GetTotalEnergyDeposit();

	G4double ScintillationYield = aMaterialPropertiesTable->GetConstProperty("SCINTILLATIONYIELD");
	G4double ResolutionScale    = aMaterialPropertiesTable->GetConstProperty("RESOLUTIONSCALE");

	ScintillationYield = GetScintillationYieldFactor() * ScintillationYield;

	G4double MeanNumberOfPhotons = ScintillationYield * TotalEnergyDeposit;

	G4int NumPhotons;
	if (MeanNumberOfPhotons > 10.)
	{
		//TODO
		double dCrystalRes = 0.085;//ResolutionScale;
		G4double dResA = std::sqrt(0.662)*dCrystalRes;
		G4double sigma = std::sqrt(dResA/2.355/std::sqrt(TotalEnergyDeposit)); //ResolutionScale * sqrt(MeanNumberOfPhotons);
		NumPhotons = G4int(G4RandGauss::shoot(MeanNumberOfPhotons,sigma)+0.5);
	}
	else
	{
	NumPhotons = G4int(G4Poisson(MeanNumberOfPhotons));
	};

	if (NumPhotons <= 0)
	{
// return unchanged particle and no secondaries 
		aParticleChange.SetNumberOfSecondaries(0);
		return G4VRestDiscreteProcess::PostStepDoIt(aTrack, aStep);
	}

	aParticleChange.SetNumberOfSecondaries(NumPhotons);

	if (G4Scintillation::GetTrackSecondariesFirst())
	{
		if (aTrack.GetTrackStatus() == fAlive )
			aParticleChange.ProposeTrackStatus(fSuspend);
	}

/*
	if(aMaterial->GetName()=="Stylben")
		dStylben += TotalEnergyDeposit;
	else
		dCrystal += TotalEnergyDeposit;
*/

	////////////////////////////////////////////////////////////////
        return G4VRestDiscreteProcess::PostStepDoIt(aTrack, aStep);
	////////////////////////////////////////////////////////////////

	//G4int materialIndex = aMaterial->GetIndex();

	G4int Num = NumPhotons;
	G4double ScintillationTime = 0.*ns;

	//defining curves
	G4double	lambda1 = 0.0;
	G4double	lambda2 = 0.0;
	G4double	tau1 = 22.0;
	G4double	tau2 = 700.0;
	G4int		tau_max = 0;

	G4double	smean =		400.0;
	G4double	ssigma =	25.0;
	G4String	sMName =	aMaterial->GetName();
	G4double	w3 =		G4UniformRand();

	if(sMName == "CsI")
	{
		G4double	c2 =	1.112 - 0.62*0.001*dTemp;
		if(c2>1.0)
			c2 = 1.0;
		else if(c2<0.0)
			c2 = 0.0;
		G4double	c1 = 1.0 - c2;
	
		if(w3 <= c1)
		{
			smean = 400.0;
			ssigma = 25.0;
		}
		else
		{
			smean = 560.0;
			ssigma = 60.0;
		}
		tau1 = 22.0;	
		tau2 = 700.0;
	}
	
	if(sMName == "NaI")
	{
		G4double	c2 =	0.926;
		if(c2>1.0)
			c2 = 1.0;
		else if(c2<0.0)
			c2 = 0.0;
		G4double	c1 = 1.0 - c2;
		if(w3 <= c1)
		{
			smean = 340.0;
			ssigma = 15.0;
		}
		else
		{
			smean = 415.0;
			ssigma = 40.0;
		}
		tau1 = 22.0;	
		tau2 = 700.0;
	}

	lambda1 = 1/tau1;
	lambda2 = 1/tau2;
	tau_max = (int)(log(lambda2/lambda1)/(lambda2-lambda1)+0.5);
	
	G4double	model[3][200];
	G4double	model_max = 0.0;

	model[0][0] = 0.0;
	model[1][0] = 0.0;

	for(G4int i = 1; i < 200; i++)
	{
		G4double	splitter = 0.0;
		if(i<60)
			splitter = 1.2*tau_max/60.0;
		else
			splitter = tau_max*(tau2/tau1+10)/140.0;

		model[0][i] = model[0][i-1]+splitter;
		model[2][i] = GSMS::GetCurve(lambda1,lambda2,model[0][i]);

		G4double k = (GSMS::GetCurve(lambda1,lambda2,model[0][i]) - GSMS::GetCurve(lambda1,lambda2,model[0][i-1]))/splitter;
		G4double b = GSMS::GetCurve(lambda1,lambda2,model[0][i-1]);
		model[1][i] = model[1][i-1]+k*splitter*splitter/2 +b*splitter;
		if(i==199)
			model_max = model[1][i];
	}

	for (G4int i = 0; i < Num; i++)
	{
		// Determine photon momentum

		G4double w1 = G4UniformRand();
		G4double w2 = G4UniformRand();

		G4double sampledMomentum = (smean+ssigma*cos(twopi*w1)*sqrt(-2*log(w2)));
		sampledMomentum = GSMS::Nm2MeV(sampledMomentum);

		//verboseLevel = 10;
		//if (verboseLevel>1) {
                   //G4cout << "sampledMomentum = " << sampledMomentum << G4endl;
		   //G4cout << "CIIvalue =        " << CIIvalue << G4endl;
		//}
		//verboseLevel = 0;

// Generate random photon direction

                G4double cost = 1. - 2.*G4UniformRand();
                G4double sint = sqrt((1.-cost)*(1.+cost));

		G4double phi = twopi*G4UniformRand();
		G4double sinp = sin(phi);
		G4double cosp = cos(phi);

		G4double px = sint*cosp;
		G4double py = sint*sinp;
		G4double pz = cost;

// Create photon momentum direction vector 
		G4ParticleMomentum photonMomentum(px, py, pz);

// Determine polarization of new photon 
		G4double sx = cost*cosp;
		G4double sy = cost*sinp; 
		G4double sz = -sint;

		G4ThreeVector photonPolarization(sx, sy, sz);

                G4ThreeVector perp = photonMomentum.cross(photonPolarization);

		phi = twopi*G4UniformRand();
		sinp = sin(phi);
		cosp = cos(phi);

		photonPolarization = cosp * photonPolarization + sinp * perp;
		photonPolarization = photonPolarization.unit();

// Generate a new photon:
		G4DynamicParticle* aScintillationPhoton =
			new G4DynamicParticle(G4OpticalPhoton::OpticalPhoton(),photonMomentum);
		aScintillationPhoton->SetPolarization
			(photonPolarization.x(),
			photonPolarization.y(),
			photonPolarization.z());

		aScintillationPhoton->SetKineticEnergy(sampledMomentum);

// Generate new G4Track object:
                G4double rand;

		if (aParticle->GetDefinition()->GetPDGCharge() != 0)
		{
			rand = G4UniformRand();
                }
		else
		{
			rand = 1.0;
                }

		G4double delta = rand * aStep.GetStepLength();
		G4double deltaTime = delta /
			((pPreStepPoint->GetVelocity()+
			pPostStepPoint->GetVelocity())/2.);

		deltaTime = deltaTime - 
			ScintillationTime * log( G4UniformRand() );
		
		
//new time
		G4double w = G4UniformRand();
		G4int index = 0;
		for(G4int i=1;i<200;i++)
		{
			if((model[1][i-1]/model_max)<=w && (model[1][i]/model_max)>=w)
			{
				index = i;
				break;
			}
		}
	
		G4double prop = (w-(model[1][index-1]/model_max))/((model[1][index]-model[1][index-1])/model_max);
		deltaTime = model[0][index-1]+prop*(model[0][index]-model[0][index-1]);

		G4double aSecondaryTime = t0 + deltaTime;
		G4ThreeVector aSecondaryPosition =
			x0 + rand * aStep.GetDeltaPosition();

		G4Track* aSecondaryTrack = 
			new G4Track(aScintillationPhoton,aSecondaryTime,aSecondaryPosition);

		aSecondaryTrack->SetTouchableHandle((G4VTouchable*)0);
		aSecondaryTrack->SetParentID(aTrack.GetTrackID());
		aParticleChange.AddSecondary(aSecondaryTrack);
	}

	if (verboseLevel>0) {
	G4cout	<< "\n Exiting from G4Scintillation::DoIt -- NumberOfSecondaries = " 
		<< aParticleChange.GetNumberOfSecondaries() << G4endl;
	}

	return G4VRestDiscreteProcess::PostStepDoIt(aTrack, aStep);
}
