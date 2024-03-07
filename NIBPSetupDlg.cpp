// NIBPSetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "monitor.h"
#include "NIBPSetupDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNIBPSetupDlg dialog


CNIBPSetupDlg::CNIBPSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNIBPSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNIBPSetupDlg)
	//}}AFX_DATA_INIT
}

void CNIBPSetupDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CNIBPSetupDlg)
    DDX_Control(pDX, IDC_MODE, m_cboNIBPMode);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNIBPSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CNIBPSetupDlg)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PRESET, OnDeltaposSpinPreset)
	ON_CBN_SELCHANGE(IDC_MODE, OnSelchangeMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNIBPSetupDlg message handlers

BOOL CNIBPSetupDlg::OnInitDialog() 
{
    CString str;
    UCHAR mode;
    
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    mode = ((CMainFrame *)GetParent())->m_NIBPMode;
    m_cboNIBPMode.SetCurSel(mode);
    UpdateData(false);

    switch(mode) {
    case 0x00:
        ((CMainFrame *)GetParent())->m_PresetPress = 150;
        break;
    case 0x01:
        ((CMainFrame *)GetParent())->m_PresetPress = 100;
        break;
    case 0x02:
        ((CMainFrame *)GetParent())->m_PresetPress = 70;
        break;
    default:
        TRACE("invalid NIBP mode=%d\n", mode);
        break;
    }
    str.Format("%d", ((CMainFrame *)GetParent())->m_PresetPress);
    SetDlgItemText(IDC_PRESET, str);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNIBPSetupDlg::OnOK() 
{
    CString str;

	// TODO: Add extra validation here
	UpdateData(true);
    ((CMainFrame *)GetParent())->m_NIBPMode = m_cboNIBPMode.GetCurSel();
    GetDlgItemText(IDC_PRESET, str);
    ((CMainFrame *)GetParent())->m_PresetPress = atoi(str);    

	CDialog::OnOK();
}

void CNIBPSetupDlg::OnDeltaposSpinPreset(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
    CString str;
    UCHAR mode;
    INT max, min;
    INT preset;
    
    mode = m_cboNIBPMode.GetCurSel();
    switch(mode) {
    case 0x00:
        max = 300;
        min = 40;
    	break;
    case 0x01:
        max = 210;
        min = 40;
        break;
    case 0x02:
        max = 140;
        min = 40;
        break;
    default:
        TRACE("invalid NIBP mode=%d\n", mode);
        break;
    }

    GetDlgItemText(IDC_PRESET, str);
    preset = atoi(str);
    preset -= pNMUpDown->iDelta * 10;
    if (preset > max)    // 最大500ms的偏移量
    {
        preset = max;
    }
    else if (preset < min)
    {
        preset = min;
    }
    str.Format("%d", preset);
    SetDlgItemText(IDC_PRESET, str);
    
	*pResult = 0;
}

void CNIBPSetupDlg::OnSelchangeMode() 
{
	// TODO: Add your control notification handler code here
    UCHAR mode;
    INT preset;
    CString str;
    
    mode = m_cboNIBPMode.GetCurSel();
    switch(mode) {
    case 0x00:
        preset = 150;
        break;
    case 0x01:
        preset = 100;
        break;
    case 0x02:
        preset = 70;
        break;
    default:
        TRACE("invalid NIBP mode=%d\n", mode);
        break;
    }

    str.Format("%d", preset);
    SetDlgItemText(IDC_PRESET, str);    
}
