// Relaxation.h: interface for the Relaxation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RELAXATION_H__7E49D0EB_F810_4C69_A19F_21577A3FA961__INCLUDED_)
#define AFX_RELAXATION_H__7E49D0EB_F810_4C69_A19F_21577A3FA961__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Modeling.h"
#include "MigrationResults.h"

class PotentialNotLoadedException {
public:
	PotentialNotLoadedException(AtomType* atomType1, AtomType* atomType2) : 
	  atomType1(atomType1), atomType2(atomType2) {};
	  virtual ~PotentialNotLoadedException() {};

	AtomType* atomType1;
	AtomType* atomType2;
};

class Relaxation : public Modeling  
{
public:
	Relaxation(CLatticeRelaxationDoc* doc, ModelingOptions modelingOptions);
	virtual ~Relaxation();

	virtual MigrationResults migration(LPVOID pParam);
	virtual RelaxationResults relaxation(LPVOID pParam);
	virtual void resetShellForces();
	virtual void calculateForces(bool includeImmoveableAtoms = false);
	virtual void saveForces();

protected:
	virtual RelaxationResults relaxLattice(LPVOID pParam);
	virtual RelaxationResults correctShell(LPVOID pParam);
	virtual double calculatePotentialEnergyPerAtom(Atom* atomI);
	virtual double calculatePotentialEnergy(bool includeImmoveableAtoms = false);
	virtual double integrateVelocities(double delt);
	virtual void dampModel();
	
	virtual Potential* getPotential(AtomType* atomType1, AtomType* atomType2);

	ModelingOptions modelingOptions;

	Lattice* lattice;
	std::deque<Atom*>& atomsDeque;
	
};

#endif // !defined(AFX_RELAXATION_H__7E49D0EB_F810_4C69_A19F_21577A3FA961__INCLUDED_)
