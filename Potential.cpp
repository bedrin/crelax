// Potential.cpp: implementation of the Potential class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "Potential.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Potential::~Potential()
{

}

int Potential::instancesCount = 0;

std::string Potential::generateNewName() {
	std::string potentialName = "Potential ";
	int instanceNumber = ++Potential::instancesCount;
        
	char instanceNumberString[4];
    itoa(instanceNumber, instanceNumberString, 10);

	potentialName += instanceNumberString;
	return potentialName;
}
