#if !defined(AFX_NIBPADJUSTDLG_H__E16B0333_B877_4767_8427_B837E177DF74__INCLUDED_)
#define AFX_NIBPADJUSTDLG_H__E16B0333_B877_4767_8427_B837E177DF74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NIBPAdjustDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNIBPAdjustDlg dialog

class CNIBPAdjustDlg : public CDialog
{
// Construction
public:
    int m_BiasPress;
	CNIBPAdjustDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    BOOL m_IsOpen;
	//{{AFX_DATA(CNIBPAdjustDlg)
	enum { IDD = IDD_NIBP_ADJUST };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNIBPAdjustDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNIBPAdjustDlg)
	afx_msg void OnAdjust();
	afx_msg void OnDeltaposSpinBias(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NIBPADJUSTDLG_H__E16B0333_B877_4767_8427_B837E177DF74__INCLUDED_)
