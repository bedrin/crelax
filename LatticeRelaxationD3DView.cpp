// LatticeRelaxationD3DView.cpp : implementation file
//

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "LatticeRelaxationDoc.h"
#include "LatticeRelaxationD3DView.h"

#include "AtomDialog.h"
#include "MigrateAtomDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/// START
struct Vertex
{
    FLOAT x, y, z;
        FLOAT nX, nY, nZ;
    DWORD color;
        DWORD specColor;
};

const DWORD VertexFVF = ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_SPECULAR );

struct my_vertex{
    FLOAT x, y, z, rhw; // The transformed position for the vertex.
    DWORD color;        // The vertex color.
};
#define D3D8T_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
/// FINISH

my_vertex g_triangle_vertices[] = {
    {   0.0f,   0.0f,   0.0f, 1.0f, 0xFFFFFFFF }, 
        {   0.0f,   0.0f,  3*2.86, 1.0f, 0xFFFFFFFF }, 

    {   0.0f,  3*2.86,   0.0f, 1.0f, 0xFFFFFFFF }, 
        {   0.0f,   0.0f,   0.0f, 1.0f, 0xFFFFFFFF }, 

        {  3*2.86,   0.0f,   0.0f, 1.0f, 0xFFFFFFFF }, 
        {   0.0f,   0.0f,   0.0f, 1.0f, 0xFFFFFFFF },

        {  3*2.86,   0.0f,  3*2.86, 1.0f, 0xFFFFFFFF }, 
        {   0.0f,   0.0f,  3*2.86, 1.0f, 0xFFFFFFFF },

        {  3*2.86,   0.0f,  3*2.86, 1.0f, 0xFFFFFFFF }, 
        {  3*2.86,   0.0f,   0.0f, 1.0f, 0xFFFFFFFF },

        {   0.0f,  3*2.86,  3*2.86, 1.0f, 0xFFFFFFFF }, 
        {  3*2.86,  3*2.86,  3*2.86, 1.0f, 0xFFFFFFFF },

        {   0.0f,  3*2.86,   0.0f, 1.0f, 0xFFFFFFFF }, 
        {  3*2.86,  3*2.86,   0.0f, 1.0f, 0xFFFFFFFF },

        {   0.0f,  3*2.86,  3*2.86, 1.0f, 0xFFFFFFFF }, 
        {   0.0f,   0.0f,  3*2.86, 1.0f, 0xFFFFFFFF }, 

    {   0.0f,  3*2.86,  3*2.86, 1.0f, 0xFFFFFFFF }, 
        {   0.0f,  3*2.86,   0.0f, 1.0f, 0xFFFFFFFF }, 

        {  3*2.86,  3*2.86,  3*2.86, 1.0f, 0xFFFFFFFF }, 
        {  3*2.86,   0.0f,  3*2.86, 1.0f, 0xFFFFFFFF }, 

        {  3*2.86,  3*2.86,  3*2.86, 1.0f, 0xFFFFFFFF }, 
        {  3*2.86,  3*2.86,   0.0f, 1.0f, 0xFFFFFFFF }, 

        {  3*2.86,  3*2.86,   0.0f, 1.0f, 0xFFFFFFFF }, 
        {  3*2.86,   0.0f,   0.0f, 1.0f, 0xFFFFFFFF }
};
IDirect3DVertexBuffer8 *g_triangle=NULL;

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationD3DView

IMPLEMENT_DYNCREATE(CLatticeRelaxationD3DView, CScrollView)

CLatticeRelaxationD3DView::CLatticeRelaxationD3DView()
	: rotationX(-0.09)
    , rotationY(-0.63)
    , clickPoint(-1)
    , cameraX(0)
    , cameraY(0)
    , cameraZ(0)
	, selectedAtom(NULL),
	initialized(false)
{
}

CLatticeRelaxationD3DView::~CLatticeRelaxationD3DView()
{
}


