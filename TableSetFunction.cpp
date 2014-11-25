// TableSetFunction.cpp: implementation of the TableSetFunction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "TableSetFunction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TableSetFunction::~TableSetFunction()
{
	delete valuesTable;
}

double TableSetFunction::value(double argument) {
	
	if (argument > maximumArgument) return maximumValue; 

	//if (argument < minimalArgument) return minimalValue; 

	double normalizedArgument = (argument - minimalArgument) / step + 1;
	int normalizedStep = int(normalizedArgument);

	if (normalizedStep < 1) {
		normalizedStep = 1;
	}

	return valuesTable[normalizedStep - 1] + ((valuesTable[normalizedStep] - valuesTable[normalizedStep - 1]) * (normalizedArgument - normalizedStep));

}
