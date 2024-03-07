#if !defined(AFX_NIBPSETUPDLG_H__D3103E65_71A4_460F_86D4_B0C3131A0D57__INCLUDED_)
#define AFX_NIBPSETUPDLG_H__D3103E65_71A4_460F_86D4_B0C3131A0D57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NIBPSetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNIBPSetupDlg dialog

class CNIBPSetupDlg : public CDialog
{
// Construction
public:
	CNIBPSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNIBPSetupDlg)
	enum { IDD = IDD_NIBP_SETUP };
    CComboBox	m_cboNIBPMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNIBPSetupDlg)
	protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNIBPSetupDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDeltaposSpinPreset(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NIBPSETUPDLG_H__D3103E65_71A4_460F_86D4_B0C3131A0D57__INCLUDED_)
