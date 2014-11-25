// MigrationStepResults.h: interface for the MigrationStepResults class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIGRATIONSTEPRESULTS_H__B64418DE_4678_4B2E_BAE6_8F9DAF78636C__INCLUDED_)
#define AFX_MIGRATIONSTEPRESULTS_H__B64418DE_4678_4B2E_BAE6_8F9DAF78636C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RelaxationResults.h"
#include "Vector.h"

class MigrationStepResults : public RelaxationResults  
{
public:
	MigrationStepResults();
	virtual ~MigrationStepResults();

	MigrationStepResults(RelaxationResults& relaxationResults) : RelaxationResults(relaxationResults) {};

	Vector migratingAtomCoordinates;
};

#endif // !defined(AFX_MIGRATIONSTEPRESULTS_H__B64418DE_4678_4B2E_BAE6_8F9DAF78636C__INCLUDED_)
