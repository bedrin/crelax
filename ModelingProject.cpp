// ModelingProject.cpp: implementation of the ModelingProject class.+
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "ModelingProject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ModelingProject::ModelingProject()
{
	migratingAtom = NULL;
}

ModelingProject::ModelingProject(Lattice* lattice)
{
	lattices.push_back(lattice);
	activeLattice = lattice;
	migratingAtom = NULL;
}

ModelingProject::~ModelingProject()
{

}

void ModelingProject::populateAtomTypes() {
	std::deque<Lattice*>::const_iterator latticeIterator;
	for (latticeIterator = lattices.begin(); latticeIterator != lattices.end(); latticeIterator++) {
		Lattice* lattice = *latticeIterator;
		std::deque<Atom*>& atoms = lattice->atoms;
		std::deque<Atom*>::const_iterator atomsIterator;
		for (atomsIterator = atoms.begin(); atomsIterator != atoms.end(); atomsIterator++) {
			Atom* atom = *atomsIterator;
			atomTypes.insert(atom->atomType);
		}
	}
}

void ModelingProject::populatePotentials() {
	populateAtomTypes();
	
	std::set<AtomType*>::iterator atomTypesIteratorI;
	std::set<AtomType*>::iterator atomTypesIteratorJ;
	for (atomTypesIteratorI = atomTypes.begin(); atomTypesIteratorI != atomTypes.end(); atomTypesIteratorI++) {
		AtomType* atomTypeI = *atomTypesIteratorI;
		for (atomTypesIteratorJ = atomTypesIteratorI; atomTypesIteratorJ != atomTypes.end(); atomTypesIteratorJ++) {
			AtomType* atomTypeJ = *atomTypesIteratorJ;
			if (atomTypeI < atomTypeJ) {
				std::pair<AtomType*,AtomType*> atomTypePair(atomTypeI,atomTypeJ);
				potentials.insert(std::map<std::pair<AtomType*,AtomType*>,Potential*>::value_type(atomTypePair,0));
			} else {
				std::pair<AtomType*,AtomType*> atomTypePair(atomTypeJ,atomTypeI);
				potentials.insert(std::map<std::pair<AtomType*,AtomType*>,Potential*>::value_type(atomTypePair,0));
			}
		}
	}
}