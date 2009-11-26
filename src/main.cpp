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

	GSMS::GSMS::unserialize("text.gz");

	GSMS::GSMS::setVerbosity(0);
	GSMS::GSMS::initRunManager();
	GSMS::GSMS::run_forced(50000);//Co60
	//GSMS::GSMS::run_forced(3378);//Cs137
	//GSMS::GSMS::run_forced(7200);//Ba133

	return 0;
}
