// RelaxPtPotentialBuilder.h: interface for the RelaxPtPotentialBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RELAXPTPOTENTIALBUILDER_H__CC68D627_5EE3_47F1_959A_03F33C1BA6DF__INCLUDED_)
#define AFX_RELAXPTPOTENTIALBUILDER_H__CC68D627_5EE3_47F1_959A_03F33C1BA6DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PotentialBuilder.h"
#include "TableSetFunction.h" 

#define DEFAULT_A0_VALUE 2.86

class RelaxPtPotentialBuilder : public PotentialBuilder  
{
public:
	RelaxPtPotentialBuilder() : a0(DEFAULT_A0_VALUE) {};
	RelaxPtPotentialBuilder(double a0) : a0(a0) {};

	virtual Potential* loadPotential(std::istream* inputStream);
	virtual TableSetFunction* loadTableSetFunction(std::istream* inputStream);
	virtual void storePotential(Potential* potential, std::ostream* outputStream);

	double a0;

};

#endif // !defined(AFX_RELAXPTPOTENTIALBUILDER_H__CC68D627_5EE3_47F1_959A_03F33C1BA6DF__INCLUDED_)
