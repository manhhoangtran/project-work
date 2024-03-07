#if !defined(AFX_STATICPRESSDLG_H__AD86FAC9_3869_4758_8D99_03C7F9823C5D__INCLUDED_)
#define AFX_STATICPRESSDLG_H__AD86FAC9_3869_4758_8D99_03C7F9823C5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticPressDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticPressDlg dialog

class CStaticPressDlg : public CDialog
{
// Construction
public:
	CStaticPressDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    BOOL m_IsOpen;
	//{{AFX_DATA(CStaticPressDlg)
	enum { IDD = IDD_STATIC_PRESS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticPressDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStaticPressDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICPRESSDLG_H__AD86FAC9_3869_4758_8D99_03C7F9823C5D__INCLUDED_)
