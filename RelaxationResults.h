// RelaxationResults.h: interface for the RelaxationResults class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RELAXATIONRESULTS_H__AA0F2087_7D8E_4210_98D9_2A4A32D7C718__INCLUDED_)
#define AFX_RELAXATIONRESULTS_H__AA0F2087_7D8E_4210_98D9_2A4A32D7C718__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class RelaxationResults  
{
public:
	RelaxationResults() : dilatationVolume(0) {};
	virtual ~RelaxationResults();

	long   numberOfStemps;
	int    numberOfDempthings;
	double modelTime;
	double relaxationEnergy;
	DWORD  calculationTime;

	double complexEnergyBeforeRelaxation;
	double complexEnergyAfterRelaxation;
	double complexEnergyAfterRelaxationCorrected;

	double dilatationVolume;

	char* getStringValue() {
		char* buff = new char[2000];
		sprintf(buff, "Relaxation results\r\n\r\n"
						"Energy: %f eV\r\n"
						"Energy after relaxation: %f eV\r\n"
						"Energy after relaxation with elastic correction: %f eV\r\n"
						"Relaxation energy: %f eV\r\n"
						"Calculation time: %d ms\r\n"
						"Physical time: %f s\r\n"
						"Number of steps: %d \r\n"
						"Number of demphings: %d \r\n"
						"Dilatation Volume: %f \r\n"
			,complexEnergyBeforeRelaxation, complexEnergyAfterRelaxation, complexEnergyAfterRelaxationCorrected ,relaxationEnergy, calculationTime, modelTime, numberOfStemps, numberOfDempthings, dilatationVolume);

		return buff;
	};

};

#endif // !defined(AFX_RELAXATIONRESULTS_H__AA0F2087_7D8E_4210_98D9_2A4A32D7C718__INCLUDED_)
