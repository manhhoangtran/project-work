// monitorView.h : interface of the CMonitorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONITORVIEW_H__E09B96AA_C6C3_483F_9801_A2C42F64AC70__INCLUDED_)
#define AFX_MONITORVIEW_H__E09B96AA_C6C3_483F_9801_A2C42F64AC70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMonitorView : public CView
{
protected: // create from serialization only
    CMonitorView();
    DECLARE_DYNCREATE(CMonitorView)

// Attributes
public:
    CMonitorDoc* GetDocument();

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMonitorView)
    public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
    protected:
    virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CMonitorView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    
// Generated message map functions
protected:
    //{{AFX_MSG(CMonitorView)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in monitorView.cpp
inline CMonitorDoc* CMonitorView::GetDocument()
   { return (CMonitorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITORVIEW_H__E09B96AA_C6C3_483F_9801_A2C42F64AC70__INCLUDED_)
