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

#include "Hull.h"
#include <sys/stat.h>
#include <sys/types.h>

#include "GSMS.h"

#include <geant/G4Tubs.hh>
#include <geant/G4Cons.hh>
#include <geant/G4Box.hh>
#include <geant/G4PVPlacement.hh>
#include <geant/G4VisAttributes.hh>

unsigned int	GSMS::Hull::save(std::ofstream* stream)
{
	Hull*	pHull = this;
	boost::archive::xml_oarchive out(*stream);
	out << BOOST_SERIALIZATION_NVP(pHull);
}

unsigned int	GSMS::Hull::imprint(G4VPhysicalVolume* wptr)
{

	G4VPhysicalVolume*	world = NULL;
	if(wptr)
		world = wptr;
	else
		GSMS::GSMS::getWorld(&world);

	try
	{
		G4VSolid*	s_hull = NULL;
		G4double	drum_radius = 0.;
		G4double	drum_height = 0.;

		if(m_radius < 0) {
			double mr, mw, mt;
			mr = GSMS::GSMS::get_mask().get_radius();
			mt = GSMS::GSMS::get_mask().get_ethick();
			mw = GSMS::GSMS::get_mask().get_ewidth();

			std::cerr << "Mask radius: " << mr << std::endl;
			std::cerr << "Mask thickness: " << mt << std::endl;
			std::cerr << "Mask width: " << mw << std::endl;

			drum_radius = mr;

			if(GSMS::GSMS::get_mask().get_etype() == "Box") {
				m_radius = std::sqrt((mr+mt)*(mr+mt) + mw*mw/4.) + m_gap;
			}
			else {
				m_radius = mr + mt + m_gap;
			}

			std::cerr << "Hull radius: " << m_radius << std::endl;

		}

		if(m_height < 0)
			m_height = GSMS::GSMS::get_mask().get_eheight() + 2*m_gap;
		drum_height = GSMS::GSMS::get_mask().get_eheight();
		

		G4Material*	mat_cover = NULL;
		G4Material*	mat_stand = NULL;
		G4Material*	mat_stainless = NULL;
		G4VSolid*	s_cover = NULL;
		G4VSolid*	s_hat = NULL;
		G4VSolid*	s_plate = NULL;
		G4VSolid*	s_stand = NULL;
		G4VSolid*	s_mtube = NULL;
		G4VSolid*	s_mplate = NULL;

		G4VSolid*	s_drum_plate_top = NULL;
		G4VSolid*	s_drum_plate_bottom = NULL;
		G4VSolid*	s_drum = NULL;


		if(	!__SUCCEEDED(GSMS::GSMS::getMaterial("GRP", &mat_cover)) ||
			!__SUCCEEDED(GSMS::GSMS::getMaterial("Steel", &mat_stand)) ||
			!__SUCCEEDED(GSMS::GSMS::getMaterial("H18N10", &mat_stainless)) ||
			m_radius <= 0. || m_thickness <= 0.)
			return GSMS_ERR;

		s_cover = new G4Tubs(
			"Cover",
			m_radius,
			m_radius + m_thickness,
			m_height/2,
			0.0*deg,
			360.0*deg);

		s_hat = new G4Cons(
			"Hat",
			m_radius, m_radius + m_thickness,
			m_top_radius, m_top_radius + m_thickness,
			m_hat_height/2,
			0.0*deg,
			360.0*deg);


		s_plate = new G4Tubs(
			"Top_Plate",
			6.0*cm/2,//TODO - get real detector radius
			m_radius,
			5.0*mm/2,
			0.0*deg,
			360.0*deg);

		s_mtube = new G4Tubs(
			"Metal_Tube",
			6.0*cm/2,//TODO - get real detector radius
			6.5*cm/2,
			9.0*cm/2,
			0.0*deg,
			360.0*deg);

		s_mplate = new G4Tubs(
			"Metal_Plate",
			6.5*cm/2,//TODO - get real detector radius
			9.0*cm/2,
			3.0*mm/2,
			0.0*deg,
			360.0*deg);

		s_drum_plate_top = new G4Tubs(
			"Drum_Plate_Top",
			28.*cm/2,
			drum_radius,
			0.4*mm/2,
			0.0*deg,
			360.0*deg);

		s_drum_plate_bottom = new G4Tubs(
			"Drum_Plate_Bottom",
			0.,
			drum_radius,
			0.8*mm/2,
			0.0*deg,
			360.0*deg);

		s_drum = new G4Tubs(
			"Drum",
			drum_radius,
			drum_radius + 0.8*mm,
			drum_height/2,
			0.0*deg,
			360.0*deg);


		//hull cyllinder
		G4LogicalVolume*	cover_log = new G4LogicalVolume(
						s_cover,
						mat_cover,
						"cover_log");

		G4VPhysicalVolume*	cover_phys = new G4PVPlacement(
			0,
			G4ThreeVector(0.,0.,0.),
			"cover_phys",
			cover_log,
			world,
			true,
			0);

		//hat cone
		G4LogicalVolume*	hat_log = new G4LogicalVolume(
						s_hat,
						mat_cover,
						"hat_log");

		G4VPhysicalVolume*	hat_phys = new G4PVPlacement(
			0,
			G4ThreeVector(0.,0.,(m_hat_height + m_height)/2),
			"hat_phys",
			hat_log,
			world,
			true,
			0);

		//plates
		G4LogicalVolume*	plate_log = new G4LogicalVolume(
						s_plate,
						mat_cover,
						"plate_log");

		G4VPhysicalVolume*	top_plate_phys = new G4PVPlacement(
			0,
			G4ThreeVector(0.,0.,(m_height + 5.*mm)/2),
			"top_plate_phys",
			plate_log,
			world,
			true,
			0);

		G4VPhysicalVolume*	bottom_plate_phys = new G4PVPlacement(
			0,
			G4ThreeVector(0.,0.,-(m_height + 5.*mm)/2),
			"bottom_plate_phys",
			plate_log,
			world,
			true,
			0);

		//metal tube
		G4LogicalVolume*	mtube_log = new G4LogicalVolume(
						s_mtube,
						mat_stand,
						"mtube_log");

		G4LogicalVolume*	mplate_log = new G4LogicalVolume(
						s_mplate,
						mat_stand,
						"mplate_log");


		G4VPhysicalVolume*	mtube_phys = new G4PVPlacement(
			0,
			G4ThreeVector(0.,0.,(m_height - 9.0*cm)/2),//TODO? mtube height?
			"mtube_phys",
			mtube_log,
			world,//cover_phys?
			true,
			0);

		G4VPhysicalVolume*	mplate_phys_bottom = new G4PVPlacement(
			0,
			G4ThreeVector(0.,0.,(m_height + 3.0*mm)/2 - 9.0*cm),//TODO? mtube height?
			"mplate_phys_bottom",
			mplate_log,
			world,//cover_phys?
			true,
			0);

		G4VPhysicalVolume*	mplate_phys_top = new G4PVPlacement(
			0,
			G4ThreeVector(0.,0.,(m_height - 3.0*mm)/2),//TODO? mtube height?
			"mplate_phys_top",
			mplate_log,
			world,//cover_phys?
			true,
			0);

		//drum
		G4LogicalVolume*	drum_plate_top_log = new G4LogicalVolume(
						s_drum_plate_top,
						mat_stainless,
						"drum_plate_top");
		G4LogicalVolume*	drum_plate_bottom_log = new G4LogicalVolume(
						s_drum_plate_bottom,
						mat_stainless,
						"drum_plate_bottom");
		G4LogicalVolume*	drum_log = new G4LogicalVolume(
						s_drum,
						mat_stainless,
						"drum_log");

		G4VPhysicalVolume*	drum_plate_top_phys = new G4PVPlacement(
			0,
			G4ThreeVector(0.,0.,(drum_height + 0.8*mm)/2),
			"drum_plate_top_phys",
			drum_plate_top_log,
			world,//cover_phys?
			true,
			0);
		G4VPhysicalVolume*	drum_plate_bottom_phys = new G4PVPlacement(
			0,
			G4ThreeVector(0.,0.,-(drum_height + 0.8*mm)/2),
			"drum_plate_bottom_phys",
			drum_plate_bottom_log,
			world,//cover_phys?
			true,
			0);
		G4VPhysicalVolume*	drum_phys = new G4PVPlacement(
			0,
			G4ThreeVector(0.,0.,0.),
			"drum_phys",
			drum_log,
			world,//cover_phys?
			true,
			0);

		G4VisAttributes*	cover_vis = new G4VisAttributes(GSMS_COLOR_PLASTIC);
		G4VisAttributes*	stand_vis = new G4VisAttributes(GSMS_COLOR_STEEL);

		cover_vis->SetVisibility(true);
		stand_vis->SetVisibility(true);

		cover_vis->SetForceSolid(true);
		stand_vis->SetForceSolid(true);

		cover_log->SetVisAttributes(cover_vis);
		hat_log->SetVisAttributes(cover_vis);
		plate_log->SetVisAttributes(cover_vis);
		mplate_log->SetVisAttributes(stand_vis);
		mtube_log->SetVisAttributes(stand_vis);
		drum_plate_top_log->SetVisAttributes(stand_vis);
		drum_plate_bottom_log->SetVisAttributes(stand_vis);
		drum_log->SetVisAttributes(stand_vis);


/*
		if(m_etype == "Box")
		{

			s_element = new G4Box(
				"element",
				m_ewidth/2,
				m_ethick/2,
				m_eheight/2);

		}
		else if(m_etype == "Segment")
		{
			s_element = new G4Box(
				"element",
				m_ewidth/2,
				m_ethick/2,
				m_eheight/2);
		}
		else return GSMS_ERR;

		G4Material*		element_mat = NULL;
		G4Material*		mask_mat = NULL;
		if(!__SUCCEEDED(GSMS::GSMS::getMaterial(m_emat,&element_mat)) ||
			!__SUCCEEDED(GSMS::GSMS::getMaterial("Air",&mask_mat)))
				return GSMS_ERR;

		G4LogicalVolume*	element_log = new G4LogicalVolume(
						s_element,
						element_mat,
						"element_log");

		G4RotationMatrix	mR;		//mask
		G4ThreeVector		mT(0.,0.,0.);	//mask

		G4double local_time,angle,angle_offset;
		local_time = angle = angle_offset = 0.0;
		if(!__SUCCEEDED(GSMS::getTime(&local_time)))
			return GSMS_ERR;

		angle_offset = (m_speed * local_time);

		std::cerr << "Mask angle offset: " << angle_offset*360/2/pi << std::endl;

		for(int i=0;i<m_ecount;i++)
			if(!isTransparent(i))
			{
				G4RotationMatrix	mRe;		//element
				G4ThreeVector		mTe;		//element
				angle = ( (float)i/(float)m_ecount*2*pi + angle_offset );
				G4float xoff = (m_radius+m_ethick)*cos(angle);
				G4float yoff = (m_radius+m_ethick)*sin(angle);
				G4float zoff = 0.;
				mTe.setX(xoff);
				mTe.setY(yoff);
				mTe.setZ(zoff);
				
				mRe.rotateZ(pi/2 + angle);

				G4VPhysicalVolume*	mask_phys = new G4PVPlacement(
					G4Transform3D(mRe,G4ThreeVector(xoff,yoff,zoff)),
					element_log,
					"element_phys",
					world->GetLogicalVolume(),
					false,
					i
					);

				m_mask.push_back(mask_phys);

				std::cerr << "Element " << i << " at angle " << angle*360/2/pi
					<< " xOff = " << xoff
					<< " yOff = " << yoff
					<< " zOff = " << zoff
					<< std::endl;
			};

		G4VisAttributes*	element_vis = new G4VisAttributes(GSMS_COLOR_ELEMENT);

		element_vis->SetVisibility(true);
		element_vis->SetForceSolid(true);
		element_log->SetVisAttributes(element_vis);
*/
	}
	catch(...)
	{
		return GSMS_ERR;
	};

	return GSMS_OK;
};

double	GSMS::Hull::get_dist(G4ThreeVector	coords) {
	return 0.;
	}

double	GSMS::Hull::get_delta_phi(G4ThreeVector	coords) {
	double result = 2*pi/2/180;

	double	dist = std::sqrt(coords.getX()*coords.getX() + coords.getY()*coords.getY());
	result = atan((m_radius + m_thickness) / dist);

	return result;
}


double	GSMS::Hull::get_delta_theta(G4ThreeVector	coords) {
	double result = 0.0;

	//distance to outer ring
	double dist = std::sqrt(coords.getX()*coords.getX() + coords.getY()*coords.getY()) - (m_radius + m_thickness);
	result = atan(m_height/2 / dist);

	return result;
}
