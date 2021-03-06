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

#include "Source.h"
#include <sys/stat.h>
#include <sys/types.h>

#include <geant/G4Gamma.hh>
#include "config/GSMS.h"

unsigned int	GSMS::Source::save(std::ofstream* stream)
{
	Source*	pSource = this;
	boost::archive::xml_oarchive out(*stream);
	out << BOOST_SERIALIZATION_NVP(pSource);
}

void	GSMS::Source::generate_G4(G4GeneralParticleSource*	dst, G4double	dAngle) {

	if (!dst) return;
	for(int i=0; i<m_gamma.size(); i++) {
		G4float	ene = m_gamma[i].first;
		G4float	act = m_gamma[i].second;

		dst->AddaSource(act);
		dst->SetParticleDefinition(G4Gamma::Gamma());
		G4SingleParticleSource*	src = dst->GetCurrentSource();
		src->GetEneDist()->SetMonoEnergy(ene);

		src->GetAngDist()->SetAngDistType("iso");
		src->GetPosDist()->SetPosDisType("Point");
		src->GetEneDist()->SetEnergyDisType("Mono");

		//src->GetPosDist()->SetCentreCoords(get_coords());
		//src->GetPosDist()->SetCentreCoords(G4ThreeVector(1., 0., 0.));
		src->GetPosDist()->SetCentreCoords(G4ThreeVector(m_x, m_y, m_z));

		G4double	basePhi = 0.0;
		m_x != 0.0 ? basePhi = std::atan(m_y/m_x) :
			m_y > 0 ? basePhi = pi/2 : basePhi = -pi/2;

		if(m_x < 0.0 ) basePhi = -pi + basePhi;

		std::cerr << "X: " << m_x << " Y: " << m_y << " Phi: " << basePhi << std::endl;
		
		
		G4double	dPhi = GSMS::get_hull().get_delta_phi(get_coords());
		G4double	baseTheta = pi/2;//TODO

		G4double	dTheta = GSMS::get_hull().get_delta_theta(get_coords());
		std::cerr << "dPhi: " << dPhi*360/2/pi << "; dTheta" << dTheta*360/2/pi << std::endl;

		//dPhi = 3*pi/2/180;//2*pi/2/180;
		//dTheta = 16*pi/2/180;//6*pi/2/180;

		src->GetAngDist()->SetMinPhi(basePhi - dPhi);
		src->GetAngDist()->SetMaxPhi(basePhi + dPhi);
		src->GetAngDist()->SetMinTheta(baseTheta - dTheta);
		src->GetAngDist()->SetMaxTheta(baseTheta + dTheta);
		std::cerr << ene << std::endl;
		std::cerr << act << std::endl;
	}
}

void	GSMS::Source::normalize_activities() {
	G4double	summ = 0.0;
	for(int i=0; i<m_gamma.size(); i++)
		summ += m_gamma[i].second;
	for(int i=0; i<m_gamma.size(); i++)
		m_gamma[i].second = m_gamma[i].second/summ;
}