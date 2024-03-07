#if !defined(AFX_ECGSETUP_H__73635B1B_8143_4558_A840_9ED16ECA561E__INCLUDED_)
#define AFX_ECGSETUP_H__73635B1B_8143_4558_A840_9ED16ECA561E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ECGSetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CECGSetupDlg dialog

class CECGSetupDlg : public CDialog
{
// Construction
public:
	CECGSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CECGSetupDlg)
	enum { IDD = IDD_ECG_SETUP };
	CComboBox	m_cboECGCmd;
    CComboBox	m_cboECGMode;
    CComboBox	m_cboECGGain;
    CComboBox	m_cboRESPGain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CECGSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CECGSetupDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECGSETUP_H__73635B1B_8143_4558_A840_9ED16ECA561E__INCLUDED_)
