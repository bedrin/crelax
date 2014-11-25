// LatticeElement.h: interface for the LatticeElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LATTICEELEMENT_H__838E3DE3_232E_4D65_8DF6_E7D1914ED280__INCLUDED_)
#define AFX_LATTICEELEMENT_H__838E3DE3_232E_4D65_8DF6_E7D1914ED280__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vector.h"

class LatticeElement  
{
public:
	Vector r;
	bool visible;
	LatticeElement();
	virtual ~LatticeElement();

};

#endif // !defined(AFX_LATTICEELEMENT_H__838E3DE3_232E_4D65_8DF6_E7D1914ED280__INCLUDED_)
