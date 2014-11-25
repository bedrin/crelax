// TableSetFunction.h: interface for the TableSetFunction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLESETFUNCTION_H__29B8D3D3_652E_435F_A0A5_9C3251F00DE4__INCLUDED_)
#define AFX_TABLESETFUNCTION_H__29B8D3D3_652E_435F_A0A5_9C3251F00DE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TableSetFunction  
{
public:
	TableSetFunction() {};
	virtual ~TableSetFunction();

	double minimalArgument;
	double minimalValue;

	double maximumArgument;
	double maximumValue;

	double step;
	int numberOfSteps;

	double* valuesTable;

	double value(double argument);

	double operator () (double argument) { return value(argument); };
};

#endif // !defined(AFX_TABLESETFUNCTION_H__29B8D3D3_652E_435F_A0A5_9C3251F00DE4__INCLUDED_)
