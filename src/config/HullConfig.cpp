#include "HullConfig.h"
#include <sys/stat.h>
#include <sys/types.h>

unsigned int	GSMS::HullConfig::save(std::ofstream* stream)
{
	HullConfig*	pHullConfig = this;
	boost::archive::xml_oarchive out(*stream);
	out << BOOST_SERIALIZATION_NVP(pHullConfig);
}
