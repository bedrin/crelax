// Direct3DView.h: interface for the Direct3DView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECT3DVIEW_H__8594DF2C_55C0_4AED_B801_04632A3BBBF1__INCLUDED_)
#define AFX_DIRECT3DVIEW_H__8594DF2C_55C0_4AED_B801_04632A3BBBF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <D3DX8.h>

class Direct3DView  
{
public:
	Direct3DView();
	virtual ~Direct3DView();

protected:
	InitScene(CRect rect);
	bool Resize(int width, int height);

	LPDIRECT3DDEVICE8 direct3DDevice;
	D3DPRESENT_PARAMETERS direct3DPresentParameters;
	D3DDISPLAYMODE direct3DDisplayMode;
	LPDIRECT3D8 direct3D;
	InitDirect3D(HWND hWnd);
};

#endif // !defined(AFX_DIRECT3DVIEW_H__8594DF2C_55C0_4AED_B801_04632A3BBBF1__INCLUDED_)
