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

#include "Geometry.h"
#include "config/GSMS.h"

#include <geant/G4Material.hh>
#include <geant/G4MaterialTable.hh>
#include <geant/G4Element.hh>
#include <geant/G4Isotope.hh>
#include <geant/G4UnitsTable.hh>
#include <geant/G4Box.hh>
#include <geant/G4Cons.hh>
#include <geant/G4Tubs.hh>
#include <geant/G4Sphere.hh>
#include <geant/G4UnionSolid.hh>
#include <geant/G4SubtractionSolid.hh>

#include <geant/G4LogicalVolume.hh>
#include <geant/G4PVPlacement.hh>
#include <geant/G4ThreeVector.hh>
#include <geant/G4RotationMatrix.hh>
#include <geant/G4Transform3D.hh>
#include <geant/G4LogicalBorderSurface.hh>
#include <geant/G4LogicalSkinSurface.hh>
#include <geant/G4OpBoundaryProcess.hh>

#include <geant/G4FieldManager.hh>
#include <geant/G4UniformElectricField.hh>
#include <geant/G4TransportationManager.hh>
#include <geant/G4MagIntegratorStepper.hh>
#include <geant/G4EqMagElectricField.hh>
#include <geant/G4ClassicalRK4.hh>
#include <geant/G4ChordFinder.hh>

#include <geant/G4VisAttributes.hh>
#include <geant/G4Colour.hh>

#include <geant/G4RunManager.hh>

#include <geant/G4SDManager.hh>
#include <geant/G4HCtable.hh>


G4VPhysicalVolume* GSMS::Geometry::Construct()
{
	std::cerr << "Construct" << std::endl;
	G4double	new_time = 0;
	if(
		__SUCCEEDED(GSMS::imprintDetector(m_world)) &&
		__SUCCEEDED(GSMS::setTime(&new_time)) &&
		__SUCCEEDED(GSMS::imprintMask(m_world))
	)
	return m_world;
	else
	return NULL;
}

bool	GSMS::Geometry::Update() {
	std::cerr << "Update" << std::endl;
	if(
		__SUCCEEDED(GSMS::imprintMask(m_world))
	)
	return true;
	else
	return false;
}

