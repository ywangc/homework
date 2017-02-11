// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// ImageDisplayerView.cpp : implementation of the CImageDisplayerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImageDisplayer.h"
#endif

#include "ImageDisplayerDoc.h"
#include "ImageDisplayerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageDisplayerView

IMPLEMENT_DYNCREATE(CImageDisplayerView, CView)

BEGIN_MESSAGE_MAP(CImageDisplayerView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageDisplayerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_Open, &CImageDisplayerView::OnButtonOpen)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_Open, &CImageDisplayerView::OnUpdateButtonOpen)
END_MESSAGE_MAP()

// CImageDisplayerView construction/destruction

CImageDisplayerView::CImageDisplayerView()
{
	// TODO: add construction code here

}

CImageDisplayerView::~CImageDisplayerView()
{
}

BOOL CImageDisplayerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CImageDisplayerView drawing

void CImageDisplayerView::OnDraw(CDC* pDC)
{
	CImageDisplayerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	if(!image.IsNull())
	{
		image.Draw(pDC->GetSafeHdc(), 0, 0);
	}
}


// CImageDisplayerView printing


void CImageDisplayerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageDisplayerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImageDisplayerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImageDisplayerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CImageDisplayerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageDisplayerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageDisplayerView diagnostics

#ifdef _DEBUG
void CImageDisplayerView::AssertValid() const
{
	CView::AssertValid();
}

void CImageDisplayerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageDisplayerDoc* CImageDisplayerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageDisplayerDoc)));
	return (CImageDisplayerDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageDisplayerView message handlers


void CImageDisplayerView::OnButtonOpen()
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE, _T(".bmp"), _T("*.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("位图文件（*.bmp）|*.bmp|JPGE文件（*.jpg)|*.jpg||"));
	if(dlg.DoModal() == IDOK)
	{
		if(!image.IsNull())
		{
			image.Destroy();
		}
		image.Load(dlg.GetPathName());
		Invalidate();
	}
}


void CImageDisplayerView::OnUpdateButtonOpen(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}
