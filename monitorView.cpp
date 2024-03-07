// monitorView.cpp : implementation of the CMonitorView class
//

#include "stdafx.h"
#include "monitor.h"

#include "monitorDoc.h"
#include "monitorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitorView

IMPLEMENT_DYNCREATE(CMonitorView, CView)

BEGIN_MESSAGE_MAP(CMonitorView, CView)
    //{{AFX_MSG_MAP(CMonitorView)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitorView construction/destruction

CMonitorView::CMonitorView()
{
    // TODO: add construction code here

}

CMonitorView::~CMonitorView()
{
}

BOOL CMonitorView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs
    
    return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMonitorView drawing

void CMonitorView::OnDraw(CDC* pDC)
{
    CMonitorDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    // TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMonitorView diagnostics

#ifdef _DEBUG
void CMonitorView::AssertValid() const
{
    CView::AssertValid();
}

void CMonitorView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CMonitorDoc* CMonitorView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMonitorDoc)));
    return (CMonitorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMonitorView message handlers

BOOL CMonitorView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
    // TODO: Add your specialized code here and/or call the base class
    
    return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CMonitorView::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
    // TODO: Add your specialized code here and/or call the base class
    
    CView::CalcWindowRect(lpClientRect, nAdjustType);
}
