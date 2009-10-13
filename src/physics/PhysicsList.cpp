#include "PhysicsList.h"

#include <geant/G4ProcessManager.hh>
#include <geant/G4ProcessVector.hh>

#include <geant/G4ParticleDefinition.hh>
#include <geant/G4ParticleWithCuts.hh>
#include <geant/G4ParticleTypes.hh>
#include <geant/G4ParticleTable.hh>

#include <geant/G4ios.hh>
#include <iomanip>  

#include <geant/G4UserLimits.hh>


// Constructor 
/////////////////////////////////////////////////////////////
GSMS::PhysicsList::PhysicsList() : G4VUserPhysicsList() 
{

  defaultCutValue     = 1.0*micrometer; //
  cutForGamma         = defaultCutValue;
  cutForElectron      = 1.0*nanometer;
  cutForPositron      = defaultCutValue;

  VerboseLevel = 1;
  OpVerbLevel = 0;

  SetVerboseLevel(VerboseLevel);

//	G4cout << "PhysicsList::PhysicsList()" << G4endl;

}

GSMS::PhysicsList::~PhysicsList() 
{
//G4cout << "PhysicsList::~PhysicsList()" << G4endl;
}

void GSMS::PhysicsList::ConstructParticle()
{
	G4Gamma::GammaDefinition();

	G4OpticalPhoton::OpticalPhotonDefinition();

	G4Electron::ElectronDefinition();

//	G4Neutron::NeutronDefinition();

	G4Positron::PositronDefinition();

//	G4cout << "PhysicsList::ConstructParticle()" << G4endl;

}

#include <geant/G4MultipleScattering.hh>

// gamma
#include <geant/G4LowEnergyRayleigh.hh>
#include <geant/G4LowEnergyPhotoElectric.hh>
#include <geant/G4LowEnergyCompton.hh>
#include <geant/G4LowEnergyGammaConversion.hh>

// e-
#include <geant/G4LowEnergyIonisation.hh>
#include <geant/G4LowEnergyBremsstrahlung.hh>

// e+
#include <geant/G4eIonisation.hh>
#include <geant/G4eBremsstrahlung.hh>
#include <geant/G4eplusAnnihilation.hh>

#include <geant/G4EmProcessOptions.hh>

//optics
#include <geant/G4Scintillation.hh>
#include <geant/G4OpAbsorption.hh>
#include <geant/G4OpRayleigh.hh>
#include <geant/G4OpBoundaryProcess.hh>

//decay
#include <geant/G4Decay.hh>

