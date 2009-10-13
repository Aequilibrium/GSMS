#include "Config.h"
#include <sys/stat.h>
#include <sys/types.h>

unsigned int	GSMS::Config::save(std::ofstream* stream)
{
}

unsigned int	GSMS::LogObjConfig::save(std::ofstream* stream)
{
}

unsigned int	GSMS::PhysObjConfig::save(std::ofstream* stream)
{
	PhysObjConfig*	pDetectorConfig = this;
	boost::archive::xml_oarchive out(*stream);
	out << BOOST_SERIALIZATION_NVP(pDetectorConfig);
}
