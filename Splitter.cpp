// Splitter.cpp : implementation file
//

#include "stdafx.h"
#include "monitor.h"
#include "Splitter.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitter

CSplitter::CSplitter()
{
    m_cySplitterGap = 3;
    m_IsCreated = false;
}

CSplitter::~CSplitter()
{
}


BEGIN_MESSAGE_MAP(CSplitter, CSplitterWnd)
    //{{AFX_MSG_MAP(CSplitter)
    ON_WM_LBUTTONDOWN()
    ON_WM_SETCURSOR()
    ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSplitter message handlers

void CSplitter::OnLButtonDown(UINT nFlags, CPoint point) 
{
    // TODO: Add your message handler code here and/or call default
    
    CWnd::OnLButtonDown(nFlags, point);
}

BOOL CSplitter::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
    // TODO: Add your message handler code here and/or call default
    
    return CSplitterWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CSplitter::OnMouseMove(UINT nFlags, CPoint point) 
{
    // TODO: Add your message handler code here and/or call default
    
    CWnd::OnMouseMove(nFlags, point);
}

#if 0
void CSplitter::OnDrawSplitter(CDC *pDC, ESplitType nType, const CRect &rect)
{
    // TODO: Add your message handler code here and/or call default
    if(pDC==NULL) 
    { 
        RedrawWindow(rect,NULL,RDW_INVALIDATE|RDW_NOCHILDREN);
        return;
    } 

    ASSERT_VALID(pDC);

    CRect rc = rect;
    switch(nType) 
    { 
    case splitBorder:
        //TRACE("Draw splitBorder...\n");
        TRACE("rc.height=%d\n", rc.Height());
        //重画分割窗口边界,使之为红色 
        pDC->Draw3dRect(rc,RGB(255,0,0),RGB(255,0,0));
        rc.InflateRect(-1,-1); 
        pDC->Draw3dRect(rc,RGB(255,0,0),RGB(255,0,0)); 
        return; 
    case splitBox:
        TRACE("Draw splitBox...\n");
        return; 
    case splitBar:
        TRACE("Draw splitBar...\n");
        //重画分割条，使之为绿色 
        //pDC->FillSolidRect(rc,RGB(0,255,0));
        //rc.InflateRect(-1,-1); 
        //pDC->Draw3dRect(rc,RGB(255,0,0),RGB(0,0,255)); 
        return; 
    default: 
        ASSERT(FALSE); 
    } 
    //pDC->FillSolidRect(rc,RGB(0,0,0));  
}
#endif


void CSplitter::OnSize(UINT nType, int cx, int cy) 
{
    CSplitterWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
    if (m_IsCreated)
    {
        CRect rc1, rc2;
        int totalHeight, rowHeight;
        int i;
        
        //TRACE("nType=%d, cx=%d, cy=%d\n", nType, cx, cy);
        GetClientRect(&rc1);
        //TRACE("rc1.Height=%d\n", rc1.Height());
        if (((CMainFrame *)GetParent())->m_wndToolBar.IsWindowVisible() &&
            !((CMainFrame *)GetParent())->m_wndToolBar.IsFloating())
        {
            ((CMainFrame *)GetParent())->m_wndToolBar.GetClientRect(&rc2);
            //TRACE("rc2.Height=%d\n", rc2.Height());
            totalHeight = rc1.Height() - rc2.Height();
        }
        else
        {
            totalHeight = rc1.Height() - m_cySplitterGap * CHANNEL_NUM;
        }
        //TRACE("totalHeight=%d\n", totalHeight);
        
        if (totalHeight > 210)
        {
            for (i = 0; i < CHANNEL_NUM; i++)
            {
                rowHeight = totalHeight / (CHANNEL_NUM - i);
                totalHeight -= rowHeight;
                SetRowInfo(i, rowHeight, 10);
                //TRACE("rowHeight=%d\n", rowHeight);
            }
            RecalcLayout();
        }
    }
}
