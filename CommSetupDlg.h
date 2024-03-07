#if !defined(AFX_COMSETUP_H__A3020EB2_A3C9_442D_BCE8_9C332F7C0227__INCLUDED_)
#define AFX_COMSETUP_H__A3020EB2_A3C9_442D_BCE8_9C332F7C0227__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommSetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComSetupDlg dialog

class CComSetupDlg : public CDialog
{
// Construction
public:
    CComSetupDlg(CWnd* pParent = NULL);   // standard constructor
        
// Dialog Data
    //{{AFX_DATA(CComSetupDlg)
    enum { IDD = IDD_COMM_SETUP };
    CComboBox   m_cboStopBit;
    CComboBox   m_cboParityBit;
    CComboBox   m_cboDataBit;
    CComboBox   m_cboBaudRate;
    CComboBox   m_cboPort;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CComSetupDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CComSetupDlg)
    afx_msg void OnDefault();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    void SaveConfig2Registry(void);    
    void SaveConfig2INIFile(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMSETUP_H__A3020EB2_A3C9_442D_BCE8_9C332F7C0227__INCLUDED_)
