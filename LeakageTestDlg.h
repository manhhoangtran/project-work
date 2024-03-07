#if !defined(AFX_NIBPLEAKAGEDLG_H__5BF960A8_49AD_40B5_B0A6_9E0B3E5A9F83__INCLUDED_)
#define AFX_NIBPLEAKAGEDLG_H__5BF960A8_49AD_40B5_B0A6_9E0B3E5A9F83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NIBPLeakageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLeakageTestDlg dialog

class CLeakageTestDlg : public CDialog
{
// Construction
public:
    BOOL m_IsOpen;
    BOOL m_IsLeakageTest;
	CLeakageTestDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLeakageTestDlg)
	enum { IDD = IDD_LEAKAGE_TEST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeakageTestDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLeakageTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpinLeakagePreset(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLeakageTest();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NIBPLEAKAGEDLG_H__5BF960A8_49AD_40B5_B0A6_9E0B3E5A9F83__INCLUDED_)
