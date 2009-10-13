#include "Job.h"
#include <sys/stat.h>
#include <sys/types.h>

unsigned int	GSMS::Job::save(std::ofstream* stream)
{
	Job*	pJob = this;
	boost::archive::xml_oarchive out(*stream);
	out << BOOST_SERIALIZATION_NVP(pJob);
}
