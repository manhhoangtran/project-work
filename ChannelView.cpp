// ChannelView.cpp : implementation file
//

#include "stdafx.h"
#include "monitor.h"
#include "ChannelView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChannelView

IMPLEMENT_DYNCREATE(CChannelView, CView)

CChannelView::CChannelView()
{
}

CChannelView::~CChannelView()
{
}


BEGIN_MESSAGE_MAP(CChannelView, CView)
    //{{AFX_MSG_MAP(CChannelView)
    ON_WM_ERASEBKGND()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChannelView drawing

void CChannelView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
    // TODO: add draw code here
}

void CChannelView::DrawTitle()
{
    CClientDC dc(this); 
    CFont font;
    CFont *pOldFont;
    CRect rcTitle = CRect(5, 1, 60, 12);
    
    dc.SetBkColor(RGB(0, 0, 0));
    dc.SetTextColor(RGB(255, 255, 255));
    font.CreatePointFont(80, "Verdana");
    //font.CreatePointFont(80, "Arial Black");
    //font.CreatePointFont(80, "MS Serif");
    //font.CreatePointFont(80, "新宋体");
    pOldFont=dc.SelectObject(&font);
    dc.DrawText(m_Title, rcTitle, DT_VCENTER);
    //dc.DrawFocusRect(&rcTitle);
    dc.SelectObject(pOldFont);
    font.DeleteObject();
}

void CChannelView::DrawCurve()
{
    CClientDC dc(this);
    CPoint ptStart, ptEnd;
    CPoint ptOrigin;
    CPen pen(PS_SOLID, 1, m_ChannelColor);
    CPen *pOldPen;
    CBrush eraseBrush(RGB(0, 0, 0));
    CRect rcChannel;
    CRect rcErase;
    double xScale;
    double yScale;
    
    GetClientRect(&rcChannel);
    rcChannel.top += 12;    // 去掉m_Title的高度
    rcChannel.bottom -= 12;

    if (m_ChannelType == ECG) {
        xScale = ECG_XSCALE;
        yScale = (double)rcChannel.Height() / ECG_WAVE_RANGE;
        ptOrigin.x = rcChannel.left;
        ptOrigin.y = rcChannel.top + rcChannel.Height() / 2;
    }
    else if (m_ChannelType == SPO2) {
        xScale = SPO2_XSCALE;
        yScale = (double)rcChannel.Height() / SPO2_WAVE_RANGE;
        ptOrigin.x = rcChannel.left;
        ptOrigin.y = rcChannel.top + rcChannel.Height() - 2;
    }
    else if (m_ChannelType == RESP) {
        xScale = RESP_XSCALE;
        yScale = (double)rcChannel.Height() / RESP_WAVE_RANGE;
        ptOrigin.x = rcChannel.left;
        ptOrigin.y = rcChannel.top + rcChannel.Height() / 2;
    }

    if (m_CurPos >= (int)(rcChannel.Width() / xScale))
        m_CurPos = 0;

    //画擦除矩形
    if (m_CurPos == 0)
        rcErase.left = ptOrigin.x;
    else
        rcErase.left = ptOrigin.x + (int)(m_CurPos * xScale) + 1;
    rcErase.top = rcChannel.top - 1;
    rcErase.right = rcErase.left + (int)xScale + 3;
    rcErase.bottom = rcChannel.bottom + 1;
    dc.FillRect(&rcErase, &eraseBrush);
    
    //设置当前曲线的起点和终点坐标
    ptStart.x = ptOrigin.x + (int)(m_CurPos * xScale);
    ptStart.y = ptOrigin.y - (int)((m_OldValue - m_BaseValue) * yScale);
    if (ptStart.y < rcChannel.top) {
        ptStart.y = rcChannel.top;
    }
    else if (ptStart.y > rcChannel.bottom) {
        ptStart.y = rcChannel.bottom;
    }
    ptEnd.x = ptOrigin.x + (int)((m_CurPos + 1) * xScale);
    ptEnd.y = ptOrigin.y - (int)((m_CurValue - m_BaseValue) * yScale);
    if (ptEnd.y < rcChannel.top) {
        ptEnd.y = rcChannel.top;
    }
    else if (ptEnd.y > rcChannel.bottom) {
        ptEnd.y = rcChannel.bottom;
    }
    //TRACE("m_CurPos=%d\n", m_CurPos);
    //TRACE("ptStart.x=%d\n", ptStart.x);
    //TRACE("ptEnd.x=%d\n", ptEnd.x);
    
    //画波形曲线
    pOldPen = dc.SelectObject(&pen);
    dc.MoveTo(ptStart);
    dc.LineTo(ptEnd);
    dc.SelectObject(pOldPen);
}

void CChannelView::DrawRPulse()
{
    CClientDC dc(this);
    CPoint ptStart, ptEnd;
    CPoint ptOrigin;
    CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
    CPen *pOldPen;
    CRect rcChannel;
    double xScale;

    if (m_ChannelType == ECG) {
        xScale = ECG_XSCALE;
    }
    else if (m_ChannelType == SPO2) {
        xScale = SPO2_XSCALE;
    }
    else {
        xScale = RESP_XSCALE;
    }

    GetClientRect(&rcChannel);
    
    ptOrigin.x = rcChannel.left;
    ptOrigin.y = rcChannel.top + rcChannel.Height() / 2;

    //设置RPulse标记线的坐标
    ptStart.x = ptOrigin.x + (int)(m_CurPos * xScale);
    ptStart.y = ptOrigin.y - 50;
    ptEnd.x = ptStart.x;
    ptEnd.y = ptOrigin.y + 50;
    //TRACE("m_CurPos=%d\n", m_CurPos);
    //TRACE("ptStart.x=%d\n", ptStart.x);
    //TRACE("ptEnd.x=%d\n", ptEnd.x);
    
    //画RPulse标记线
    pOldPen = dc.SelectObject(&pen);
    dc.MoveTo(ptStart);
    dc.LineTo(ptEnd);
    dc.SelectObject(pOldPen);
}

void CChannelView::RefreshChannel()
{
    CClientDC dc(this);
    CRect rcChannel;
    
    //清除当前channel的图像内容
    GetClientRect(&rcChannel);
    dc.FillRect(&rcChannel, &CBrush(RGB(0, 0, 0)));
    m_CurPos = 0;

    DrawTitle();
}

/////////////////////////////////////////////////////////////////////////////
// CChannelView diagnostics

#ifdef _DEBUG
void CChannelView::AssertValid() const
{
    CView::AssertValid();
}

void CChannelView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChannelView message handlers

BOOL CChannelView::OnEraseBkgnd(CDC* pDC) 
{
    // TODO: Add your message handler code here and/or call default
    //设置brush为希望的背景颜色
    CBrush backBrush(RGB(0, 0, 0));
    
    //保存旧的brush
    CBrush* pOldBrush = pDC->SelectObject(&backBrush);
    CRect rect;
    pDC->GetClipBox(&rect);
    
    //画需要的区域
    pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
    pDC->SelectObject(pOldBrush);
    
    DrawTitle();
    
    return true;    
    //return CView::OnEraseBkgnd(pDC);
}






















