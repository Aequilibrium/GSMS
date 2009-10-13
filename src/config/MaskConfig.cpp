#include "MaskConfig.h"
#include <sys/stat.h>
#include <sys/types.h>

#include "GSMS.h"

#include <geant/G4Tubs.hh>
#include <geant/G4Box.hh>
#include <geant/G4PVPlacement.hh>
#include <geant/G4VisAttributes.hh>

#include <geant/G4PVParameterised.hh>
#include <geant/G4VPVParameterisation.hh>

void		GSMS::MaskElement::ComputeTransformation(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
		std::cout << "Tran" << copyNo << std::endl;
}

void		GSMS::MaskElement::ComputeDimensions(G4Box& element, const G4int copyNo, G4VPhysicalVolume* physVol) const
{
		std::cout << "Dim" << copyNo << std::endl;
}

G4Material*	GSMS::MaskElement::ComputeMaterial(const G4int copyNo, G4VPhysicalVolume* physVol, const G4VTouchable* parentTouch)
{
		std::cout << "Mat" << copyNo << std::endl;
}

bool		GSMS::MaskConfig::isTransparent(unsigned char	index)
{
//		std::cout << m_evector << std::endl;
//		std::cout << (m_evector >> index) << std::endl;
//		std::cout << ((m_evector >> index) & 1) << std::endl;
	return !(bool)((m_evector >> index) & 1);
}

unsigned int	GSMS::MaskConfig::save(std::ofstream* stream)
{
	MaskConfig*	pMaskConfig = this;
	boost::archive::xml_oarchive out(*stream);
	out << BOOST_SERIALIZATION_NVP(pMaskConfig);
}

unsigned int	GSMS::MaskConfig::imprintMask(G4VPhysicalVolume* wptr)
{
	//clean up
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
		m_assembly = new G4AssemblyVolume;
	}

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

		s_mask = new G4Tubs(
			"mask",
			0.,
			m_radius+m_ethick*1.5,
			m_eheight/2,
			0.*deg,
			360.*deg
			);

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

				m_assembly->AddPlacedVolume(element_log,mTe,&mRe);
				std::cerr << "Element " << i << " at angle " << angle*360/2/pi
					<< " xOff = " << xoff
					<< " yOff = " << yoff
					<< " zOff = " << zoff
					<< std::endl;
			};

		m_assembly->MakeImprint(world->GetLogicalVolume(),mT,&mR, true);

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

unsigned int	GSMS::MaskConfig::getRadius(G4double* radius)
{
	if(!radius) return GSMS_ERR;
	try
	{
		*radius = m_radius;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::setRadius(G4double* radius)
{
	if(!radius) return GSMS_ERR;
	try
	{
		m_radius = *radius;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::getSpeed(G4double* speed)
{
	if(!speed) return GSMS_ERR;
	try
	{
		*speed = m_speed;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::setSpeed(G4double* speed)
{
	if(!speed) return GSMS_ERR;
	try
	{
		m_speed = *speed;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::getECount(unsigned char* ecount)
{
	if(!ecount) return GSMS_ERR;
	try
	{
		*ecount = m_ecount;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::setECount(unsigned char* ecount)
{
	if(!ecount) return GSMS_ERR;
	try
	{
		m_ecount = *ecount;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::getEHeight(G4double* eheight)
{
	if(!eheight) return GSMS_ERR;
	try
	{
		*eheight = m_eheight;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::setEHeight(G4double* eheight)
{
	if(!eheight) return GSMS_ERR;
	try
	{
		m_eheight = *eheight;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::getEWidth(G4double* ewidth)
{
	if(!ewidth) return GSMS_ERR;
	try
	{
		*ewidth = m_ewidth;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::setEWidth(G4double* ewidth)
{
	if(!ewidth) return GSMS_ERR;
	try
	{
		m_ewidth = *ewidth;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::getEThick(G4double* ethick)
{
	if(!ethick) return GSMS_ERR;
	try
	{
		*ethick = m_ethick;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::setEThick(G4double* ethick)
{
	if(!ethick) return GSMS_ERR;
	try
	{
		m_ethick = *ethick;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::getEMat(std::string*	emat)
{
	if(!emat) return GSMS_ERR;
	try
	{
		*emat = m_emat;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::setEMat(std::string*	emat)
{
	if(!emat) return GSMS_ERR;
	try
	{
		m_emat = *emat;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::getEType(std::string*	etype)
{
	if(!etype) return GSMS_ERR;
	try
	{
		*etype = m_etype;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}

unsigned int	GSMS::MaskConfig::setEType(std::string*	etype)
{
	if(!etype) return GSMS_ERR;
	try
	{
		m_etype = *etype;
	}
	catch(...) {return GSMS_ERR;}
	return GSMS_OK;
}
