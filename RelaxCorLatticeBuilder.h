// RelaxCorLatticeBuilder.h: interface for the RelaxCorLatticeBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RELAXCORLATTICEBUILDER_H__84AEC629_D929_4650_9220_61C7ECA95AFA__INCLUDED_)
#define AFX_RELAXCORLATTICEBUILDER_H__84AEC629_D929_4650_9220_61C7ECA95AFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LatticeBuilder.h"

class RelaxCorLatticeBuilder : public LatticeBuilder  
{
public:
	RelaxCorLatticeBuilder();
	virtual ~RelaxCorLatticeBuilder();

	virtual Lattice* loadLattice(std::istream* inputStream);
	virtual void storeLattice(Lattice* lattice, std::ostream* outputStream);

};

#endif // !defined(AFX_RELAXCORLATTICEBUILDER_H__84AEC629_D929_4650_9220_61C7ECA95AFA__INCLUDED_)
