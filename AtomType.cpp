// AtomType.cpp: implementation of the AtomType class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "AtomType.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
AtomType::AtomType(const char* name, const double mass) 
{
	setName(name);
	this->mass = mass;
	this->color = RGB(0,0,0);
}

AtomType::AtomType(const AtomType& atomType) {
	setName(atomType.name);
	mass = atomType.mass;
}

AtomType::AtomType()
{

}

void AtomType::setName(const char* name)
{
	for (byte i = 0; i < 3; i++) {
		this->name[i] = name[i];
	}
}

AtomType::~AtomType()
{
	//delete name;
}
