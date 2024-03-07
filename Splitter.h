#if !defined(AFX_ECGSPLITTER_H__68125DDB_CB71_4FAF_A215_E09E063D87AE__INCLUDED_)
#define AFX_ECGSPLITTER_H__68125DDB_CB71_4FAF_A215_E09E063D87AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Splitter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSplitter window

class CSplitter : public CSplitterWnd
{
// Construction
public:
    CSplitter();

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSplitter)
    //}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_IsCreated;
    virtual ~CSplitter();

    // Generated message map functions
protected:
    //{{AFX_MSG(CSplitter)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //afx_msg void OnDrawSplitter(CDC *pDC, ESplitType nType, const CRect &rect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECGSPLITTER_H__68125DDB_CB71_4FAF_A215_E09E063D87AE__INCLUDED_)