BEGIN_MESSAGE_MAP(CLatticeRelaxationD3DView, CScrollView)
	//{{AFX_MSG_MAP(CLatticeRelaxationD3DView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DELETE_ATOM_BUTTON, OnDeleteAtomButton)
	ON_COMMAND(ID_EDIT_BUTTON_ATOM, OnEditButtonAtom)
	ON_UPDATE_COMMAND_UI(ID_DELETE_ATOM_BUTTON, OnUpdateDeleteAtomButton)
	ON_UPDATE_COMMAND_UI(ID_EDIT_BUTTON_ATOM, OnUpdateEditButtonAtom)
	ON_COMMAND(ID_MIGRATE_ATOM_BUTTON, OnMigrateAtomButton)
	ON_UPDATE_COMMAND_UI(ID_MIGRATE_ATOM_BUTTON, OnUpdateMigrateAtomButton)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ATOM_X, OnUpdateIndicatorAtomX)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ATOM_Y, OnUpdateIndicatorAtomY)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ATOM_Z, OnUpdateIndicatorAtomZ)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationD3DView drawing

void CLatticeRelaxationD3DView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	CRect rect;
	GetClientRect(&rect);

	InitDirect3D(m_hWnd);        
	InitScene(rect);

	CLatticeRelaxationDoc* doc = GetDocument();
	CSingleLock csl(&(doc->m_CS));
	csl.Lock();

	BuildAtomMeshes();

	csl.Unlock();

    unsigned char *vb_vertices;
    HRESULT hr;
    hr=direct3DDevice->CreateVertexBuffer(24*sizeof(my_vertex),//Size of memory to be allocated
                                                       // Number of vertices * size of a vertex
                                   D3DUSAGE_WRITEONLY, // We never need to read from it so
                                                       // we specify write only, it's faster
                                   D3D8T_CUSTOMVERTEX, //Our custom vertex specifier (coordinates & a colour)
                                   D3DPOOL_MANAGED,    //Tell DirectX to manage the memory of this resource
                                   &g_triangle);       //Pointer to our triangle, after this call
                                                       //It will point to a valid vertex buffer
    

    hr=g_triangle->Lock(0, //Offset, we want to start at the beginning
                   0, //SizeToLock, 0 means lock the whole thing
                   &vb_vertices, //If successful, this will point to the data in the VB
                   0);  //Flags, nothing special

    memcpy(vb_vertices, g_triangle_vertices, sizeof(g_triangle_vertices) );

    g_triangle->Unlock();

	initialized = true;
}

void CLatticeRelaxationD3DView::OnDraw(CDC* pDC)
{
	CLatticeRelaxationDoc* doc = GetDocument();
	
	CSingleLock csl(&(doc->m_CS));
	csl.Lock();

	RenderScene();

	csl.Unlock();
}

