// TEMPAdjustDlg.cpp : implementation file
//

#include "stdafx.h"
#include "monitor.h"
#include "TEMPAdjustDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTEMPAdjustDlg dialog


CTEMPAdjustDlg::CTEMPAdjustDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTEMPAdjustDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTEMPAdjustDlg)
    m_TempBias1 = 0;
    m_TempBias2 = 0;
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CTEMPAdjustDlg, CDialog)
	//{{AFX_MSG_MAP(CTEMPAdjustDlg)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BIAS1, OnDeltaposSpinBias1)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BIAS2, OnDeltaposSpinBias2)
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_ADJUST_TEMP1, OnAdjustTemp1)
    ON_BN_CLICKED(ID_ADJUST_TEMP2, OnAdjustTemp2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTEMPAdjustDlg message handlers

void CTEMPAdjustDlg::OnDeltaposSpinBias1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
    CString str;
    
    m_TempBias1 -= pNMUpDown->iDelta;
    if (m_TempBias1 > 20)    // 最大500ms的偏移量
    {
        m_TempBias1 = 20;
    }
    else if (m_TempBias1 < -20)
    {
        m_TempBias1 = -20;
    }
    str.Format("%.1f", (float)m_TempBias1 / 10);
    SetDlgItemText(IDC_TEMP_BIAS1, str);

	*pResult = 0;
}

void CTEMPAdjustDlg::OnAdjustTemp1() 
{
    // TODO: Add your control notification handler code here
    unsigned char cmd[6];
    
    cmd[0] = 0x55;
    cmd[1] = 0xaa;
    cmd[2] = 0x04;
    cmd[3] = 0x0d;
    cmd[4] = m_TempBias1;
    cmd[5] = CMainFrame::CalcSum(cmd, 6);
    ((CMainFrame *)GetParent())->m_Comm.Write(cmd, 6);

    m_TempBias1 = 0;
    SetDlgItemText(IDC_TEMP_BIAS1, "0.0");
}

void CTEMPAdjustDlg::OnDeltaposSpinBias2(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    // TODO: Add your control notification handler code here
    CString str;
    
    m_TempBias2 -= pNMUpDown->iDelta;
    if (m_TempBias2 > 20)    // 最大500ms的偏移量
    {
        m_TempBias2 = 20;
    }
    else if (m_TempBias2 < -20)
    {
        m_TempBias2 = -20;
    }
    str.Format("%.1f", (float)m_TempBias2 / 10);
    SetDlgItemText(IDC_TEMP_BIAS2, str);
    
    *pResult = 0;
}

void CTEMPAdjustDlg::OnAdjustTemp2() 
{
    // TODO: Add your control notification handler code here
    unsigned char cmd[6];
    
    cmd[0] = 0x55;
    cmd[1] = 0xaa;
    cmd[2] = 0x04;
    cmd[3] = 0x0e;
    cmd[4] = m_TempBias2;
    cmd[5] = CMainFrame::CalcSum(cmd, 6);
    ((CMainFrame *)GetParent())->m_Comm.Write(cmd, 6);
    
    m_TempBias2 = 0;
    SetDlgItemText(IDC_TEMP_BIAS2, "0.0");
}

BOOL CTEMPAdjustDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    SetDlgItemText(IDC_TEMP_BIAS1, "0.0");
    SetDlgItemText(IDC_TEMP_BIAS2, "0.0");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTEMPAdjustDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
    m_IsOpen = false;
	
	CDialog::OnClose();
}

BOOL CTEMPAdjustDlg::PreTranslateMessage(MSG* pMsg) 
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

HBRUSH CTEMPAdjustDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
    if (pWnd->m_hWnd == GetDlgItem(IDC_TIPS1)->m_hWnd) {
        pDC->SetTextColor(RGB(255, 0, 0));
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_TIPS2)->m_hWnd) {
        pDC->SetTextColor(RGB(255, 0, 0));
    }

	// TODO: Return a different brush if the default is not desired
	return hbr;
}
