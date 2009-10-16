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
/*!\file Exposition.h
 * \brief Exposition configuration
 */
#ifndef EXPOSITION_H
#define EXPOSITION_H

#include "config/Waypoint.h"

namespace GSMS {

/*!\typedef Spectrum
 * \brief spectrum
 */
typedef std::vector<std::vector<G4double> > Spectrum;

/*!\typedef SpectrumMap
 * \brief spectra map
 */
typedef std::map<std::string,Spectrum>	SpectrumMap;

/*!\typedef SpectrumIterator
 * \brief iterator over spectra map
 */
typedef SpectrumMap::iterator	SpectrumIterator;

/*!\class Exposition
 * \brief Exposition configuration
 */
class Exposition : public LogObjConfig
{
	friend class boost::serialization::access;

	/*!\fn serialize(Archive & ar, const unsigned int version)
	 * \brief Mask serializer
	 * \param ar output archive
	 * \param version archive version
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar	& BOOST_SERIALIZATION_BASE_OBJECT_NVP(LogObjConfig)
			& BOOST_SERIALIZATION_NVP(m_spectra);
	}
protected:

	/*!\var m_spectra
	 * \brief accumulated spectra
	 */
	SpectrumMap	m_spectra;

public:
	/*!\fn Exposition()
	 * \brief Default constructor
	 */
	Exposition() : LogObjConfig()
		{
			m_type = "Exposition";

			Spectrum	spectrum;
//			for(int i=0; i< 217; i++) {
//				std::vector<G4double>	discrete;
//				for(int j=0; j< 1024; j++)
//					discrete.push_back(0.);
//				spectrum.push_back(discrete);
//			}
			push_spectrum(spectrum, "217*1024");
		}

	/*!\fn ~Exposition()
	 * \brief Default destructor
	 */
virtual	~Exposition() {}

	/*!\fn unsigned int save(std::ofstream* stream)
	 * \brief Self-serializer
	 * \param stream output stream
	 * \return exit code
	 */
virtual unsigned int	save(std::ofstream* stream);

	/*!\fn SpectrumIterator	get_spectrum_iterator()
	 * \brief Spectra iterator
	 * \return iterator of spectra map
	 */
inline	SpectrumIterator	get_spectrum_iterator() {
		SpectrumIterator	it = m_spectra.begin();
		return it;
	}

	/*!\fn Spectrum&	get_spectrum(std::string name)
	 * \brief Spectrum getter
	 * \param name assigned name of the spectrum
	 * \return spectrum
	 */
inline	Spectrum&	get_spectrum(std::string name) {
		return m_spectra[name];
	}

	/*!\fn unsigned int	get_spectrum_count()
	 * \brief Number of spectra
	 * \return number of spectra
	 */
inline	unsigned int	get_spectrum_count() {
		return m_spectra.size();
	}

	/*!\fn void	push_spectrum(std::vector<std::vector<G4double> > spectrum, std::string name)
	 * \brief Add spectrum
	 * \param spectrum accumulated spectrum (normally G4double[217][1024])
	 * \param name assigned name of the spectrum
	 */
inline	void	push_spectrum(Spectrum spectrum, std::string name) {
		
		m_spectra[name] = spectrum;
	}

	/*!\fn const Spectrum&	operator[](std::string name) {	return m_spectra[name];}
	 * \brief Access op
	 * \param name assigned name of the spectrum
	 */
	Spectrum&	operator[](std::string name) {
		return m_spectra[name];
	}

	/*!\fn const std::vector<std::vector<G4double> >&	operator[](unsigned int idx) {	return m_spectra[name];}
	 * \brief Access op
	 * \param idx spectrum index
	 */
	Spectrum&	operator[](unsigned int idx) {
		if(idx >= m_spectra.size()) throw __EXCEPTION(_E_OUT_OF_BOUND);
		SpectrumIterator	it = m_spectra.begin();
		for(int i =0; i<idx; i++, it++) {}
		return (*it).second;
	}

	/*!\fn int	get_discrete_complete_count(std::string name)
	 * \brief obtain current angular discrete
	 * \param name assigned name of the spectrum
	 * \return discrete index
	 */
inline	int get_discrete_complete_count(std::string name) {
	SpectrumIterator	itr = m_spectra.find(name);
	if(itr == m_spectra.end())
		return -1;
	return (*itr).second.size();
	}

};

}; //namespace GSMS

BOOST_CLASS_VERSION(GSMS::Exposition,1)

#endif /*EXPOSITION_H*/