void CLatticeRelaxationD3DView::RenderScene() {
	if (atomMeshes.empty()) return;

    float scalingCoefficient = 3;

    if (direct3DDevice) {
        direct3DDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255,255,255), 1.0f, 0);
            
        direct3DDevice->BeginScene();

        D3DXMATRIX view_matrix;

		D3DXMatrixLookAtLH(&view_matrix,        
            &D3DXVECTOR3( cameraX + 10.0f, cameraY + 10.0f, cameraZ - 50.0f ),
            &D3DXVECTOR3( cameraX, cameraY, cameraZ ),
            &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
        
                    direct3DDevice->SetTransform(D3DTS_VIEW,&view_matrix);

        D3DXMATRIX matWorld;
        D3DXMATRIX matTranslation, matRotation, matRotationX, matRotationY;

        D3DXMatrixRotationY(&matRotationY,rotationY);
        D3DXMatrixRotationX(&matRotationX,rotationX);
        D3DXMatrixMultiply(&matRotation,&matRotationX,&matRotationY);

        std::map<Atom*, LPD3DXMESH>::iterator it;
         
		direct3DDevice->SetRenderState(D3DRS_LOCALVIEWER , TRUE);

        for (it = atomMeshes.begin(); it != atomMeshes.end(); it++) {
                    
            Atom* atom = it->first;
            LPD3DXMESH mesh = it->second;

            if (!atom->visible) continue;

			D3DXMatrixTranslation(&matTranslation, atom->r.x * scalingCoefficient, atom->r.y * scalingCoefficient, atom->r.z * scalingCoefficient);
            D3DXMatrixMultiply(&matWorld,&matTranslation,&matRotation);

            direct3DDevice->SetTransform(D3DTS_WORLD,&matWorld );

			if (atom == selectedAtom) {
				//direct3DDevice->SetRenderState(D3DRS_LIGHTING , FALSE);
				direct3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_COLORVALUE(0,1,0,0.8));
				
			} else {
				direct3DDevice->SetRenderState(D3DRS_LIGHTING , TRUE);
				direct3DDevice->SetRenderState(D3DRS_AMBIENT, 0);
			}
			
			mesh->DrawSubset(0);
                    
        }

		direct3DDevice->SetRenderState(D3DRS_LIGHTING , TRUE);
		direct3DDevice->SetRenderState(D3DRS_AMBIENT, 0);

					int i;

					D3DXMatrixTranslation(&matTranslation, - scalingCoefficient * 1.43, - scalingCoefficient * 1.43, - scalingCoefficient * 1.43);
                    D3DXMatrixMultiply(&matRotation,&matTranslation,&matRotation);

                    D3DXMatrixTranslation(&matTranslation, 0.0f, 0.0f, 0.0f);
                    D3DXMatrixMultiply(&matWorld,&matTranslation,&matRotation);
                    direct3DDevice->SetTransform(D3DTS_WORLD,&matWorld );
                    direct3DDevice->SetStreamSource(0,g_triangle,sizeof(my_vertex));
					for ( i = 1; i < 13; i++) {
						direct3DDevice->DrawPrimitive(D3DPT_LINELIST ,0, i);
					}

                    D3DXMatrixTranslation(&matTranslation, 0.0f, scalingCoefficient * 2.86, 0.0f);
                    D3DXMatrixMultiply(&matWorld,&matTranslation,&matRotation);
                    direct3DDevice->SetTransform(D3DTS_WORLD,&matWorld );
                    direct3DDevice->SetStreamSource(0,g_triangle,sizeof(my_vertex));
                    for ( i = 1; i < 13; i++) {
						direct3DDevice->DrawPrimitive(D3DPT_LINELIST ,0, i);
					}

                    D3DXMatrixTranslation(&matTranslation, -scalingCoefficient * 2.86, 0.0f, scalingCoefficient * 2.86);
                    D3DXMatrixMultiply(&matWorld,&matTranslation,&matRotation);
                    direct3DDevice->SetTransform(D3DTS_WORLD,&matWorld );
                    direct3DDevice->SetStreamSource(0,g_triangle,sizeof(my_vertex));
                    for ( i = 1; i < 13; i++) {
						direct3DDevice->DrawPrimitive(D3DPT_LINELIST ,0, i);
					}

                    D3DXMatrixTranslation(&matTranslation, -scalingCoefficient * 2.86, scalingCoefficient * 2.86, scalingCoefficient * 2.86);
                    D3DXMatrixMultiply(&matWorld,&matTranslation,&matRotation);
                    direct3DDevice->SetTransform(D3DTS_WORLD,&matWorld );
                    direct3DDevice->SetStreamSource(0,g_triangle,sizeof(my_vertex));
                    for ( i = 1; i < 13; i++) {
						direct3DDevice->DrawPrimitive(D3DPT_LINELIST ,0, i);
					}

                    D3DXMatrixTranslation(&matTranslation, scalingCoefficient * 2.86, 0.0f, 0.0f);
                    D3DXMatrixMultiply(&matWorld,&matTranslation,&matRotation);
                    direct3DDevice->SetTransform(D3DTS_WORLD,&matWorld );
                    direct3DDevice->SetStreamSource(0,g_triangle,sizeof(my_vertex));
                    for ( i = 1; i < 13; i++) {
						direct3DDevice->DrawPrimitive(D3DPT_LINELIST ,0, i);
					}

                    D3DXMatrixTranslation(&matTranslation, scalingCoefficient * 2.86, scalingCoefficient * 2.86, 0.0f);
                    D3DXMatrixMultiply(&matWorld,&matTranslation,&matRotation);
                    direct3DDevice->SetTransform(D3DTS_WORLD,&matWorld );
                    direct3DDevice->SetStreamSource(0,g_triangle,sizeof(my_vertex));
                    for ( i = 1; i < 13; i++) {
						direct3DDevice->DrawPrimitive(D3DPT_LINELIST ,0, i);
					}

                    D3DXMatrixTranslation(&matTranslation, scalingCoefficient * 2.86, 0.0f, -scalingCoefficient * 2.86);
                    D3DXMatrixMultiply(&matWorld,&matTranslation,&matRotation);
                    direct3DDevice->SetTransform(D3DTS_WORLD,&matWorld );
                    direct3DDevice->SetStreamSource(0,g_triangle,sizeof(my_vertex));
                    for ( i = 1; i < 13; i++) {
						direct3DDevice->DrawPrimitive(D3DPT_LINELIST ,0, i);
					}


        direct3DDevice->EndScene();

        direct3DDevice->Present(NULL, NULL, NULL, NULL);

	}

}