void GSMS::PhysicsList::ConstructProcess(){

//G4cout << "Adding processes..." << G4endl;

	G4VUserPhysicsList::AddTransportation();

//G4cout << "Transportation added..." << G4endl;

	G4LowEnergyPhotoElectric* lowePhot = new G4LowEnergyPhotoElectric();
	G4LowEnergyIonisation* loweIon  = new G4LowEnergyIonisation();
	G4LowEnergyBremsstrahlung* loweBrem = new G4LowEnergyBremsstrahlung();	

	G4double fluorcut = 250*eV;
	lowePhot->SetCutForLowEnSecPhotons(fluorcut);
	loweIon->SetCutForLowEnSecPhotons(fluorcut);
	loweBrem->SetCutForLowEnSecPhotons(fluorcut);

	theParticleIterator->reset();
	while( (*theParticleIterator)() )
	{
		G4ParticleDefinition* particle = theParticleIterator->value();
		G4ProcessManager* pmanager = particle->GetProcessManager();
		G4String particleName = particle->GetParticleName();
		G4String particleType = particle->GetParticleType();
		//G4double charge = particle->GetPDGCharge();
    
		if (particleName == "gamma") 
		{
			pmanager->AddDiscreteProcess(new G4LowEnergyRayleigh());
			pmanager->AddDiscreteProcess(lowePhot);
			pmanager->AddDiscreteProcess(new G4LowEnergyCompton());
			pmanager->AddDiscreteProcess(new G4LowEnergyGammaConversion());
		} 
		else if (particleName == "e-") 
		{
			// process ordering: AddProcess(name, at rest, along step, post step)
			// -1 = not implemented, then ordering
		        G4MultipleScattering* aMultipleScattering = new G4MultipleScattering();
			pmanager->AddProcess(aMultipleScattering,     -1, 1, 1);
			pmanager->AddProcess(loweIon,                 -1, 2, 2);
			pmanager->AddProcess(loweBrem,                -1,-1, 3);
		} 
		else if (particleName == "e+") 
		{
			G4MultipleScattering* aMultipleScattering = new G4MultipleScattering();
			pmanager->AddProcess(aMultipleScattering,     -1, 1, 1);
			pmanager->AddProcess(new G4eIonisation(),     -1, 2, 2);
			pmanager->AddProcess(new G4eBremsstrahlung(), -1,-1, 3);
			pmanager->AddProcess(new G4eplusAnnihilation(),0,-1, 4);      
		} 
	}

	G4EmProcessOptions opt;
	opt.SetMscStepLimitation(fMinimal);//some factor??
	//  opt.SetMscStepLimitation(0);//some factor??

	//G4cout << "EM added..." << G4endl;


/*
	// default scintillation process
	GSMS::Scintillation* theScintProcessDef = new GSMS::Scintillation("Scintillation");
	// theScintProcessDef->DumpPhysicsTable();
	theScintProcessDef->SetTrackSecondariesFirst(true);
	theScintProcessDef->SetScintillationYieldFactor(1.0);
	theScintProcessDef->SetScintillationExcitationRatio(1.0);
	theScintProcessDef->SetVerboseLevel(OpVerbLevel);
*/

	// optical processes
	G4OpAbsorption* theAbsorptionProcess = new G4OpAbsorption();
	G4OpRayleigh* theRayleighScatteringProcess = new G4OpRayleigh();
	G4OpBoundaryProcess* theBoundaryProcess = new G4OpBoundaryProcess();
	//  theAbsorptionProcess->DumpPhysicsTable();
	//  theRayleighScatteringProcess->DumpPhysicsTable();
	theAbsorptionProcess->SetVerboseLevel(OpVerbLevel);
	theRayleighScatteringProcess->SetVerboseLevel(OpVerbLevel);
	theBoundaryProcess->SetVerboseLevel(OpVerbLevel);
	G4OpticalSurfaceModel themodel = unified;
	theBoundaryProcess->SetModel(themodel);

	//G4cout << "Optical added..." << G4endl;

	theParticleIterator->reset();
	while( (*theParticleIterator)() )
	{
		G4ParticleDefinition* particle = theParticleIterator->value();
		G4ProcessManager* pmanager = particle->GetProcessManager();
		G4String particleName = particle->GetParticleName();

/*
		if (theScintProcessDef->IsApplicable(*particle))
		{
			pmanager->AddProcess(theScintProcessDef);
			pmanager->SetProcessOrderingToLast(theScintProcessDef,idxAtRest);
			pmanager->SetProcessOrderingToLast(theScintProcessDef,idxPostStep);
		}
*/

		if (particleName == "opticalphoton")
		{
			pmanager->AddDiscreteProcess(theAbsorptionProcess);
			pmanager->AddDiscreteProcess(theRayleighScatteringProcess);
			pmanager->AddDiscreteProcess(theBoundaryProcess);
		}
	}

	G4Decay* theDecayProcess = new G4Decay();
	theParticleIterator->reset();
	while( (*theParticleIterator)() )
	{
		G4ParticleDefinition* particle = theParticleIterator->value();
		G4ProcessManager* pmanager = particle->GetProcessManager();
      
		if (theDecayProcess->IsApplicable(*particle) && !particle->IsShortLived()) 
		{ 
			pmanager ->AddProcess(theDecayProcess);
			// set ordering for PostStepDoIt and AtRestDoIt
			pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
			pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
		}
	}

//	G4cout << "PhysicsList::ConstructProcess()" << G4endl;
}

void GSMS::PhysicsList::SetCuts()
{
	G4cout << "PhysicsList::SetCuts:";
	G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;

	G4double lowlimit = 1*keV;//250*eV
	G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowlimit,1.*GeV);//100*GeV

	// set cut values for gamma at first and for e- second and next for e+,
	// because some processes for e+/e- need cut values for gamma 
	SetCutValue(cutForGamma, "gamma");
	SetCutValue(cutForElectron, "e-");
	SetCutValue(cutForPositron, "e+");
  
	DumpCutValuesTable();

//	G4cout << "PhysicsList::SetCuts()" << G4endl;

}
