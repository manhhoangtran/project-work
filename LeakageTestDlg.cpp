// LeakageTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "monitor.h"
#include "LeakageTestDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeakageTestDlg dialog


CLeakageTestDlg::CLeakageTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLeakageTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLeakageTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLeakageTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLeakageTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLeakageTestDlg, CDialog)
	//{{AFX_MSG_MAP(CLeakageTestDlg)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_LEAKAGE_PRESET, OnDeltaposSpinLeakagePreset)
	ON_BN_CLICKED(ID_LEAKAGE_TEST, OnLeakageTest)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeakageTestDlg message handlers

BOOL CLeakageTestDlg::OnInitDialog() 
{
    CString str;

    CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_IsOpen = TRUE;
    m_IsLeakageTest = FALSE;
    str.Format("%d", 250);
    SetDlgItemText(IDC_LEAKAGE_PRESET, str);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLeakageTestDlg::OnDeltaposSpinLeakagePreset(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    // TODO: Add your control notification handler code here
    CString str;
    INT preset;

    GetDlgItemText(IDC_LEAKAGE_PRESET, str);
    preset = atoi(str);
    preset -= pNMUpDown->iDelta * 10;
    if (preset > 300)    // 最大500ms的偏移量
    {
        preset = 300;
    }
    else if (preset < 40)
    {
        preset = 40;
    }
    str.Format("%d", preset);
    SetDlgItemText(IDC_LEAKAGE_PRESET, str);
    
    *pResult = 0;
}

void CLeakageTestDlg::OnLeakageTest() 
{
	// TODO: Add your control notification handler code here
    CString str;
    UCHAR preset;
    UCHAR cmd[6];
    
    m_IsLeakageTest = !m_IsLeakageTest;
    if (m_IsLeakageTest) {
        GetDlgItemText(IDC_LEAKAGE_PRESET, str);
        preset = atoi(str) / 2;
        cmd[0] = 0x55;
        cmd[1] = 0xaa;
        cmd[2] = 0x04;
        cmd[3] = 0x10;
        cmd[4] = preset;
        cmd[5] = CMainFrame::CalcSum(cmd, 6);
        ((CMainFrame *)GetParent())->m_Comm.Write(cmd, 6);
    }
    else {
        cmd[0] = 0x55;
        cmd[1] = 0xaa;
        cmd[2] = 0x04;
        cmd[3] = 0x10;
        cmd[4] = 0x00;
        cmd[5] = CMainFrame::CalcSum(cmd, 6);
        ((CMainFrame *)GetParent())->m_Comm.Write(cmd, 6);
    }
}

void CLeakageTestDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
    UCHAR cmd[6];

    m_IsOpen = false;
    if (m_IsLeakageTest) {
        m_IsLeakageTest = FALSE;
        cmd[0] = 0x55;
        cmd[1] = 0xaa;
        cmd[2] = 0x04;
        cmd[3] = 0x10;
        cmd[4] = 0x00;
        cmd[5] = CMainFrame::CalcSum(cmd, 6);
        ((CMainFrame *)GetParent())->m_Comm.Write(cmd, 6);
    }

	CDialog::OnClose();
}

BOOL CLeakageTestDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
        return TRUE;
    }
    
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) {
        OnClose();
    }
    
	return CDialog::PreTranslateMessage(pMsg);
}