unsigned int GSMS::Geometry::defineMaterials()
{

	G4double	density,// density
			a,	// atomic mass
			z;	// atomic number
	G4double	G4d_density;
//	G4double	G4d_temp;
//	G4double	G4d_press;
	G4int	 	nelements;
	G4String	G4s_name;
	G4String	G4s_symbol;
	G4int		G4i_ncomp;

  G4Element* H = new G4Element("Hydrogen", "H", z=1., a=1.0079*g/mole);
  G4Element* C = new G4Element("Carbon", "C", z=6., a=12.011*g/mole);
  G4Element* N = new G4Element("Nitrogen", "N", 7., 14.00674*g/mole);
  G4Element* O = new G4Element("Oxygen", "O", 8., 16.00000*g/mole);
  G4Element* Na = new G4Element("Natrium", "Na", z=11., a=22.98977*g/mole);
  G4Element* Mg = new G4Element("Magnezium", "Mg", z=12., a=24.305*g/mole);
  G4Element* Al = new G4Element("Aluminium", "Al", z=13., a=26.981*g/mole);
  G4Element* Si = new G4Element("Silicium", "Si", z=14., a=28.086*g/mole);
  G4Element* P = new G4Element("Phosphorus", "P", z=15., a=30.973976*g/mole);
  G4Element* S = new G4Element("Sulfur", "S", z=16., a=32.06*g/mole);
  G4Element* Cl = new G4Element("Chlorine","Cl", z=17., a=35.453*g/mole);
  G4Element* K = new G4Element("Kalium", "K", z=19., a=39.098*g/mole);
  G4Element* Ca = new G4Element("Calcium", "Ca", z=20., a=40.08*g/mole);
  G4Element* Ti = new G4Element("Titanium", "Ti", z=22., a=47.9*g/mole);
  G4Element* Cr = new G4Element("Chrome", "Cr", z=24., a=51.996*g/mole);
  G4Element* Mn = new G4Element("Manganeze", "Mn", z=25., a=54.938*g/mole);
  G4Element* Fe = new G4Element("Ferrum", "Fe", z=26., a=55.847*g/mole);
  G4Element* Ni = new G4Element("Nickel", "Ni", z=28., a=58.7*g/mole);
  G4Element* Cu = new G4Element("Cuprum", "Cu", z=29., a=63.546*g/mole);
  G4Element* Zn = new G4Element("Zyncum", "Zn", z=30., a=65.38*g/mole);
  G4Element* Ge = new G4Element("Germanium", "Ge", z=32., a=72.59*g/mole);
  G4Element* Ag = new G4Element("Argentum", "Ag", z=47., a=107.8682*g/mole);  
  G4Element* I = new G4Element("Iodine", "I", z=53., a=126.904*g/mole);
  G4Element* Cs = new G4Element("Cesium", "Cs", z=55., a=132.905*g/mole);
  G4Element* Ba = new G4Element("Barium", "Ba", z=56., a=133.*g/mole);
  G4Element* W = new G4Element("Wolfram", "W", z=74., a=183.85*g/mole);
  G4Element* Pt = new G4Element("Platinum", "Pt", z=78., a=195.08*g/mole);  
  G4Element* Au = new G4Element("Aurum", "Au", z=79., a=196.9665*g/mole);  
  G4Element* Pb = new G4Element("Plumbum", "Pb", z=82., a=207.2*g/mole);
  G4Element* Bi = new G4Element("Bismuth", "Bi", z=83., a=208.9804*g/mole);

	G4Material*	mptr;
	std::string	name;

	try
	{
//vacuum
		name = "Vacuum";
		mptr = new G4Material(
				name.c_str(),	//name
				1,		//components
				1.00794*g/mole,	//1st component a/weight
				1.0E-25*g/cm3,	//density
				kStateGas,	//state
				0.1*kelvin,	//temp
				1.0E-19*pascal);//pressure
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));
//air
		name = "Air";
		mptr = new G4Material(
				name,
				1.2929*kg/m3,
				2, 
				kStateGas,
				300.00*kelvin,
				1.0*atmosphere);
		mptr->AddElement(N,	0.8);
		mptr->AddElement(O,	0.2);
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));
//aluminium
		name = "Aluminium";
		mptr = new G4Material(
				name,
				2.8*g/cm3,
				1);
		mptr->AddElement(Al,	1);
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));
//lead
		name = "Lead";
		mptr = new G4Material(
				name,
				11.336*g/cm3,
				1);
		mptr->AddElement(Pb,	1);
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));
//MgO
		name = "MgO";
		mptr = new G4Material(
			name, 
			0.7 * 2.506*g/cm3,
			2);
		mptr->AddElement(O,	1);
		mptr->AddElement(Mg,	1);
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));
//glass
		name = "Glass";
		mptr = new G4Material(
			name, 
			2.6*g/cm3,
			7);
		mptr->AddElement(O,	59.8*perCent);
		mptr->AddElement(Si,	24.7*perCent);
		mptr->AddElement(Al,	1.4*perCent);
		mptr->AddElement(Mg,	1.4*perCent);
		mptr->AddElement(Ca,	2.3*perCent);
		mptr->AddElement(Na,	10.3*perCent);
		mptr->AddElement(Fe,	0.1*perCent);
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));
//soil
		name = "Soil";
		mptr = new G4Material(
			name, 
			1.6*g/cm3,//1.3..2.0
			11);
		mptr->AddElement(O,	46.0*perCent);//46.7
		mptr->AddElement(Si,	27.0*perCent);
		mptr->AddElement(Al,	8.0*perCent);//8.0
		mptr->AddElement(Fe,	5.0*perCent);

		mptr->AddElement(Ca,	2.0*perCent);
		mptr->AddElement(Mg,	2.0*perCent);
		mptr->AddElement(K,	2.0*perCent);
		mptr->AddElement(Na,	2.0*perCent);
		mptr->AddElement(P,	2.0*perCent);
		mptr->AddElement(S,	2.0*perCent);
		mptr->AddElement(N,	2.0*perCent);
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));
//steel
		name = "Steel";
		mptr = new G4Material(
			name, 
			7.81*g/cm3,
			7);
		mptr->AddElement(C,	0.0010);
		mptr->AddElement(Si,	0.0100);
		mptr->AddElement(Mn,	0.0065);
		mptr->AddElement(Cr,	0.0075);
		mptr->AddElement(Ni,	0.0065);
		mptr->AddElement(Cu,	0.0050);
		mptr->AddElement(Fe,	0.9635);
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));
//D16
		name = "D16";
		mptr = new G4Material(
			name, 
			2.8*g/cm3,
			9);
		mptr->AddElement(Al,	92.5*perCent);
		mptr->AddElement(Cu,	4.0*perCent);
		mptr->AddElement(Mg,	1.5*perCent);
		mptr->AddElement(Fe,	0.5*perCent);
		mptr->AddElement(Si,	0.5*perCent);
		mptr->AddElement(Mn,	0.5*perCent);
		mptr->AddElement(Zn,	0.3*perCent);
		mptr->AddElement(Ni,	0.1*perCent);
		mptr->AddElement(Ti,	0.1*perCent);
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));
//plastic
		name = "Plastic";
		mptr = new G4Material(
			name,
			1.19*g/cm3,
			3);
		mptr->AddElement(H, 	0.08);
		mptr->AddElement(C, 	0.60);
		mptr->AddElement(O, 	0.32);
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));
//lavsan
		name = "Lavsan";
		mptr = new G4Material(
			name,
			1.38*g/cm3,
			3);
		mptr->AddElement(H, 	8);
		mptr->AddElement(C, 	10);
		mptr->AddElement(O, 	4);
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));

		const int NUMENTRIES = 3;
		G4double PP[NUMENTRIES] =	{1.0*eV,	5.0*eV,	10.0*eV};