/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationD3DView diagnostics

#ifdef _DEBUG
void CLatticeRelaxationD3DView::AssertValid() const
{
	//CScrollView::AssertValid();
}

void CLatticeRelaxationD3DView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CLatticeRelaxationDoc* CLatticeRelaxationD3DView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLatticeRelaxationDoc)));
	return (CLatticeRelaxationDoc*)m_pDocument;
}
#endif //_DEBUG


void CLatticeRelaxationD3DView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CLatticeRelaxationDoc* doc = GetDocument();
	
	CSingleLock csl(&(doc->m_CS));
	csl.Lock();

	if (1 == lHint) {
		CLatticeRelaxationDoc* doc = GetDocument();
		Lattice* lattice = doc->modelingProject->activeLattice;
		std::deque<Atom*>& atoms = lattice->atoms;
		std::deque<Atom*>::iterator atomsIterator;
		
		std::map<Atom*, LPD3DXMESH>::iterator it;

		for (it = atomMeshes.begin(); it != atomMeshes.end(); it++) {
            LPD3DXMESH mesh = it->second;
			mesh->Release();
		}

		BuildAtomMeshes();
	}
	
	RenderScene();

	csl.Unlock();
}

void CLatticeRelaxationD3DView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    clickPoint = point;
	mouseDownAtom = getAtomFromPoint(point);
	
	CScrollView::OnLButtonDown(nFlags, point);
}

void CLatticeRelaxationD3DView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    clickPoint.x = -1;
    clickPoint.y = -1;

	mouseUpAtom = getAtomFromPoint(point);
	if (NULL != mouseUpAtom) {
		if (mouseUpAtom == mouseDownAtom) {
			selectedAtom = mouseUpAtom;
			RenderScene();
		}
		
	}
	
	mouseDownAtom = NULL;
	
	
	CScrollView::OnLButtonUp(nFlags, point);
}

void CLatticeRelaxationD3DView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    if (clickPoint.x != -1) {
        CPoint offset = point - clickPoint;
        if (nFlags & MK_CONTROL) {
            cameraX += ((float)offset.x) / 50;
            cameraY -= ((float)offset.y) / 50;
        } else {
            rotationY += ((float)offset.x) / 100;
            rotationX += ((float)offset.y) / 100;
        }
        clickPoint = point;

		CLatticeRelaxationDoc* doc = GetDocument();
		CSingleLock csl(&(doc->m_CS));
		csl.Lock();

        RenderScene();

		csl.Unlock();
    }
	
	CScrollView::OnMouseMove(nFlags, point);
}

