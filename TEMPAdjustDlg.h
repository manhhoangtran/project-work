#if !defined(AFX_TEMPADJUSTDLG_H__C7E906C6_F4A2_4372_BAF8_130D236BDE7B__INCLUDED_)
#define AFX_TEMPADJUSTDLG_H__C7E906C6_F4A2_4372_BAF8_130D236BDE7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TEMPAdjustDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTEMPAdjustDlg dialog

class CTEMPAdjustDlg : public CDialog
{
// Construction
public:
	int m_TempBias1;
    int m_TempBias2;
	CTEMPAdjustDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    BOOL m_IsOpen;
	//{{AFX_DATA(CTEMPAdjustDlg)
	enum { IDD = IDD_TEMP_ADJUST };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTEMPAdjustDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTEMPAdjustDlg)
	afx_msg void OnDeltaposSpinBias1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDeltaposSpinBias2(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnAdjustTemp1();
    afx_msg void OnAdjustTemp2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPADJUSTDLG_H__C7E906C6_F4A2_4372_BAF8_130D236BDE7B__INCLUDED_)
