// LatticeBuilder.h: interface for the LatticeBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LATTICEBUILDER_H__9ED70D0C_4C14_4D10_B0F7_E85403936DA6__INCLUDED_)
#define AFX_LATTICEBUILDER_H__9ED70D0C_4C14_4D10_B0F7_E85403936DA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <istream>
#include <ostream>

#include "Lattice.h"

class LatticeBuilder  
{
public:
	LatticeBuilder() {};
	virtual ~LatticeBuilder();

protected:
	static bool isAtomInCell(double _x, double _y, double _z, double x, double y, double z);
	static bool isAtomRepresentable(double x, double y, double z);
	static bool isAtomMoveable(double x, double y, double z);
	static Atom* buildAtom(AtomType* atomType, double x, double y, double z);

public:
	static  Lattice* buildFCCLattice(double moveableRadius, double totalRadius);
	static  Lattice* buildBCCLattice(double moveableRadius, double totalRadius);

	virtual Lattice* loadLattice(std::istream* inputStream) = 0;
	virtual void storeLattice(Lattice* lattice, std::ostream* outputStream) = 0;

};

#endif // !defined(AFX_LATTICEBUILDER_H__9ED70D0C_4C14_4D10_B0F7_E85403936DA6__INCLUDED_)
