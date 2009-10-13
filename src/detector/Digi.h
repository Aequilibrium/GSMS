//
// C++ Interface: Digi
//
// Description: 
//
//
// Author: P.Voylov <pvoilov@aidoss.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

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