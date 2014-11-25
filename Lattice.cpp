// Lattice.cpp: implementation of the Lattice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "Lattice.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Lattice::~Lattice()
{

}

long Lattice::getNumberOfAtoms()
{
	return atoms.size();
}

long Lattice::getNumberOfMoveableAtoms()
{
	long numberOfMoveableAtoms = 0;
	std::deque<Atom*>::const_iterator atomsIterator;
	for (atomsIterator = atoms.begin(); atomsIterator != atoms.end(); atomsIterator++) {
		Atom* atom = *atomsIterator;
		if (atom->moveable) {
			numberOfMoveableAtoms++;
		}
	}
	return numberOfMoveableAtoms;
}

/*
bool isMoveable(Atom& atom) {
	return atom.moveable;
}

void Lattice::sortAtomsMoveableFirst() {
	std::stable_partition(atoms.begin(),atoms.end(),isMoveable);
}

std::deque<AtomPair> Lattice::getMoveableNeighbourAtoms(const double maximumDistance)
{
	long numberOfMoveableAtoms = getNumberOfMoveableAtoms();
	long numberOfAtoms = getNumberOfAtoms();

	std::deque<AtomPair> atomPairs;

	std::deque<Atom*>::const_iterator atomsIt1, atomsIt2;
	for (atomsIt1 = atoms.begin(); atomsIt1 != atoms.end(); atomsIt1++) {
		Atom* atom1 = *atomsIt1;
		for (atomsIt2 = atomsIt1 + 1; atomsIt2 != atoms.end(); atomsIt2++) {
			Atom* atom2 = *atomsIt2;

			if (fabs(atom1->r.x - atom2->r.x) > maximumDistance) continue;
			if (fabs(atom1->r.y - atom2->r.y) > maximumDistance) continue;
			if (fabs(atom1->r.z - atom2->r.z) > maximumDistance) continue;

			Vector diff = atom1->r - atom2->r;
			if (diff.getLength() < maximumDistance) {
				atomPairs.push_back(AtomPair(atom1,atom2));
			}
		}
	}

	for (long i = 0; i < numberOfMoveableAtoms; i++) {
		Atom& atomI = atoms[i];
		for (long j = i + 1; j < numberOfAtoms; j++) {
			Atom& atomJ = atoms[j];

			if (fabs(atomI.r.x - atomJ.r.x) > maximumDistance) continue;
			if (fabs(atomI.r.y - atomJ.r.y) > maximumDistance) continue;
			if (fabs(atomI.r.z - atomJ.r.z) > maximumDistance) continue;

			Vector diff = atomI.r - atomJ.r;
			if (diff.getLength() < maximumDistance) {
				atomPairs.push_back(AtomPair(&atomI,&atomJ));
			}

		}
	}

	return atomPairs;
}
*/

void Lattice::calculateAtomNeighbours(const double maximumDistance)
{
	std::deque<Atom*>::const_iterator atomsIt1, atomsIt2;

	for (atomsIt1 = atoms.begin(); atomsIt1 != atoms.end(); atomsIt1++) {
		Atom* atom1 = *atomsIt1;
		atom1->neigbours.clear();
		atom1->mutexNeigbours.clear();
	}

	for (atomsIt1 = atoms.begin(); atomsIt1 != atoms.end(); atomsIt1++) {
		Atom* atom1 = *atomsIt1;
		//if (atom1->moveable) {
			for (atomsIt2 = atomsIt1 + 1; atomsIt2 != atoms.end(); atomsIt2++) {
				Atom* atom2 = *atomsIt2;

				if (fabs(atom1->r.x - atom2->r.x) > maximumDistance) continue;
				if (fabs(atom1->r.y - atom2->r.y) > maximumDistance) continue;
				if (fabs(atom1->r.z - atom2->r.z) > maximumDistance) continue;

				Vector diff = atom1->r - atom2->r;
				if (diff.getLength() < maximumDistance) {
					atom1->neigbours.push_back(atom2);
					atom1->mutexNeigbours.push_back(atom2);
					atom2->neigbours.push_back(atom1);
					
					
				}
			}
		//}
	}

	/*long numberOfMoveableAtoms = getNumberOfMoveableAtoms();
	long numberOfAtoms = getNumberOfAtoms();

	for (long i = 0; i < numberOfMoveableAtoms; i++) {
		Atom* atomI = atoms[i];
		for (long j = i + 1; j < numberOfAtoms; j++) {
			Atom* atomJ = atoms[j];

			if (fabs(atomI->r.x - atomJ->r.x) > maximumDistance) continue;
			if (fabs(atomI->r.y - atomJ->r.y) > maximumDistance) continue;
			if (fabs(atomI->r.z - atomJ->r.z) > maximumDistance) continue;

			Vector diff = atomI->r - atomJ->r;
			if (diff.getLength() < maximumDistance) {
				//atomPairs.push_back(AtomPair(&atomI,&atomJ));
				atomI->neigbours.push_back(atomJ);
				atomJ->neigbours.push_back(atomI);
			}

		}
	}*/
}
