// Atom.h: interface for the Atom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATOM_H__296B909E_5C3A_40B7_9EC4_FACFF9E3D243__INCLUDED_)
#define AFX_ATOM_H__296B909E_5C3A_40B7_9EC4_FACFF9E3D243__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

#include "LatticeElement.h"
#include "AtomType.h"

class Atom
{
public:
	Vector v;
	Vector r;

	Vector q1, q2, q3, q4, q5;
	Vector rSaved;
	Vector vSaved;

	bool moveable;
	bool visible;
	bool inShell;

	AtomType* atomType;
	std::vector<Atom*> neigbours;
	std::vector<Atom*> mutexNeigbours;

	Atom();
	//Atom(const Atom& a);
	Atom(AtomType* atomType, Vector r, bool visible, bool moveable) : atomType(atomType), r(r), visible(visible), inShell(!moveable), moveable(moveable) {};
	virtual ~Atom();

};

#endif // !defined(AFX_ATOM_H__296B909E_5C3A_40B7_9EC4_FACFF9E3D243__INCLUDED_)
