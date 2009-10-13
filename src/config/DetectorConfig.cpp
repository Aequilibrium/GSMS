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

#include "DetectorConfig.h"
#include <sys/stat.h>
#include <sys/types.h>

#include "GSMS.h"
#include "detector/Detector.h"

#include <geant/G4Tubs.hh>
#include <geant/G4Sphere.hh>
#include <geant/G4PVPlacement.hh>
#include <geant/G4VisAttributes.hh>
#include <geant/G4SDManager.hh>

#include <geant/G4SDParticleFilter.hh>
#include <geant/G4VPrimitiveScorer.hh>
#include <geant/G4PSEnergyDeposit.hh>
#include <geant/G4PSNofSecondary.hh>
#include <geant/G4PSMinKinEAtGeneration.hh>
#include <geant/G4PSTrackLength.hh>
#include <geant/G4PSNofStep.hh>

unsigned int	GSMS::DetectorConfig::save(std::ofstream* stream)
{
	DetectorConfig*	pDetectorConfig = this;
	boost::archive::xml_oarchive out(*stream);
	out << BOOST_SERIALIZATION_NVP(pDetectorConfig);
}

unsigned int	GSMS::DetectorConfig::imprintDetector(G4VPhysicalVolume* wptr)
{
	G4VPhysicalVolume*	world = NULL;
	if(wptr)
		world = wptr;
	else
		GSMS::GSMS::getWorld(&world);
	try
	{
		G4VSolid*	s_crystal = NULL;
		G4VSolid*	s_mirror = NULL;
		G4VSolid*	s_shirt = NULL;

		if(m_shape == "Cyllinder")
		{
			s_crystal = new G4Tubs(
				"crystal",
				0.,
				m_radius,
				m_height/2,
				0.0*deg,
				360.0*deg);
			s_mirror = new G4Tubs(
				"mirror",
				0.,
				m_radius + m_mirror_thick,
				m_height/2 + m_mirror_thick,
				0.0*deg,
				360.0*deg);
			s_shirt = new G4Tubs(
				"shirt",
				0.,
				m_radius + m_mirror_thick + m_shirt_thick,
				m_height/2 + m_mirror_thick + m_shirt_thick,
				0.0*deg,
				360.0*deg);
		}
		else if (m_shape == "Sphere")
		{
			s_crystal = new G4Sphere(
				"crystal",
				0.,
				m_radius,
				0.0*deg,
				360.0*deg,
				0.0*deg,
				360.0*deg
				);
			s_mirror = new G4Sphere(
				"mirror",
				0.,
				m_radius + m_mirror_thick,
				0.0*deg,
				360.0*deg,
				0.0*deg,
				360.0*deg
				);
			s_shirt = new G4Sphere(
				"shirt",
				0.,
				m_radius + m_mirror_thick + m_shirt_thick,
				0.0*deg,
				360.0*deg,
				0.0*deg,
				360.0*deg
				);

		}
		else return GSMS_ERR;

		G4Material*		crystal_mat = NULL;
		G4Material*		mirror_mat = NULL;
		G4Material*		shirt_mat = NULL;
		if(	!__SUCCEEDED(GSMS::GSMS::getMaterial(m_material,&crystal_mat)) ||
			!__SUCCEEDED(GSMS::GSMS::getMaterial("MgO",&mirror_mat)) ||
			!__SUCCEEDED(GSMS::GSMS::getMaterial("D16",&shirt_mat)))
		return GSMS_ERR;

		G4LogicalVolume*	crystal_log = new G4LogicalVolume(
						s_crystal,
						crystal_mat,
						"crystal_log");
		G4LogicalVolume*	mirror_log = new G4LogicalVolume(
						s_mirror,
						mirror_mat,
						"mirror_log");
		G4LogicalVolume*	shirt_log = new G4LogicalVolume(
						s_shirt,
						shirt_mat,
						"shirt_log");


		G4VPhysicalVolume*	shirt_phys = new G4PVPlacement(
						0,
						G4ThreeVector(0.,0.,0.),
						"shirt_phys",
						shirt_log,
						world,
						false,
						0);
		G4VPhysicalVolume*	mirror_phys = new G4PVPlacement(
						0,
						G4ThreeVector(0.,0.,0.),
						"mirror_phys",
						mirror_log,
						shirt_phys,
						false,
						0);

		G4VPhysicalVolume*	crystal_phys = new G4PVPlacement(
						0,
						G4ThreeVector(0.,0.,0.),
						"crystal_phys",
						crystal_log,
						mirror_phys,
						false,
						0);

		G4VisAttributes*	crystal_vis = new G4VisAttributes(GSMS_COLOR_CRYSTAL);
		G4VisAttributes*	mirror_vis = new G4VisAttributes(GSMS_COLOR_MGO);
		G4VisAttributes*	shirt_vis = new G4VisAttributes(GSMS_COLOR_ALUMINIUM);

		crystal_vis->SetVisibility(true);
		mirror_vis->SetVisibility(true);
		shirt_vis->SetVisibility(true);

		crystal_vis->SetForceSolid(true);
		mirror_vis->SetForceSolid(true);
		shirt_vis->SetForceSolid(true);

		crystal_log->SetVisAttributes(crystal_vis);
		mirror_log->SetVisAttributes(mirror_vis);
		shirt_log->SetVisAttributes(shirt_vis);

/*
		G4SDManager*		sd_manager = G4SDManager::GetSDMpointer();
		G4VSensitiveDetector*	crystal_sd = new Detector("crystal");
		sd_manager->AddNewDetector(crystal_sd);
		crystal_log->SetSensitiveDetector(crystal_sd);
*/

	G4String filterName, particleName;
  
	G4SDParticleFilter* gammaFilter = 
		new G4SDParticleFilter(filterName="gammaFilter",particleName="gamma");
	G4SDParticleFilter* electronFilter = 
		new G4SDParticleFilter(filterName="electronFilter",particleName="e-");
	G4SDParticleFilter* positronFilter = 
		new G4SDParticleFilter(filterName="positronFilter",particleName="e+");
	G4SDParticleFilter* epFilter = new G4SDParticleFilter(filterName="epFilter");
	epFilter->add(particleName="e-");
	epFilter->add(particleName="e+");
    
    
	// Loop counter j = 0 : absorber
	//                = 1 : gap
	G4String detName = "crystal";
	G4MultiFunctionalDetector* det = new G4MultiFunctionalDetector(detName);
  
	//  The second argument in each primitive means the "level" of geometrical hierarchy,
	// the copy number of that level is used as the key of the G4THitsMap.
	//  For absorber (j = 0), the copy number of its own physical volume is used.
	//  For gap (j = 1), the copy number of its mother physical volume is used, since there
	// is only one physical volume of gap is placed with respect to its mother.
	G4VPrimitiveScorer* primitive;
		primitive = new G4PSEnergyDeposit("eDep");
		//primitive->SetFilter(gammaFilter);
		det->RegisterPrimitive(primitive);

	primitive = new G4PSNofSecondary("nGamma");
		primitive->SetFilter(gammaFilter);
		det->RegisterPrimitive(primitive);

	primitive = new G4PSNofSecondary("nElectron");
		primitive->SetFilter(electronFilter);
		det->RegisterPrimitive(primitive);

	primitive = new G4PSNofSecondary("nPositron");
		primitive->SetFilter(positronFilter);
		det->RegisterPrimitive(primitive);

	primitive = new G4PSMinKinEAtGeneration("minEkinGamma");
		primitive->SetFilter(gammaFilter);
		det->RegisterPrimitive(primitive);

	primitive = new G4PSMinKinEAtGeneration("minEkinElectron");
		primitive->SetFilter(electronFilter);
		det->RegisterPrimitive(primitive);

	primitive = new G4PSMinKinEAtGeneration("minEkinPositron");
		primitive->SetFilter(positronFilter);
		det->RegisterPrimitive(primitive);

	primitive = new G4PSTrackLength("trackLength");
		primitive->SetFilter(epFilter);
		det->RegisterPrimitive(primitive);

	primitive = new G4PSNofStep("nStep");
		primitive->SetFilter(epFilter); 
		det->RegisterPrimitive(primitive);
  
	G4SDManager::GetSDMpointer()->AddNewDetector(det);
	crystal_log->SetSensitiveDetector(det);

	}
	catch(...)
	{
		return GSMS_ERR;
	};
	return GSMS_OK;
};
