//
// C++ Implementation: Digi
//
// Description: 
//
//
// Author: P.Voylov <pvoilov@aidoss.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

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