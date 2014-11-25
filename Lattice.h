// Lattice.h: interface for the Lattice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LATTICE_H__F791D765_7274_4695_9F7E_E199FA5A8452__INCLUDED_)
#define AFX_LATTICE_H__F791D765_7274_4695_9F7E_E199FA5A8452__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <deque>
#include <algorithm>

#include "AtomPair.h"

class Lattice  
{
public:
	void calculateAtomNeighbours(const double maximumDistance);
	std::deque<Atom*> atoms;
	double a0;
	Lattice() {};
	virtual ~Lattice();

	long getNumberOfMoveableAtoms();
	long getNumberOfAtoms();
	/*std::deque<AtomPair> getMoveableNeighbourAtoms(const double maximumDistance);
	void sortAtomsMoveableFirst();*/
};

#endif // !defined(AFX_LATTICE_H__F791D765_7274_4695_9F7E_E199FA5A8452__INCLUDED_)
