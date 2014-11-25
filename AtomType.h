// AtomType.h: interface for the AtomType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATOMTYPE_H__CB2FB60A_18CB_4848_8092_DE4EB91EC1BC__INCLUDED_)
#define AFX_ATOMTYPE_H__CB2FB60A_18CB_4848_8092_DE4EB91EC1BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "TableSetFunction.h"

class AtomType  
{
public:
	AtomType(const char* name, const double mass);
	AtomType(const AtomType& atomType);
	AtomType();
	virtual ~AtomType();

	TableSetFunction embeddingEnergy;

	//std::string name;
	char name [3];
	double mass;
	COLORREF color; // todo: remove this dependency from windows

	void setName(const char* name);
	
	AtomType& operator =  (const AtomType& atomType) { setName(atomType.name); mass = atomType.mass; return *this; };
	
	bool	  operator == (const AtomType& atomType) const { return ((name[0] == atomType.name[0]) && (name[1] == atomType.name[1]) && (name[2] == atomType.name[2])); };

	bool	  operator <  (const AtomType& atomType) const { return ((name[0] < atomType.name[0]) || ((name[0] == atomType.name[0]) && (name[1] < atomType.name[1]))); };

	/*bool	  operator >  (const AtomType& atomType) const { return mass >  atomType.mass; };
	bool	  operator >= (const AtomType& atomType) const { return mass >= atomType.mass; };
	bool	  operator <  (const AtomType& atomType) const { return mass <  atomType.mass; };
	bool	  operator <= (const AtomType& atomType) const { return mass <= atomType.mass; };*/

};

#endif // !defined(AFX_ATOMTYPE_H__CB2FB60A_18CB_4848_8092_DE4EB91EC1BC__INCLUDED_)