//CsI
		name = "CsI";
		mptr = new G4Material(
			name,
			4.51*g/cm3,
			2,
			kStateUndefined,
			273*kelvin);
		mptr->AddElement(Cs,	1);
		mptr->AddElement(I,	1);
		G4MaterialPropertiesTable*	Scn_Mt = new G4MaterialPropertiesTable();
		G4double CsI_RIND[NUMENTRIES] =	{1.79,		1.79,	1.79};
		G4double CsI_ABSL[NUMENTRIES] =	{71.*cm,	71*cm,	71.*cm};
		Scn_Mt->AddProperty("RINDEX",	PP, CsI_RIND, NUMENTRIES);
		Scn_Mt->AddProperty("ABSLENGTH",PP, CsI_ABSL, NUMENTRIES);
		Scn_Mt->AddConstProperty("SCINTILLATIONYIELD",	54000./MeV);
		Scn_Mt->AddConstProperty("RESOLUTIONSCALE",	0.0759);
		Scn_Mt->AddConstProperty("YIELDRATIO",		1.);
		Scn_Mt->AddConstProperty("EXCITATIONRATIO",	1.);
		mptr->SetMaterialPropertiesTable(Scn_Mt);
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));
//NaI
		name = "NaI";
		mptr = new G4Material(
			name.c_str(),
			3.67*g/cm3,
			2,
			kStateUndefined,
			273*kelvin);
		mptr->AddElement(Na,	1);
		mptr->AddElement(I,	1);
		Scn_Mt = new G4MaterialPropertiesTable();
		G4double NaI_RIND[NUMENTRIES] =	{2.15,		2.15,	2.15};
		G4double NaI_ABSL[NUMENTRIES] =	{71.*cm,	71*cm,	71.*cm};
		Scn_Mt->AddProperty("RINDEX",	PP, NaI_RIND, NUMENTRIES);
		Scn_Mt->AddProperty("ABSLENGTH",PP, NaI_ABSL, NUMENTRIES);
		Scn_Mt->AddConstProperty("SCINTILLATIONYIELD",	38000./MeV);
		Scn_Mt->AddConstProperty("RESOLUTIONSCALE",	0.085);
		Scn_Mt->AddConstProperty("YIELDRATIO",		1.);
		Scn_Mt->AddConstProperty("EXCITATIONRATIO",	1.);
		mptr->SetMaterialPropertiesTable(Scn_Mt);
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));
//BGO
		name = "BGO";
		mptr = new G4Material(
			name.c_str(),
			7.13*g/cm3,
			3,
			kStateUndefined,
			273*kelvin);
		mptr->AddElement(Bi,	4);
		mptr->AddElement(Ge,	3);
		mptr->AddElement(O,	12);
		Scn_Mt = new G4MaterialPropertiesTable();
		G4double BGO_RIND[NUMENTRIES] =	{2.15,		2.15,	2.15};
		G4double BGO_ABSL[NUMENTRIES] =	{71.*cm,	71*cm,	71.*cm};
		Scn_Mt->AddProperty("RINDEX",	PP, BGO_RIND, NUMENTRIES);
		Scn_Mt->AddProperty("ABSLENGTH",PP, BGO_ABSL, NUMENTRIES);
		Scn_Mt->AddConstProperty("SCINTILLATIONYIELD",	9000./MeV);
		Scn_Mt->AddConstProperty("RESOLUTIONSCALE",	0.11);
		Scn_Mt->AddConstProperty("YIELDRATIO",		1.);
		Scn_Mt->AddConstProperty("EXCITATIONRATIO",	1.);
		mptr->SetMaterialPropertiesTable(Scn_Mt);
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));
//stylben
/*
		name = "Stylben";
		mptr = new G4Material(
			name.c_str(),
			1.16*g/cm3,
			2);
		mptr->AddElement(H,	12);
		mptr->AddElement(C,	14);
		Scn_Mt = new G4MaterialPropertiesTable();
		Scn_Mt->AddProperty("RINDEX",	Scn_PP, Scn_RIND, NUMENTRIES);
		Scn_Mt->AddProperty("ABSLENGTH",Scn_PP, Scn_ABSL, NUMENTRIES);
		Scn_Mt->AddConstProperty("SCINTILLATIONYIELD",	54000./MeV);
		Scn_Mt->AddConstProperty("RESOLUTIONSCALE",	0.0759);
		Scn_Mt->AddConstProperty("YIELDRATIO",		1.);
		Scn_Mt->AddConstProperty("EXCITATIONRATIO",	1.);
		mptr->SetMaterialPropertiesTable(Scn_Mt);
		m_materials.insert(std::pair<std::string,G4Material*>(name,mptr));
*/

	}
	catch(...)
	{
		return GSMS_ERR;
	}

	return GSMS_OK;
}

