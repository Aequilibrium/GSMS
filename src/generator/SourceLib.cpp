/***************************************************************************
 *   Copyright (C) 2009 by P.Voylov   *
 *   pvoilov@aidoss.com   *
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

#include "SourceLib.h"

GSMS::Source*	util::SourceLib::create_source(std::string	name, float activity, G4ThreeVector	coords){

	GSMS::Source*	src = new GSMS::Source();

	if(name == "Cs137")	{
		src->push_gamma(0.032, 0.058);
		src->push_gamma(0.036, 0.014);
		src->push_gamma(0.662, 0.9);
	}
	if(name == "Co57")	{
		src->push_gamma(0.122, 0.855);
		src->push_gamma(0.136, 0.106);
	}
	if(name == "Co60")	{
		src->push_gamma(1.173, 1.0);
		src->push_gamma(1.332, 1.0);
	}
	if(name == "Ba133")	{
		src->push_gamma(0.030, 34.25);
		src->push_gamma(0.031, 63.42);
		src->push_gamma(0.035, 22.76);
		src->push_gamma(0.081, 32.97);
		src->push_gamma(0.276, 6.9);
		src->push_gamma(0.303, 17.79);
		src->push_gamma(0.356, 60.5);
		src->push_gamma(0.384, 8.67);
	}
	if(name == "K40")	{
		src->push_gamma(1.461, 0.107);
	}

	src->normalize_activities();
	src->set_activity(activity);
	src->set_coords(coords);

	return src;
}