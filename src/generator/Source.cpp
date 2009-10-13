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
		src->GetPosDist()->SetCentreCoords(G4ThreeVector(m_X, m_Y, m_Z));

		G4double	basePhi = 0.0;
		m_X != 0.0 ? basePhi = std::atan(m_Y/m_X) :
			m_Y > 0 ? basePhi = pi/2 : basePhi = -pi/2;

		std::cerr << "X: " << m_X << " Y: " << m_Y << " Phi: " << basePhi << std::endl;
		
		G4double	dPhi = 0.0;
		G4double	baseTheta = pi/2;//TODO
		G4double	dTheta = 0.0;

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