GSMS::Geometry::Geometry()
{
	m_world = NULL;
	defineMaterials();

	G4Box* world_box = new G4Box(
		"world_box",
		2*m,
		2*m,
		2*m);

	G4LogicalVolume*	world_log  = new G4LogicalVolume(
		world_box,
		m_materials["Air"],
		"world_log");

	m_world = new G4PVPlacement(
		0,
		G4ThreeVector(0.	,0.	,0.),
		"world_phys",
		world_log,
		NULL,
		false,
		0);

	world_log->SetVisAttributes(G4VisAttributes::Invisible);
}

GSMS::Geometry::~Geometry()
{
}

/*
void OTDetectorConstruction::ReconstructCrystal()
{

/////////////////////////////
//Clearing up old instances//
/////////////////////////////
G4cout << "Clearing up crystal..." << G4endl;
	if(crystal_log) delete crystal_log;
	if(crystal_phys) delete crystal_phys;

G4cout << "Clearing up plastic..." << G4endl;
	if(plastic_log) delete plastic_log;
	if(plastic_phys) delete plastic_phys;

G4cout << "Clearing up foil..." << G4endl;
	if(foil_log) delete foil_log;
	if(foil_phys) delete foil_phys;

	if(foilp_log) delete foilp_log;
	if(foilp_phys) delete foilp_phys;

G4cout << "Clearing up glass..." << G4endl;
	if(glass_log) delete glass_log;
	if(glass_phys) delete glass_phys;

G4cout << "Clearing up PET..." << G4endl;
	if(PET_log) delete PET_log;
	if(PET_phys) delete PET_phys;

G4cout << "hey1" << G4endl;

//////////////////////////
//Clearing up primitives//
//////////////////////////
G4cout << "Clearing up primitives..." << G4endl;
	G4VSolid* Crystal = NULL;
	G4VSolid* Glass = NULL;
	G4VSolid* Plastic = NULL;
	G4VSolid* Foil = NULL;
	G4VSolid* FoilP = NULL;
	G4VSolid* PET = NULL;

///////////////////////////////
//Creating phoswitch assembly//
///////////////////////////////
G4cout << "Creating assembly..." << G4endl;

	Crystal = new G4Tubs(
		"Crystal",
		0.,
		dCD/2,
		dCH/2,
		0.0*deg,
		360.0*deg);

	if(dGlassTck > 0.)
	{
		Glass = new G4Tubs(
			"Glass",
			0.,
			dCD/2,
			dGlassTck/2,
			0.0*deg,
			360.0*deg);
	};

	Plastic = new G4Tubs(
		"Plastic",
		0.,
		dCD/2,
		dStylbTck/2,
		0.0*deg,
		360.0*deg);

	Foil = new G4Tubs(
		"Foil",
		0.,
		dCD/2,
		dFoilTck/2,
		0.0*deg,
		360.0*deg);

	FoilP = new G4Tubs(
		"FoilP",
		0.,
		dCD/2,
		dFoilPTck/2,
		0.0*deg,
		360.0*deg);

	PET = new G4Tubs(
		"PET",
		0.,
		dCD/2,
		dPETTck/2,
		0.0*deg,
		360.0*deg);

////////////////////////////
//Creating logical volumes//
////////////////////////////
G4cout << "Creating logical volumes..." << G4endl;

	foil_log =	new G4LogicalVolume(Foil,G4Mat_Al,"foil_log");
	foilp_log =	new G4LogicalVolume(FoilP,G4Mat_Lavsan,"foilp_log");
	plastic_log =	new G4LogicalVolume(Plastic,G4Mat_Plastic,"plastic_log");
	if(Glass)
		glass_log =	new G4LogicalVolume(Glass,G4Mat_Glass,"glass_log");
	crystal_log =	new G4LogicalVolume(Crystal,G4Mat_CsI,"crystal_log");
	PET_log =	new G4LogicalVolume(PET,G4Mat_Al,"PET_log");

/////////////////////////////
//Creating physical volumes//
/////////////////////////////
G4cout << "Creating physical volumes..." << G4endl;

	G4double	dFoilOffset	= 0.0;
	G4double	dFoilPOffset	= (dFoilTck+dFoilPTck)/2;
	G4double	dPlasticOffset	= dFoilPTck+(dFoilTck+dStylbTck)/2;
	G4double	dGlassOffset	= dFoilPTck+dStylbTck+(dFoilTck+dGlassTck)/2;
	G4double	dCrystalOffset	= dFoilPTck+dStylbTck+dGlassTck+(dFoilTck+dCH)/2;
	G4double	dPETOffset	= dFoilPTck+dStylbTck+dGlassTck+dCH+(dFoilTck+dPETTck)/2;

	foil_phys =	new G4PVPlacement(0, G4ThreeVector(0.,0.,-dFoilOffset), "foil_phys", foil_log, world_phys, false, 0);
	foilp_phys =	new G4PVPlacement(0, G4ThreeVector(0.,0.,-dFoilPOffset), "foilp_phys", foilp_log, world_phys, false, 0);
	plastic_phys =	new G4PVPlacement(0, G4ThreeVector(0.,0.,-dPlasticOffset), "plastic_phys", plastic_log, world_phys, false, 0);
	if(Glass)
		glass_phys =	new G4PVPlacement(0, G4ThreeVector(0.,0.,-dGlassOffset), "glass_phys", glass_log, world_phys, false, 0);
 	crystal_phys =	new G4PVPlacement(0, G4ThreeVector(0.,0.,-dCrystalOffset), "crystal_phys", crystal_log, world_phys, false, 0);
	PET_phys =	new G4PVPlacement(0, G4ThreeVector(0.,0.,-dPETOffset), "PET_phys", PET_log, world_phys, false, 0);

//////////////////////////////
//Creating visual attributes//
//////////////////////////////
G4cout << "Creating visual attributes..." << G4endl;

	G4VisAttributes* Foil_VAt  = new G4VisAttributes(G4Colour(1., 1., 0.));
	G4VisAttributes* Stylb_VAt = new G4VisAttributes(G4Colour(1., 0., 1.));
	G4VisAttributes* Glass_VAt = new G4VisAttributes(G4Colour(0., 0., 1.));
	G4VisAttributes* CsI_VAt   = new G4VisAttributes(G4Colour(0., 1., 0.));
	G4VisAttributes* PET_VAt   = new G4VisAttributes(G4Colour(1., 0., 0.));

	Foil_VAt->SetVisibility(true);
	Stylb_VAt->SetVisibility(true);
	Glass_VAt->SetVisibility(true);
	CsI_VAt->SetVisibility(true);
	PET_VAt->SetVisibility(true);

	Foil_VAt->SetForceSolid(true);
	Stylb_VAt->SetForceSolid(true);
	Glass_VAt->SetForceSolid(true);
	CsI_VAt->SetForceSolid(true);
	PET_VAt->SetForceSolid(true);

	foil_log->SetVisAttributes(Foil_VAt);
	foilp_log->SetVisAttributes(Glass_VAt);
	plastic_log->SetVisAttributes(Stylb_VAt);
	if(Glass)
		glass_log->SetVisAttributes(Glass_VAt);
	crystal_log->SetVisAttributes(CsI_VAt);
	PET_log->SetVisAttributes(PET_VAt);

/////////////////////////////////
//Assigning sensitive detectors//
////////////////////////////////

	G4SDManager* SDMan = G4SDManager::GetSDMpointer();

	G4String stylbenSDName = "stylbenSD";
	G4String crystalSDName = "crystalSD";

	G4VSensitiveDetector* stylbenSD = (G4VSensitiveDetector*)(SDMan->FindSensitiveDetector(stylbenSDName));
	G4VSensitiveDetector* crystalSD = (G4VSensitiveDetector*)(SDMan->FindSensitiveDetector(crystalSDName));

	if( !stylbenSD )
	{
		stylbenSD = new OTSD( stylbenSDName );
		SDMan->AddNewDetector( stylbenSD );
	};
	if( !crystalSD )
	{
		crystalSD = new OTSD( crystalSDName );
		SDMan->AddNewDetector( crystalSD );
	};

	plastic_log->SetSensitiveDetector( stylbenSD );
	crystal_log->SetSensitiveDetector( crystalSD );


}

void OTDetectorConstruction::LoadGeometry()
{

}
*/
