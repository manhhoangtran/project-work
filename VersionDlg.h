#if !defined(AFX_VERSIONDLG_H__07B0A1B6_33AF_43C9_AAF5_926E13992371__INCLUDED_)
#define AFX_VERSIONDLG_H__07B0A1B6_33AF_43C9_AAF5_926E13992371__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VersionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVersionDlg dialog

class CVersionDlg : public CDialog
{
// Construction
public:
	CVersionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVersionDlg)
	enum { IDD = IDD_VERSION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVersionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVersionDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VERSIONDLG_H__07B0A1B6_33AF_43C9_AAF5_926E13992371__INCLUDED_)
