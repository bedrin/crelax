// Modeling.cpp: implementation of the Modeling class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "Modeling.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <algorithm>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
bool isMoveable(Atom* atom) {
	return atom->moveable;
}

Modeling::~Modeling()
{

}

void Modeling::sortAtomsMoveableFirst(std::deque<Atom*>& atoms)
{
	std::stable_partition(atoms.begin(),atoms.end(),isMoveable);
}

long Modeling::getNumberOfMoveableAtoms(std::deque<Atom*>& atoms)
{
	long numberOfMoveableAtoms = 0;
	std::deque<Atom*>::iterator atomsIterator;
	for (atomsIterator = atoms.begin(); atomsIterator != atoms.end(); atomsIterator++) {
		numberOfMoveableAtoms++;
	}
	return numberOfMoveableAtoms;
}
