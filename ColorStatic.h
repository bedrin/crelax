#if !defined(AFX_COLORSTATIC_H__2660ACE6_78E3_4CC0_A604_6EFCD60C1BF7__INCLUDED_)
#define AFX_COLORSTATIC_H__2660ACE6_78E3_4CC0_A604_6EFCD60C1BF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorStatic window

class CColorStatic : public CStatic
{
// Construction
public:
	CColorStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF m_clrBkgnd;
	COLORREF m_ctrlText;
	CBrush m_brush;
	virtual ~CColorStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSTATIC_H__2660ACE6_78E3_4CC0_A604_6EFCD60C1BF7__INCLUDED_)