void CLatticeRelaxationD3DView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	Atom* hitAtom = getAtomFromPoint(point);

	if (NULL != hitAtom) {

		editAtom(hitAtom);

	}
	
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CLatticeRelaxationD3DView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    switch (nChar) {
            case VK_LEFT:
                    cameraX += 0.5f;
                    break;
            case VK_RIGHT:
                    cameraX -= 0.5f;
                    break;
            case VK_UP:
                    cameraY -= 0.5f;
                    break;
            case VK_DOWN:
                    cameraY += 0.5f;
                    break;
            case VK_PRIOR:
                    cameraZ += 0.5f;
                    break;
            case VK_NEXT:
                    cameraZ -= 0.5f;
                    break;
    }

	CLatticeRelaxationDoc* doc = GetDocument();
	CSingleLock csl(&(doc->m_CS));
	csl.Lock();

    RenderScene();

	csl.Unlock();
		
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CLatticeRelaxationD3DView::BuildAtomMeshes()
{
	CLatticeRelaxationDoc* doc = GetDocument();
	Lattice* lattice = doc->modelingProject->activeLattice;
	std::deque<Atom*>& atoms = lattice->atoms;
	std::deque<Atom*>::iterator atomsIterator;
	
	atomMeshes.clear();

	for (atomsIterator = atoms.begin(); atomsIterator != atoms.end(); atomsIterator++) {
		Atom* atom = *atomsIterator;

		if (atom->visible) {

			AtomType* atomType = atom->atomType;

			LPD3DXMESH mesh;
            LPD3DXMESH atomMesh;
            D3DXCreateSphere(direct3DDevice, 1.0f, 30, 30, &mesh, NULL);

            mesh->CloneMeshFVF( 0, VertexFVF , direct3DDevice, &atomMesh);
			mesh->Release();

			IDirect3DVertexBuffer8* tempMeshVertexBuffer;
			atomMesh->GetVertexBuffer(&tempMeshVertexBuffer);
        
			int iNum = atomMesh->GetNumVertices();
			Vertex* pVertices = NULL;

			tempMeshVertexBuffer->Lock(0, 0, (byte**) &pVertices, 0);
			for (int i = 0; i < iNum; ++i) {
				pVertices[i].color = D3DCOLOR_RGBA( GetRValue(atomType->color), GetGValue(atomType->color), GetBValue(atomType->color), 255);
			}

			tempMeshVertexBuffer->Unlock();
			tempMeshVertexBuffer->Release();

            atomMeshes[atom] = atomMesh;

		}
	}
}

