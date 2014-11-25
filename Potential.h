// Potential.h: interface for the Potential class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POTENTIAL_H__E7A06122_D8AE_4876_B203_AEC511139658__INCLUDED_)
#define AFX_POTENTIAL_H__E7A06122_D8AE_4876_B203_AEC511139658__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

#include "TableSetFunction.h"

class Potential  
{
public:
	Potential() : name(generateNewName()) {};
	Potential(std::string name) : name(name) {};
	virtual ~Potential();

	std::string name;

	TableSetFunction energyDistribution;
	TableSetFunction forceDistribution;
	TableSetFunction electronicDensityDistribution;

private:
	static int instancesCount;
	static std::string generateNewName();

};

#endif // !defined(AFX_POTENTIAL_H__E7A06122_D8AE_4876_B203_AEC511139658__INCLUDED_)
