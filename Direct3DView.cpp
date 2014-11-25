// Direct3DView.cpp: implementation of the Direct3DView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Direct3DView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma comment(lib,"d3d8.lib")
#pragma comment(lib,"d3dx8.lib")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Direct3DView::Direct3DView()
{

}

Direct3DView::~Direct3DView()
{

}

Direct3DView::InitDirect3D(HWND hWnd)
{
        HRESULT hr;
                
        direct3D = Direct3DCreate8( D3D_SDK_VERSION );
        if(!direct3D){
                AfxMessageBox("Error getting Direct3D");
        }
        
        hr=direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&direct3DDisplayMode);
        if(FAILED(hr)){
                AfxMessageBox("Error getting display mode\n");
        }
        
        ZeroMemory(&direct3DPresentParameters,sizeof(direct3DPresentParameters));

        direct3DPresentParameters.SwapEffect     = D3DSWAPEFFECT_DISCARD;
        direct3DPresentParameters.hDeviceWindow  = hWnd;
        direct3DPresentParameters.BackBufferCount= 1;

        direct3DPresentParameters.EnableAutoDepthStencil = TRUE;
        direct3DPresentParameters.AutoDepthStencilFormat = D3DFMT_D16;

        direct3DPresentParameters.Windowed          = TRUE;
        direct3DPresentParameters.BackBufferFormat  = direct3DDisplayMode.Format;
   
        direct3DDevice = NULL;

        hr=direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
                D3DCREATE_SOFTWARE_VERTEXPROCESSING, &direct3DPresentParameters, &direct3DDevice);
        if (hr == D3DERR_INVALIDCALL) {
            AfxMessageBox("Invalid call\n");
        } else if (D3DERR_NOTAVAILABLE == hr) {
			AfxMessageBox("D3D Device Not Available\n");
		} else if (D3DERR_OUTOFVIDEOMEMORY  == hr) {
			AfxMessageBox("Out of memory\n");
		}


        if(FAILED(hr)){
                AfxMessageBox("Error creating device\n");
        }

}

bool Direct3DView::Resize(int width, int height) 
{
	if (0 == height) return false;

    D3DXMATRIX m;
    float aspectRatio = (float)width/(float)height;
    float FOV = D3DX_PI/4;
   
    D3DXMatrixPerspectiveFovLH(&m, FOV, aspectRatio, 1.0f, 100.0f);

	try {
		if (direct3DDevice)
			direct3DDevice->SetTransform(D3DTS_PROJECTION, &m);
	} catch (void* e) {
	}
	
    return true;

}

Direct3DView::InitScene(CRect rect)
{
        D3DXMATRIX matProj;

		// Code below for alpha blending
		/*direct3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_SELECTARG1);
		direct3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_DIFFUSE);

		direct3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		direct3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		direct3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);

        direct3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
        direct3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
        direct3DDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_XRGB(0,0,0) );*/

        /*D3DXMatrixPerspectiveFovLH(&matProj, //Result Matrix
                              D3DX_PI/4,//Field of View, in radians. (PI/4) is typical
                              (3.14f / 2.0f),     //Aspect ratio
                              1.0f,     //Near view plane
                              100.0f ); // Far view plane

   
        direct3DDevice->SetTransform( D3DTS_PROJECTION, &matProj );*/

        // Setting up the material
        D3DMATERIAL8 mtrl;
        ZeroMemory( &mtrl, sizeof(D3DMATERIAL8) );
        mtrl.Diffuse.r = 1.0f;
        mtrl.Ambient.r = 0.75f;
        mtrl.Diffuse.g = 1.0f;
        mtrl.Ambient.g = 0.75f;
        mtrl.Diffuse.b = 1.0f;
        mtrl.Ambient.b = 0.75f;
        mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
        direct3DDevice->SetMaterial( &mtrl );

        // Seting up the light
        D3DXVECTOR3 vecDir;
        D3DLIGHT8 light;
        
        ZeroMemory( &light, sizeof(D3DLIGHT8) );
        light.Type = D3DLIGHT_DIRECTIONAL;
		
        light.Diffuse.r = 1.0f;
        light.Diffuse.g = 1.0f;
        light.Diffuse.b = 1.0f;

		light.Position.x = 5.0f;
		light.Position.y = 5.0f;
		light.Position.z = -10.0f;


		light.Direction.x = -5.0f;
		light.Direction.y = -5.0f;
		light.Direction.z = 10.0f;
        vecDir = D3DXVECTOR3(0.0f, 0.0f, 100.0f );
        //D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
        
        light.Range = 1000.0f;
        
        direct3DDevice->SetLight( 0, &light );
        direct3DDevice->LightEnable( 0, TRUE);

		Resize(rect.right, rect.bottom);

}

