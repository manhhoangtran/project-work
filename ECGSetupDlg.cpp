// ECGSetup.cpp : implementation file
//

#include "stdafx.h"
#include "monitor.h"
#include "ECGSetupDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CECGSetupDlg dialog


CECGSetupDlg::CECGSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CECGSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CECGSetupDlg)
	//}}AFX_DATA_INIT
}

void CECGSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CECGSetupDlg)
	DDX_Control(pDX, IDC_ECG_CMD, m_cboECGCmd);
	DDX_Control(pDX, IDC_ECG_MODE, m_cboECGMode);
	DDX_Control(pDX, IDC_ECG_GAIN, m_cboECGGain);
    DDX_Control(pDX, IDC_RESP_GAIN, m_cboRESPGain);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CECGSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CECGSetupDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CECGSetupDlg message handlers

BOOL CECGSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_cboECGMode.SetCurSel(((CMainFrame *)GetParent())->m_ECGMode);
    
    m_cboECGGain.AddString("x0.25");
    m_cboECGGain.AddString("x0.5");
    m_cboECGGain.AddString("x1");
    m_cboECGGain.AddString("x2");
    m_cboECGGain.SetCurSel(((CMainFrame *)GetParent())->m_ECGGain);

    m_cboRESPGain.AddString("x0.25");
    m_cboRESPGain.AddString("x0.5");
    m_cboRESPGain.AddString("x1");
    m_cboRESPGain.AddString("x2");
    m_cboRESPGain.SetCurSel(((CMainFrame *)GetParent())->m_RESPGain);

    m_cboECGCmd.SetCurSel(((CMainFrame *)GetParent())->m_ECGCmd);

    UpdateData(false);
    
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CECGSetupDlg::OnOK() 
{
	// TODO: Add extra validation here
    UpdateData(true);
    ((CMainFrame *)GetParent())->m_ECGMode = m_cboECGMode.GetCurSel();
    ((CMainFrame *)GetParent())->m_ECGGain = m_cboECGGain.GetCurSel();
    ((CMainFrame *)GetParent())->m_RESPGain = m_cboRESPGain.GetCurSel();
    ((CMainFrame *)GetParent())->m_ECGCmd = m_cboECGCmd.GetCurSel();
    
    CDialog::OnOK();
}
