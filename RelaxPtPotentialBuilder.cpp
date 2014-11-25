// RelaxPtPotentialBuilder.cpp: implementation of the RelaxPtPotentialBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "RelaxPtPotentialBuilder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TableSetFunction* RelaxPtPotentialBuilder::loadTableSetFunction(std::istream* inputStream) {
	int numberOfSteps;
	double minimalArgument;
	double maximumArgument;
	double step;
	double* valuesTable;

	*inputStream >> numberOfSteps >> step >> minimalArgument >> maximumArgument;

	step = 1.0 / step;
	maximumArgument *= a0;

	valuesTable = new double[numberOfSteps];
	for (int i = 0; i < numberOfSteps; i++) {
		double value;
		*inputStream >> value;
		valuesTable[i] = value;
	}

	TableSetFunction* tableSetFunction = new TableSetFunction();

	tableSetFunction->numberOfSteps = numberOfSteps;
	tableSetFunction->step = step;
	tableSetFunction->minimalArgument = minimalArgument;
	tableSetFunction->minimalValue = valuesTable[0];
	tableSetFunction->maximumArgument = maximumArgument;
	tableSetFunction->maximumValue = 0.0;
	tableSetFunction->valuesTable = valuesTable;

	return tableSetFunction;
}

Potential* RelaxPtPotentialBuilder::loadPotential(std::istream* inputStream)
{
	Potential* potential = new Potential();

	int numberOfSteps;
	double minimalArgument;
	double maximumArgument;
	double step;
	double* valuesTable;

	*inputStream >> numberOfSteps >> step >> minimalArgument >> maximumArgument;

	step = 1.0 / step;
	maximumArgument *= a0;

	valuesTable = new double[numberOfSteps];
	for (int i = 0; i < numberOfSteps; i++) {
		double value;
		*inputStream >> value;
		valuesTable[i] = value * 160.219;
	}

	TableSetFunction& energyDistribution = potential->energyDistribution;

	energyDistribution.numberOfSteps = numberOfSteps;
	energyDistribution.step = step;
	energyDistribution.minimalArgument = minimalArgument;
	energyDistribution.minimalValue = valuesTable[0];
	energyDistribution.maximumArgument = maximumArgument;
	energyDistribution.maximumValue = 0.0;
	energyDistribution.valuesTable = valuesTable;

	//potential->energyDistribution = energyDistribution;
	
	valuesTable = new double[numberOfSteps];
	for (i = 0; i < numberOfSteps; i++) {
		double value;
		*inputStream >> value;
		valuesTable[i] = value * 160.219;
	}

	TableSetFunction& forceDistribution = potential->forceDistribution;

	forceDistribution.numberOfSteps = numberOfSteps;
	forceDistribution.step = step;
	forceDistribution.minimalArgument = minimalArgument;
	forceDistribution.minimalValue = valuesTable[0];
	forceDistribution.maximumArgument = maximumArgument;
	forceDistribution.maximumValue = 0.0;
	forceDistribution.valuesTable = valuesTable;

	//potential->forceDistribution = forceDistribution;

	return potential;
}

void RelaxPtPotentialBuilder::storePotential(Potential* potential, std::ostream* outputStream)
{
}
