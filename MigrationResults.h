// MigrationResults.h: interface for the MigrationResults class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIGRATIONRESULTS_H__9BE68503_367A_48C2_B2D0_2C7E6B75D6DA__INCLUDED_)
#define AFX_MIGRATIONRESULTS_H__9BE68503_367A_48C2_B2D0_2C7E6B75D6DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "MigrationStepResults.h"

class MigrationResults  
{
public:
	MigrationResults();
	virtual ~MigrationResults();

	std::vector<MigrationStepResults> migrationStepResults;
};

#endif // !defined(AFX_MIGRATIONRESULTS_H__9BE68503_367A_48C2_B2D0_2C7E6B75D6DA__INCLUDED_)
