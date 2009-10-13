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

#include "Digi.h"

G4Allocator<GSMS::Digi>	GSMS::DigiAllocator;

void	GSMS::Digi::Print() {
}

void	GSMS::Digi::Draw() {
}

int 	GSMS::Digi::operator==(const Digi& right) const {
	return (m_channel == right.m_channel && (m_time == right.m_time));
}

const GSMS::Digi&	GSMS::Digi::operator=(const GSMS::Digi& right) {
	m_channel = right.m_channel;
	m_time = right.m_time;
}

GSMS::Digi::Digi(const GSMS::Digi& right) : G4VDigi() {
	m_channel = right.m_channel;
	m_time = right.m_time;
}

GSMS::Digi::~Digi() {}

GSMS::Digi::Digi() : m_channel(0L), m_time(0.0) {}