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

#include "Mask.h"
#include <sys/stat.h>
#include <sys/types.h>

#include "GSMS.h"

#include <geant/G4Tubs.hh>
#include <geant/G4Box.hh>
#include <geant/G4PVPlacement.hh>
#include <geant/G4VisAttributes.hh>

bool		GSMS::Mask::isTransparent(unsigned char	index)
{
	return (bool)((m_evector >> index) & 1);
}

unsigned int	GSMS::Mask::save(std::ofstream* stream)
{
	Mask*	pMask = this;
	boost::archive::xml_oarchive out(*stream);
	out << BOOST_SERIALIZATION_NVP(pMask);
}

unsigned int	GSMS::Mask::imprint(G4VPhysicalVolume* wptr)
{
	//clean up
	for(int i=0; i<m_mask.size(); i++) {
		if(m_mask[i]) delete m_mask[i];
	}
	m_mask.clear();

/*
	if(m_assembly)
	{
		std::vector<G4VPhysicalVolume*>::iterator
			iter = m_assembly->GetVolumesIterator();

		for(int i=0;i<m_assembly->TotalImprintedVolumes();iter++,i++)
		{
			G4VPhysicalVolume*	ptr = *iter;
			if(ptr)
				delete ptr;
			*iter = NULL;
		}
		delete m_assembly;
	};
	m_assembly = new G4AssemblyVolume;
*/

	G4VPhysicalVolume*	world = NULL;
	if(wptr)
		world = wptr;
	else
		GSMS::GSMS::getWorld(&world);

	std::cerr << world << std::endl;
	try
	{
		G4VSolid*	s_element = NULL;
		G4VSolid*	s_mask = NULL;

/*
		s_mask = new G4Tubs(
			"mask",
			0.,
			m_radius+m_ethick*1.5,
			m_eheight/2,
			0.*deg,
			360.*deg
			);
*/

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
/////////////
/*
		G4LogicalVolume*	mask_log = new G4LogicalVolume(
						s_mask,
						mask_mat,
						"mask_log"
						);

		G4VPVParameterisation*	mask_param = new MaskElement(
						this
						);

		G4VPhysicalVolume*	mask_phys = new G4PVParameterised(
						"mask_phys",
						element_log,
						mask_log,
						kUndefined,
						m_ecount,
						mask_param
						);
*/
////////////

		G4RotationMatrix	mR;		//mask
		G4ThreeVector		mT(0.,0.,0.);	//mask

		G4double local_time,angle,angle_offset;
		local_time = angle = angle_offset = 0.0;
		if(!__SUCCEEDED(GSMS::get_time(&local_time)))
			return GSMS_ERR;

		angle_offset = (m_speed * local_time);

		std::cerr << "Mask angle offset: " << angle_offset*360/2/pi << std::endl;

		for(int i=0;i<m_ecount;i++)
			if(!isTransparent(i))
			{
				G4RotationMatrix	mRe;		//element
				G4ThreeVector		mTe;		//element
				angle = ( (float)i/(float)m_ecount*2*pi + angle_offset );
				G4float xoff = (m_radius+m_ethick/2)*cos(angle);
				G4float yoff = (m_radius+m_ethick/2)*sin(angle);
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
					true,
					i
					);
//						&mRe,
//						G4ThreeVector(xoff,yoff,zoff),
//						"mask_phys",
//						element_log,
//						world,
//						false,
//						0);
				m_mask.push_back(mask_phys);

				//m_assembly->AddPlacedVolume(element_log,mTe,&mRe);
				std::cerr << "Element " << i << " at angle " << angle*360/2/pi
					<< " xOff = " << xoff
					<< " yOff = " << yoff
					<< " zOff = " << zoff
					<< std::endl;
			};

//		m_assembly->MakeImprint(world->GetLogicalVolume(),mT,&mR, true);

		G4VisAttributes*	element_vis = new G4VisAttributes(GSMS_COLOR_ELEMENT);

		element_vis->SetVisibility(true);
		element_vis->SetForceSolid(true);
		element_log->SetVisAttributes(element_vis);

////////////
	}
	catch(...)
	{
		return GSMS_ERR;
	};


	return GSMS_OK;
};

unsigned int	GSMS::Mask::getEMat(std::string*	emat)
{
	if(!emat) return GSMS_ERR;
	try
	{
		*emat = m_emat;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::Mask::setEMat(std::string*	emat)
{
	if(!emat) return GSMS_ERR;
	try
	{
		m_emat = *emat;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

