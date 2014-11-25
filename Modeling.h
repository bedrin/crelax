// Modeling.h: interface for the Modeling class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODELING_H__C8C98518_E82C_4546_A9D3_884E0E7BAAD7__INCLUDED_)
#define AFX_MODELING_H__C8C98518_E82C_4546_A9D3_884E0E7BAAD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LatticeRelaxationDoc.h"
#include "RelaxationResults.h"
#include "ModelingOptions.h"

class Modeling  
{
public:
	Modeling(CLatticeRelaxationDoc* doc) : m_Doc(doc) {};
	virtual ~Modeling();

	virtual RelaxationResults relaxation(LPVOID pParam) = 0;

protected:
	virtual void sortAtomsMoveableFirst(std::deque<Atom*>& atoms);
	virtual long getNumberOfMoveableAtoms(std::deque<Atom*>& atoms);
	CLatticeRelaxationDoc* m_Doc;

};

#endif // !defined(AFX_MODELING_H__C8C98518_E82C_4546_A9D3_884E0E7BAAD7__INCLUDED_)
