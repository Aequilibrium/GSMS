#include "Generator.h"
#include <geant/G4Gamma.hh>
#include "generator/SourceLib.h"

#include "config/GSMS.h"

/*
void	AddCs137(G4GeneralParticleSource*	dst) {

	dst->SetParticleDefinition(G4Gamma::Gamma());
	G4SingleParticleSource*	src = dst->GetCurrentSource();
	src->GetEneDist()->SetMonoEnergy(0.032);
	src->GetAngDist()->SetAngDistType("iso");
	src->GetPosDist()->SetPosDisType("Point");
	src->GetEneDist()->SetEnergyDisType("Mono");
	src->GetPosDist()->SetCentreCoords(G4ThreeVector(0.,1.*m,0.));
	src->GetAngDist()->SetMinPhi(pi/2);
	src->GetAngDist()->SetMaxPhi(pi/2);
	src->GetAngDist()->SetMinTheta(pi/2);
	src->GetAngDist()->SetMaxTheta(pi/2);

	dst->AddaSource(0.014);
	dst->SetParticleDefinition(G4Gamma::Gamma());
	src = dst->GetCurrentSource();
	src->GetEneDist()->SetMonoEnergy(0.036);
	src->GetAngDist()->SetAngDistType("iso");
	src->GetPosDist()->SetPosDisType("Point");
	src->GetEneDist()->SetEnergyDisType("Mono");
	src->GetPosDist()->SetCentreCoords(G4ThreeVector(0.,1.*m,0.));
	src->GetAngDist()->SetMinPhi(pi/2);
	src->GetAngDist()->SetMaxPhi(pi/2);
	src->GetAngDist()->SetMinTheta(pi/2);
	src->GetAngDist()->SetMaxTheta(pi/2);

	dst->AddaSource(0.9);
	dst->SetParticleDefinition(G4Gamma::Gamma());
	src = dst->GetCurrentSource();
	src->GetEneDist()->SetMonoEnergy(0.662);
	src->GetAngDist()->SetAngDistType("iso");
	src->GetPosDist()->SetPosDisType("Point");
	src->GetEneDist()->SetEnergyDisType("Mono");
	src->GetPosDist()->SetCentreCoords(G4ThreeVector(0.,1.*m,0.));
	src->GetAngDist()->SetMinPhi(pi/2);
	src->GetAngDist()->SetMaxPhi(pi/2);
	src->GetAngDist()->SetMinTheta(pi/2);
	src->GetAngDist()->SetMaxTheta(pi/2);
}

void	AddCo60(G4GeneralParticleSource*	dst) {

	dst->AddaSource(1.0);
	dst->SetParticleDefinition(G4Gamma::Gamma());
	G4SingleParticleSource*	src = dst->GetCurrentSource();
	src->GetEneDist()->SetMonoEnergy(1.173);
	src->GetAngDist()->SetAngDistType("iso");
	src->GetPosDist()->SetPosDisType("Point");
	src->GetEneDist()->SetEnergyDisType("Mono");
	src->GetPosDist()->SetCentreCoords(G4ThreeVector(1.*m,0.,0.));
	src->GetAngDist()->SetMinPhi(0.);
	src->GetAngDist()->SetMaxPhi(0.);
	src->GetAngDist()->SetMinTheta(pi/2);
	src->GetAngDist()->SetMaxTheta(pi/2);

	dst->AddaSource(1.0);
	dst->SetParticleDefinition(G4Gamma::Gamma());
	src = dst->GetCurrentSource();
	src->GetEneDist()->SetMonoEnergy(1.332);
	src->GetAngDist()->SetAngDistType("iso");
	src->GetPosDist()->SetPosDisType("Point");
	src->GetEneDist()->SetEnergyDisType("Mono");
	src->GetPosDist()->SetCentreCoords(G4ThreeVector(0.,-1.*m,0.));
	src->GetAngDist()->SetMinPhi(-pi/2);
	src->GetAngDist()->SetMaxPhi(-pi/2);
	src->GetAngDist()->SetMinTheta(pi/2);
	src->GetAngDist()->SetMaxTheta(pi/2);
}

void	AddCo57(G4GeneralParticleSource*	dst) {

	dst->AddaSource(0.855);
	dst->SetParticleDefinition(G4Gamma::Gamma());
	G4SingleParticleSource*	src = dst->GetCurrentSource();
	src->GetEneDist()->SetMonoEnergy(0.122);
	src->GetAngDist()->SetAngDistType("iso");
	src->GetPosDist()->SetPosDisType("Point");
	src->GetEneDist()->SetEnergyDisType("Mono");
	src->GetPosDist()->SetCentreCoords(G4ThreeVector(1.*m,0.,0.));
	src->GetAngDist()->SetMinPhi(0.);
	src->GetAngDist()->SetMaxPhi(0.);
	src->GetAngDist()->SetMinTheta(pi/2);
	src->GetAngDist()->SetMaxTheta(pi/2);

	dst->AddaSource(0.106);
	dst->SetParticleDefinition(G4Gamma::Gamma());
	src = dst->GetCurrentSource();
	src->GetEneDist()->SetMonoEnergy(0.136);
	src->GetAngDist()->SetAngDistType("iso");
	src->GetPosDist()->SetPosDisType("Point");
	src->GetEneDist()->SetEnergyDisType("Mono");
	src->GetPosDist()->SetCentreCoords(G4ThreeVector(1.*m,0.,0.));
	src->GetAngDist()->SetMinPhi(0.);
	src->GetAngDist()->SetMaxPhi(0.);
	src->GetAngDist()->SetMinTheta(pi/2);
	src->GetAngDist()->SetMaxTheta(pi/2);
}
*/

	GSMS::Generator::Generator()
{
	mp_gps = new G4GeneralParticleSource;
}


void	GSMS::Generator::Update() {

	mp_gps->ClearAll();
	std::vector<Source>::iterator it = GSMS::get_job().get_source_iterator();
	for(int i=0; i< GSMS::get_job().get_source_count(); i++, it++)
		(*it).generate_G4(mp_gps);
}

	GSMS::Generator::~Generator()
{
	delete mp_gps;
}

void	GSMS::Generator::GeneratePrimaries(G4Event*	anEvent)
{
	mp_gps->GeneratePrimaryVertex(anEvent);
}
