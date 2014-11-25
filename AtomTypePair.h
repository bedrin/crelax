// AtomTypePair.h: interface for the AtomTypePair class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATOMTYPEPAIR_H__A519227C_CF89_4BCE_A42C_D50DC0A1C414__INCLUDED_)
#define AFX_ATOMTYPEPAIR_H__A519227C_CF89_4BCE_A42C_D50DC0A1C414__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtomType.h"
#include "Potential.h"

class AtomTypePair : public std::pair<AtomType, AtomType> 
{
public:
	AtomTypePair();
	AtomTypePair(AtomType atomType1, AtomType atomType2);
	virtual ~AtomTypePair();

};

#endif // !defined(AFX_ATOMTYPEPAIR_H__A519227C_CF89_4BCE_A42C_D50DC0A1C414__INCLUDED_)
