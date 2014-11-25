// ModelingProject.h: interface for the ModelingProject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODELINGPROJECT_H__F5859619_83EC_4D41_8C63_CF067FA954B0__INCLUDED_)
#define AFX_MODELINGPROJECT_H__F5859619_83EC_4D41_8C63_CF067FA954B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Lattice.h"
#include "AtomTypePair.h"

#include <map>
#include <set>

class ModelingProject  
{
public:
	ModelingProject();
	ModelingProject(Lattice* lattice);
	virtual ~ModelingProject();

	std::set<AtomType*> atomTypes;
	std::deque<Lattice*> lattices;
	std::map<std::pair<AtomType*,AtomType*>,Potential*> potentials;

	Atom* migratingAtom;
	Vector migratingToPoint;
	int migratingSteps;

	Lattice* activeLattice;

	void populateAtomTypes();
	void populatePotentials();
};

#endif // !defined(AFX_MODELINGPROJECT_H__F5859619_83EC_4D41_8C63_CF067FA954B0__INCLUDED_)
