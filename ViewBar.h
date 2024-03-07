#if !defined(AFX_VIEWBAR_H__3E347383_A9AA_412C_B58C_B167974EC396__INCLUDED_)
#define AFX_VIEWBAR_H__3E347383_A9AA_412C_B58C_B167974EC396__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewBar dialog

class CViewBar : public CDialogBar
{
// Construction
public:
    CViewBar(CWnd* pParent = NULL);   // standard constructor
        
// Dialog Data
    //{{AFX_DATA(CViewBar)
	enum { IDD = IDD_VIEWBAR };
	//}}AFX_DATA

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CViewBar)
    protected:
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CViewBar)
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    //}}AFX_MSG
    afx_msg LRESULT OnInitDialog(UINT wParam, LONG lParam);
    DECLARE_MESSAGE_MAP()
private:
    CBrush m_Brush;
    CFont m_FontBig;
    CFont m_FontNormal;
    CFont m_FontSmall;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWBAR_H__3E347383_A9AA_412C_B58C_B167974EC396__INCLUDED_)
