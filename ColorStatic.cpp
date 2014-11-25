// ColorStatic.cpp : implementation file
//

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "ColorStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorStatic

CColorStatic::CColorStatic()
{
	m_ctrlText = RGB (0    ,0    ,0   );
	m_clrBkgnd = RGB (0xC0 ,0xC0 ,0xC0);
	
	m_brush.CreateSolidBrush(m_clrBkgnd);
}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	//{{AFX_MSG_MAP(CColorStatic)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorStatic message handlers

HBRUSH CColorStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	pDC->SetTextColor(m_ctrlText);
	pDC->SetBkColor(m_clrBkgnd);

	return m_brush;
}
