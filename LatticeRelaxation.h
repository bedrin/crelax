// LatticeRelaxation.h : main header file for the LATTICERELAXATION application
//

#if !defined(AFX_LATTICERELAXATION_H__FE103B0E_7161_4082_AD82_F1B04B3ED86B__INCLUDED_)
#define AFX_LATTICERELAXATION_H__FE103B0E_7161_4082_AD82_F1B04B3ED86B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationApp:
// See LatticeRelaxation.cpp for the implementation of this class
//

class CLatticeRelaxationApp : public CWinApp
{
public:
	CLatticeRelaxationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLatticeRelaxationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLatticeRelaxationApp)
	afx_msg void OnAppAbout();
	afx_msg void On3dview();
	afx_msg void OnUpdate3dview(CCmdUI* pCmdUI);
	afx_msg void OnTableview();
	afx_msg void OnUpdateTableview(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	public:
	CView* m_pOldView;
	CView* m_pNewView;
	CView* SwitchView( );
	bool tableView;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LATTICERELAXATION_H__FE103B0E_7161_4082_AD82_F1B04B3ED86B__INCLUDED_)
