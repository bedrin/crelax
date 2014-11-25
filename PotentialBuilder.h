// PotentialBuilder.h: interface for the PotentialBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POTENTIALBUILDER_H__7E70611B_49D6_44A2_9465_B908C87ED5A4__INCLUDED_)
#define AFX_POTENTIALBUILDER_H__7E70611B_49D6_44A2_9465_B908C87ED5A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <istream>
#include <ostream>

#include "Potential.h"

class PotentialBuilder  
{
public:
	PotentialBuilder();
	virtual ~PotentialBuilder();

	virtual Potential* loadPotential(std::istream* inputStream) = 0;
	virtual void storePotential(Potential* potential, std::ostream* outputStream) = 0;
};

#endif // !defined(AFX_POTENTIALBUILDER_H__7E70611B_49D6_44A2_9465_B908C87ED5A4__INCLUDED_)
