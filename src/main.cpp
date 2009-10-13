#include <config.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "typedefs.h"

#include <geant/G4RunManager.hh>
#include <geant/Randomize.hh>

#include "config/GSMS.h"

bool	__SUCCEEDED(unsigned int ARG)
{
	bool result = false;
	if(ARG == GSMS_OK)
		result = true;
	return result;
}

int main(int argc, char* argv[])
{
	puts(PACKAGE_STRING);

	std::cout << GSMS::GSMS::unserialize("text.gz") << std::endl;
	//std::cout << GSMS::GSMS::serialize("text.gz") << std::endl;

	GSMS::GSMS::setVerbosity(0);
	std::cout << GSMS::GSMS::initRunManager() << std::endl;

	return 0;
}