Atom* CLatticeRelaxationD3DView::getAtomFromPoint(CPoint point)
{
	float scalingCoefficient = 3;

	D3DVIEWPORT8 viewport;
    direct3DDevice->GetViewport(&viewport);

    /*
	int width = viewport.Width;
    int height = viewport.Height;
	*/

	CRect rect;
	GetClientRect(&rect);

	int width = rect.right;
	int height = rect.bottom;

    D3DXMATRIX projMatrix;
    direct3DDevice->GetTransform(D3DTS_PROJECTION, &projMatrix);

    D3DXVECTOR3 mouseVector;
    mouseVector.x = ( ( ( 2.0f * point.x ) / width ) - 1 ) / projMatrix._11;
    mouseVector.y = - ( ( ( 2.0f * (point.y ) ) / height ) - 1 ) / projMatrix._22;
    mouseVector.z = 1.0f;

    D3DXMATRIX viewMatrix;
    direct3DDevice->GetTransform(D3DTS_VIEW, &viewMatrix);

    D3DXVECTOR3 rayOrigin, rayDirection;

    D3DXMATRIX m;
    D3DXMatrixInverse(&m, NULL, &viewMatrix);

    rayDirection.x = mouseVector.x * m._11 + mouseVector.y * m._21 + mouseVector.z * m._31;
    rayDirection.y = mouseVector.x * m._12 + mouseVector.y * m._22 + mouseVector.z * m._32;
    rayDirection.z = mouseVector.x * m._13 + mouseVector.y * m._23 + mouseVector.z * m._33;
    rayOrigin.x = m._41;
    rayOrigin.y = m._42;
    rayOrigin.z = m._43;

    // haha

    D3DXMATRIX matWorld;
    D3DXMATRIX matRotation, matRotationX, matRotationY;

    D3DXMatrixRotationY(&matRotationY,rotationY);
    D3DXMatrixRotationX(&matRotationX,rotationX);

	std::map<Atom*, LPD3DXMESH>::iterator it;
      
	Atom *hitAtom = NULL;
	double minimumDistance = 0.0;

    for (it = atomMeshes.begin(); it != atomMeshes.end(); it++) {
            
        Atom *atom = it->first;
        LPD3DXMESH mesh = it->second;


        D3DXMATRIX matTranslation;
        D3DXMatrixTranslation(&matTranslation, atom->r.x * 3, atom->r.y * 3, atom->r.z * 3);

        D3DXMatrixMultiply(&matRotation,&matRotationX,&matRotationY);
        D3DXMatrixMultiply(&matWorld,&matTranslation,&matRotation);

        D3DXMATRIX matInverse;
        D3DXMatrixInverse(&matInverse, NULL, &matWorld);

        D3DXVECTOR3 rayObjOrigin, rayObjDirection;

        D3DXVec3TransformCoord(&rayObjOrigin, &rayOrigin, &matInverse);
        D3DXVec3TransformNormal(&rayObjDirection, &rayDirection, &matInverse);
        D3DXVec3Normalize(&rayObjDirection,&rayObjDirection);

        BOOL hasHit;
        float distanceToCollision;

        D3DXIntersect(mesh, &rayObjOrigin, &rayObjDirection, &hasHit, NULL, NULL, NULL,
                &distanceToCollision, NULL, NULL);

		if (hasHit) {
			if (0.0 == minimumDistance) {
				minimumDistance = distanceToCollision;
			}
			if (distanceToCollision <= minimumDistance) {
				minimumDistance = distanceToCollision;
				hitAtom = atom;
			}
        }

    }

	return hitAtom;
}

void CLatticeRelaxationD3DView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	
	selectedAtom = NULL;	
	RenderScene();

	CScrollView::OnRButtonUp(nFlags, point);
}

void CLatticeRelaxationD3DView::OnDeleteAtomButton() 
{
	// TODO: Add your command handler code here
	CLatticeRelaxationDoc* doc = GetDocument();
	std::deque<Atom*>& atoms = doc->modelingProject->activeLattice->atoms;
	std::deque<Atom*>::iterator atomsIt;
	for (atomsIt = atoms.begin(); atomsIt != atoms.end(); atomsIt++) {
		Atom* atom = *atomsIt;
		if (atom == selectedAtom) {
			atoms.erase(atomsIt);
			break;
		}
	}
	OnUpdate(this,1,NULL);
}

void CLatticeRelaxationD3DView::OnEditButtonAtom() 
{
	// TODO: Add your command handler code here
	editAtom(selectedAtom);
}

void CLatticeRelaxationD3DView::OnUpdateDeleteAtomButton(CCmdUI* pCmdUI) 
{
	if (NULL == selectedAtom) {
		pCmdUI->Enable(FALSE);
	} else {
		pCmdUI->Enable(TRUE);
	}
}

void CLatticeRelaxationD3DView::OnUpdateEditButtonAtom(CCmdUI* pCmdUI) 
{
	if (NULL == selectedAtom) {
		pCmdUI->Enable(FALSE);
	} else {
		pCmdUI->Enable(TRUE);
	}
}

