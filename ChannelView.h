#if !defined(AFX_CHANNELVIEW_H__5E07C6A6_E7EE_469F_A919_E6B3376719F5__INCLUDED_)
#define AFX_CHANNELVIEW_H__5E07C6A6_E7EE_469F_A919_E6B3376719F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChannelView.h : header file
//

typedef enum {
    ECG = 0,
    SPO2,
    RESP
}ChannelType;

/////////////////////////////////////////////////////////////////////////////
// CChannelView view

class CChannelView : public CView
{
public:
    CChannelView();           // protected constructor used by dynamic creation
    DECLARE_DYNCREATE(CChannelView)

// Attributes
public:
    ChannelType m_ChannelType;
    COLORREF m_ChannelColor;
    CString m_Title;
    unsigned char m_BaseValue;
	unsigned char m_OldValue;
    unsigned char m_CurValue;
    int m_CurPos;
    double m_XScale;
    double m_YScale;
    
// Operations
public:
    void DrawTitle();
    void DrawCurve();
    void DrawRPulse();
    void RefreshChannel();
    
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CChannelView)
    protected:
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    //}}AFX_VIRTUAL

// Implementation
protected:
    virtual ~CChannelView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
protected:
    //{{AFX_MSG(CChannelView)
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANNELVIEW_H__5E07C6A6_E7EE_469F_A919_E6B3376719F5__INCLUDED_)
