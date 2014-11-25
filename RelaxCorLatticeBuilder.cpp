// RelaxCorLatticeBuilder.cpp: implementation of the RelaxCorLatticeBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "RelaxCorLatticeBuilder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RelaxCorLatticeBuilder::RelaxCorLatticeBuilder()
{

}

RelaxCorLatticeBuilder::~RelaxCorLatticeBuilder()
{

}

Lattice* RelaxCorLatticeBuilder::loadLattice(std::istream* inputStream) 
{
	Lattice* lattice = new Lattice();

	lattice->a0 = 2.86;

	AtomType* feAtomType = new AtomType("Fe", 92.76);
	feAtomType->color = RGB(0x99,0x99,0x99);

	char* corFileType = new char[3];
	int atomsAmount;
	int moveableAtomsAmount;
	*inputStream >> corFileType >> atomsAmount >> moveableAtomsAmount;
	for (int i = 0; i < atomsAmount; i++) {
		double x,y,z;
		*inputStream >> x >> y >> z;
		Atom* atom = new Atom(feAtomType, 2.86 * Vector(x,y,z),isAtomRepresentable(x,y,z),i < moveableAtomsAmount);
		lattice->atoms.push_back(atom);
	}

	return lattice;
}

void RelaxCorLatticeBuilder::storeLattice(Lattice* lattice, std::ostream* outputStream)
{
	*outputStream << "new" << " " << lattice->getNumberOfAtoms() << " " << lattice->getNumberOfMoveableAtoms() << "\n";

	std::deque<Atom*>& atoms = lattice->atoms;
	std::deque<Atom*>::const_iterator atomsIterator;


	int i = 0;

	for (atomsIterator = atoms.begin(); atomsIterator != atoms.end(); atomsIterator++) {
		Atom* atom = *atomsIterator;
		if (atom->inShell) {
			*outputStream << atom->r.x / 2.86  << " " << atom->r.y / 2.86  << " " << atom->r.z / 2.86  << " ";
			i++;
			if ( 0 == i % 5 ) {
				*outputStream << "\n";
			}
		}
	}

	for (atomsIterator = atoms.begin(); atomsIterator != atoms.end(); atomsIterator++) {
		Atom* atom = *atomsIterator;
		if (!atom->inShell) {
			*outputStream << atom->r.x / 2.86  << " " << atom->r.y / 2.86  << " " << atom->r.z / 2.86  << " ";
			i++;
			if ( 0 == i % 5 ) {
				*outputStream << "\n";
			}
		}
	}

}