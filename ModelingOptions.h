// ModelingOptions.h: interface for the ModelingOptions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODELINGOPTIONS_H__820D4644_E0A3_4055_AF79_83533BBAAC45__INCLUDED_)
#define AFX_MODELINGOPTIONS_H__820D4644_E0A3_4055_AF79_83533BBAAC45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ModelingOptions  
{
public:
	double maximumActionDistance;
	int maximumNumberOfSteps;
	int maximumNumberOfDemphings;
	double minimumKineticEnergy;
	double startDelt;
	double ddelt;
	double maxdelt;
	double diffStep;
	bool useEmbeddedAtomMethod;
	bool calculateDilatationVolume;
	double bulkModulus;
	int elasticCorrectionsAmmount;
	bool dampingEnabled;

	ModelingOptions() : 
		maximumActionDistance(1.6 * 2.86), maximumNumberOfSteps(3000), maximumNumberOfDemphings(25),
		minimumKineticEnergy(0.001), startDelt(0.001), ddelt(0.0005), maxdelt(0.005), diffStep(0.00001), 
		useEmbeddedAtomMethod(false), calculateDilatationVolume (false), bulkModulus(2.12),
		elasticCorrectionsAmmount(1), dampingEnabled(true) {};

	virtual ~ModelingOptions();

};

#endif // !defined(AFX_MODELINGOPTIONS_H__820D4644_E0A3_4055_AF79_83533BBAAC45__INCLUDED_)
