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


#ifndef DIGI_H_
#define DIGI_H_

#include <geant/G4VDigi.hh>
#include <geant/G4TDigiCollection.hh>
#include <geant/G4Allocator.hh>
#include <geant/G4ThreeVector.hh>

namespace GSMS {

class Digi : public G4VDigi {

public:
	Digi();
	~Digi();
	Digi(const Digi&);
const	Digi&	operator=(const Digi&);
int	operator==(const Digi&) const;

inline	void*	operator new(size_t);
inline	void	operator delete(void*);

	void	Draw();
	void	Print();

private:
	G4double	m_time;
	G4double	m_ene;
	G4int		m_channel;

public:

inline	void		set_time(G4double time) {m_time = time;}
inline	void		set_ene(G4double ene) {m_ene = ene;}
inline	void		set_channel(G4int ch)	{m_channel = ch;}
inline	G4double	get_time() {return m_time;}
inline	G4double	get_ene() {return m_ene;}
inline	G4int		get_channel()	{return m_channel;}
};

typedef	G4TDigiCollection<Digi>	DigitsCollection;
extern	G4Allocator<Digi>	DigiAllocator;
inline	void*	Digi::operator new(size_t) {
	void*	aDigi;
	aDigi = (void*)	DigiAllocator.MallocSingle();
	return aDigi;
}

inline	void	Digi::operator delete(void*	aDigi) {
	DigiAllocator.FreeSingle((Digi*) aDigi);
}

}

#endif