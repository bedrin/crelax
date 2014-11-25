// AtomPair.h: interface for the AtomPair class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATOMPAIR_H__440C1B29_43B3_4623_9C3F_B5214CFF1AEB__INCLUDED_)
#define AFX_ATOMPAIR_H__440C1B29_43B3_4623_9C3F_B5214CFF1AEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Atom.h"

// TODO: extend std::pair
class AtomPair  
{
public:
	AtomPair();
	AtomPair(Atom* atom1, Atom* atom2) : atom1(atom1), atom2(atom2) {};
	virtual ~AtomPair();

	Atom* atom1;
	Atom* atom2;

	std::pair<AtomType*, AtomType*> getAtomTypePair() { 
		if (atom1->atomType < atom2->atomType) {
			return std::pair<AtomType*, AtomType*>(atom1->atomType, atom2->atomType); 
		} else {
			return std::pair<AtomType*, AtomType*>(atom2->atomType, atom1->atomType); 
		}
	};

};

#endif // !defined(AFX_ATOMPAIR_H__440C1B29_43B3_4623_9C3F_B5214CFF1AEB__INCLUDED_)
