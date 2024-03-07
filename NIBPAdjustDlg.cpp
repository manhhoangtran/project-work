// NIBPAdjustDlg.cpp : implementation file
//

#include "stdafx.h"
#include "monitor.h"
#include "NIBPAdjustDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNIBPAdjustDlg dialog


CNIBPAdjustDlg::CNIBPAdjustDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNIBPAdjustDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNIBPAdjustDlg)
	//}}AFX_DATA_INIT
}


BEGIN_MESSAGE_MAP(CNIBPAdjustDlg, CDialog)
	//{{AFX_MSG_MAP(CNIBPAdjustDlg)
	ON_BN_CLICKED(ID_ADJUST, OnAdjust)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BIAS, OnDeltaposSpinBias)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNIBPAdjustDlg message handlers

void CNIBPAdjustDlg::OnAdjust() 
{
	// TODO: Add your control notification handler code here
    unsigned char cmd[6];
    CString str;
    
    cmd[0] = 0x55;
    cmd[1] = 0xaa;
    cmd[2] = 0x04;
    cmd[3] = 0x0c;
    cmd[4] = m_BiasPress;
    cmd[5] = CMainFrame::CalcSum(cmd, 6);
    ((CMainFrame *)GetParent())->m_Comm.Write(cmd, 6);
    m_BiasPress = 0;
    str.Format("%d", m_BiasPress);
    SetDlgItemText(IDC_BIAS_PRESS, str);
}

void CNIBPAdjustDlg::OnDeltaposSpinBias(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
    CString str;
    
    m_BiasPress -= pNMUpDown->iDelta;
    if (m_BiasPress > 50)    // 最大500ms的偏移量
    {
        m_BiasPress = 50;
    }
    else if (m_BiasPress < -50)
    {
        m_BiasPress = -50;
    }
    str.Format("%d", m_BiasPress);
    SetDlgItemText(IDC_BIAS_PRESS, str);
	
	*pResult = 0;
}

BOOL CNIBPAdjustDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    CString str;
    
    m_BiasPress = 0;
    str.Format("%d", m_BiasPress);
    SetDlgItemText(IDC_BIAS_PRESS, str);
    m_IsOpen = true;
    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNIBPAdjustDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_IsOpen = false;

	CDialog::OnClose();
}

BOOL CNIBPAdjustDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
        return TRUE;
    }
    
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) {
        m_IsOpen = false;
    }

	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH CNIBPAdjustDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
    if (pWnd->m_hWnd == GetDlgItem(IDC_TIPS)->m_hWnd) {
        pDC->SetTextColor(RGB(255, 0, 0));
    }

	// TODO: Return a different brush if the default is not desired
	return hbr;
}
