// LatticeBuilder.cpp: implementation of the LatticeBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "LatticeBuilder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
LatticeBuilder::~LatticeBuilder()
{

}

bool LatticeBuilder::isAtomInCell(double _x, double _y, double _z, double x, double y, double z) {
    x -= _x;
    y -= _y;
    z -= _z;
    return ((x >= 0.0f && x <= 1.0f) && (y >= 0.0f && y <= 1.0f) && (z >= 0.0f && z <= 1.0f));
}

bool LatticeBuilder::isAtomRepresentable(double x, double y, double z) {
	x += 0.5;
	y += 0.5;
	z += 0.5;
    return (
		isAtomInCell( 0.0f,0.0f, 0.0f,x,y,z) || 
		isAtomInCell( 1.0f,0.0f, 0.0f,x,y,z) || 
		isAtomInCell( 0.0f,1.0f, 0.0f,x,y,z) || 
		isAtomInCell( 1.0f,1.0f, 0.0f,x,y,z) || 
		isAtomInCell( 1.0f,0.0f,-1.0f,x,y,z) || 
		isAtomInCell(-1.0f,0.0f, 1.0f,x,y,z) || 
		isAtomInCell(-1.0f,1.0f, 1.0f,x,y,z) );
}

bool LatticeBuilder::isAtomMoveable(double x, double y, double z) {
	return ((x >= -2.0f && x <= 2.0f) && (y >= -2.0f && y <= 2.0f) && (z >= -2.0f && z <= 2.0f));
}

Atom* LatticeBuilder::buildAtom(AtomType* atomType, double x, double y, double z) {
	return new Atom(atomType,2.86 * Vector(x, y, z),isAtomRepresentable(x,y,z),isAtomMoveable(x,y,z));
}

Lattice* LatticeBuilder::buildBCCLattice(double moveableRadius, double totalRadius) {
	Lattice* lattice = new Lattice();
	
	lattice->a0 = 2.86;

	AtomType* feAtomType = new AtomType("Fe", 92.76);
	feAtomType->color = RGB(0x99,0x99,0x99);

	double ceilTotalRadius = ceil(totalRadius);

	for (float x = -ceilTotalRadius; x <= ceilTotalRadius; x += 1.0f) {
        for (float y = -ceilTotalRadius; y <= ceilTotalRadius; y += 1.0f) {
            for (float z = -ceilTotalRadius; z <= ceilTotalRadius; z += 1.0f) {
				Vector coordinates(x,y,z);
				double r = coordinates.getLength();
				if (r > totalRadius) continue;
				Atom* atom = new Atom(feAtomType, 2.86 * coordinates,isAtomRepresentable(x,y,z), r <= moveableRadius);
				lattice->atoms.push_back(atom);
            }
        }
    }

	ceilTotalRadius -= 0.5;

	for (x = -ceilTotalRadius; x <= ceilTotalRadius; x += 1.0f) {
        for (float y = -ceilTotalRadius; y <= ceilTotalRadius; y += 1.0f) {
            for (float z = -ceilTotalRadius; z <= ceilTotalRadius; z += 1.0f) {
				Vector coordinates(x,y,z);
				double r = coordinates.getLength();
				if (r > totalRadius) continue;
				Atom* atom = new Atom(feAtomType, 2.86 * coordinates,isAtomRepresentable(x,y,z), r <= moveableRadius);
				lattice->atoms.push_back(atom);
            }
        }
    }
	/*
    for (float x = -4.0f; x <= 4.0f; x += 1.0f) {
        for (float y = -4.0f; y <= 4.0f; y += 1.0f) {
            for (float z = -4.0f; z <= 4.0f; z += 1.0f) {
				lattice->atoms.push_back(buildAtom(feAtomType,x,y,z));
            }
        }
    }
    for (x = -3.5f; x <= 3.5f; x += 1.0f) {
        for (float y = -3.5f; y <= 3.5f; y += 1.0f) {
            for (float z = -3.5f; z <= 3.5f; z += 1.0f) {
                lattice->atoms.push_back(buildAtom(feAtomType,x,y,z));
            }
        }
    }
	*/
	
	return lattice;
}

Lattice* LatticeBuilder::buildFCCLattice(double moveableRadius, double totalRadius)
{
	Lattice* lattice = new Lattice();
	
	lattice->a0 = 2.86;

	AtomType* feAtomType = new AtomType("Fe", 92.76);
	feAtomType->color = RGB(0x99,0x99,0x99);

	for (float x = -totalRadius; x <= totalRadius; x += 0.5f) {
        for (float y = -totalRadius; y <= totalRadius; y += 0.5f) {
            for (float z = -totalRadius; z <= totalRadius; z += 0.5f) {
				bool xInt = x == ceil(x);
				bool yInt = y == ceil(y);
				bool zInt = z == ceil(z);
				if (xInt && yInt && zInt) continue;
				if (xInt && !yInt && !zInt) continue;
				if (!xInt && yInt && !zInt) continue;
				if (!xInt && !yInt && zInt) continue;

				Vector coordinates(x,y,z);
				double r = coordinates.getLength();
				if (r > totalRadius) continue;
				Atom* atom = new Atom(feAtomType, 2.86 * coordinates,isAtomRepresentable(x,y,z), r <= moveableRadius);
				lattice->atoms.push_back(atom);
            }
        }
    }
	
	return lattice;
}