void CLatticeRelaxationD3DView::editAtom(Atom *atom)
{
	AtomDialog atomDialog;
		
	atomDialog.m_positionX = atom->r.x;
	atomDialog.m_positionY = atom->r.y;
	atomDialog.m_positionZ = atom->r.z;

	atomDialog.m_forceX = atom->v.x;
	atomDialog.m_forceY = atom->v.y;
	atomDialog.m_forceZ = atom->v.z;

	atomDialog.m_Moveable = atom->moveable;
	atomDialog.m_Visible = atom->visible;

	atomDialog.atomType = atom->atomType;

	GetDocument()->modelingProject->populateAtomTypes();
	atomDialog.atomTypes = GetDocument()->modelingProject->atomTypes;

	if (IDOK == atomDialog.DoModal()) {
		atom->r.x = atomDialog.m_positionX;
		atom->r.y = atomDialog.m_positionY;
		atom->r.z = atomDialog.m_positionZ;

		atom->v.x = atomDialog.m_forceX;
		atom->v.y = atomDialog.m_forceY;
		atom->v.z = atomDialog.m_forceZ;

		atom->moveable = atomDialog.m_Moveable;
		atom->visible = atomDialog.m_Visible;

		atom->atomType = atomDialog.atomType;

		OnUpdate(this,1,NULL);

		if (NULL != selectedAtom) {
			if (!(selectedAtom->visible)) {
				selectedAtom = NULL;
			}
		}
	}
}

void CLatticeRelaxationD3DView::OnMigrateAtomButton() 
{
	// TODO: Add your command handler code here
	CLatticeRelaxationDoc* doc = GetDocument();

	if ((NULL != doc->modelingProject->migratingAtom) && (doc->modelingProject->migratingAtom != selectedAtom)) {
		if (!(IDYES == AfxMessageBox("You've already selected an atom to migrate. Are you sure you want to migrate this one?",MB_YESNO))) {
			return;
		}
	}
	
	MigrateAtomDialog migrateAtomDialog;
	if (doc->modelingProject->migratingAtom == selectedAtom) {
		migrateAtomDialog.m_x = doc->modelingProject->migratingToPoint.x / 2.86;
		migrateAtomDialog.m_y = doc->modelingProject->migratingToPoint.y / 2.86;
		migrateAtomDialog.m_z = doc->modelingProject->migratingToPoint.z / 2.86;
		migrateAtomDialog.m_migrationSteps = doc->modelingProject->migratingSteps;
	}

	if (IDOK == migrateAtomDialog.DoModal()) {
		doc->modelingProject->migratingToPoint.x = migrateAtomDialog.m_x * 2.86;
		doc->modelingProject->migratingToPoint.y = migrateAtomDialog.m_y * 2.86;
		doc->modelingProject->migratingToPoint.z = migrateAtomDialog.m_z * 2.86;
		doc->modelingProject->migratingSteps = migrateAtomDialog.m_migrationSteps;
		doc->modelingProject->migratingAtom = selectedAtom;
	}
}

void CLatticeRelaxationD3DView::OnUpdateMigrateAtomButton(CCmdUI* pCmdUI) 
{
	if (NULL == selectedAtom) {
		pCmdUI->Enable(FALSE);
	} else {
		pCmdUI->Enable(TRUE);
	}	
}

void CLatticeRelaxationD3DView::OnUpdateIndicatorAtomX(CCmdUI *pCmdUI)
{
	if (NULL != selectedAtom) {
		CString str;
		str.Format(TEXT(" %f "),selectedAtom->r.x / 2.86);
		pCmdUI->SetText(str);
	} else {
		pCmdUI->SetText("   ");
	}
	
}

void CLatticeRelaxationD3DView::OnUpdateIndicatorAtomY(CCmdUI *pCmdUI)
{
	if (NULL != selectedAtom) {
		CString str;
		str.Format(TEXT(" %f "),selectedAtom->r.y / 2.86);
		pCmdUI->SetText(str);
	} else {
		pCmdUI->SetText("   ");
	}
	
}

void CLatticeRelaxationD3DView::OnUpdateIndicatorAtomZ(CCmdUI *pCmdUI)
{
	if (NULL != selectedAtom) {
		CString str;
		str.Format(TEXT(" %f "),selectedAtom->r.z / 2.86);
		pCmdUI->SetText(str);
	} else {
		pCmdUI->SetText("   ");
	}
	
}

void CLatticeRelaxationD3DView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (initialized) {
		Resize(cx, cy);	
	}

}
