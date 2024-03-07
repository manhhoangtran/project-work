// ComSetup.cpp : implementation file
//

#include "stdafx.h"
#include "monitor.h"
#include "CommSetupDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComSetupDlg dialog

CComSetupDlg::CComSetupDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CComSetupDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CComSetupDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

void CComSetupDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CComSetupDlg)
    DDX_Control(pDX, IDC_STOPBIT, m_cboStopBit);
    DDX_Control(pDX, IDC_PARITYBIT, m_cboParityBit);
    DDX_Control(pDX, IDC_DATABIT, m_cboDataBit);
    DDX_Control(pDX, IDC_BAUDRATE, m_cboBaudRate);
    DDX_Control(pDX, IDC_PORT, m_cboPort);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComSetupDlg, CDialog)
    //{{AFX_MSG_MAP(CComSetupDlg)
    ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComSetupDlg message handlers

void CComSetupDlg::OnDefault() 
{
    // TODO: Add your control notification handler code here
    m_cboPort.SetCurSel(0);
    m_cboBaudRate.SetCurSel(7);
    m_cboDataBit.SetCurSel(3);
    m_cboParityBit.SetCurSel(0);
    m_cboStopBit.SetCurSel(0);
}

void CComSetupDlg::SaveConfig2Registry(void)
{
    int commPort;
    CString commParam;
    CString key;
    CString str;
    CString port, baudrate, bits, parity, stop;
    
    commPort = ((CMainFrame *)GetParent())->m_CommPort;
    commParam = ((CMainFrame *)GetParent())->m_CommParam;

    key = "Port";
    str.Format("COM%d", commPort);
    theApp.WriteProfileString(CONFIG_SECTION, key, str);
    
    AfxExtractSubString(baudrate, commParam, 0, ',');
    AfxExtractSubString(parity, commParam, 1, ',');
    AfxExtractSubString(bits, commParam, 2, ',');
    AfxExtractSubString(stop, commParam, 3, ',');

    key = "BaudRate";
    str = baudrate;
    theApp.WriteProfileString(CONFIG_SECTION, key, str);
    
    key = "ParityBits";
    str = parity;
    theApp.WriteProfileString(CONFIG_SECTION, key, str);

    key = "DataBits";
    str = bits;
    theApp.WriteProfileString(CONFIG_SECTION, key, str);

    key = "StopBits";
    str = stop;
    theApp.WriteProfileString(CONFIG_SECTION, key, str);
}

void CComSetupDlg::SaveConfig2INIFile(void)
{
    int commPort;
    CString commParam;
    CString key;
    CString str;
    CString port, baudrate, bits, parity, stop;
    
    commPort = ((CMainFrame *)GetParent())->m_CommPort;
    commParam = ((CMainFrame *)GetParent())->m_CommParam;
    
    key = "Port";
    str.Format("COM%d", commPort);
    WritePrivateProfileString("Serial Port Setting", key, str, CONFIG_INI_FILE);
    
    AfxExtractSubString(baudrate, commParam, 0, ',');
    AfxExtractSubString(parity, commParam, 1, ',');
    AfxExtractSubString(bits, commParam, 2, ',');
    AfxExtractSubString(stop, commParam, 3, ',');
    
    key = "BaudRate";
    str = baudrate;
    WritePrivateProfileString("Serial Port Setting", key, str, CONFIG_INI_FILE);
    
    key = "ParityBits";
    str = parity;
    WritePrivateProfileString("Serial Port Setting", key, str, CONFIG_INI_FILE);
    
    key = "DataBits";
    str = bits;
    WritePrivateProfileString("Serial Port Setting", key, str, CONFIG_INI_FILE);
    
    key = "StopBits";
    str = stop;
    WritePrivateProfileString("Serial Port Setting", key, str, CONFIG_INI_FILE);
}

void CComSetupDlg::OnOK() 
{
    // TODO: Add extra validation here
    CString baudrate, parity, bits, stop;

    //保存端口号
    ((CMainFrame *)GetParent())->m_CommPort = m_cboPort.GetCurSel()+1;
    //保存波特率
    m_cboBaudRate.GetLBText(m_cboBaudRate.GetCurSel(), baudrate);
    //保存校验位
    switch (m_cboParityBit.GetCurSel())
    {
    case 0:
        parity="n";
        break;
    case 1:
        parity="o";
        break;
    case 2:
        parity="e";
        break;
    }
    //保存数据位
    m_cboDataBit.GetLBText(m_cboDataBit.GetCurSel(), bits);
    //保存停止位
    m_cboStopBit.GetLBText(m_cboStopBit.GetCurSel(), stop);
    //保存串口设置
    ((CMainFrame *)GetParent())->m_CommParam = baudrate + "," + parity + "," + bits + "," + stop;

    //保存当前串口设置到注册表
    SaveConfig2Registry();
    //SaveConfig2INIFile();

    CDialog::OnOK();
}

BOOL CComSetupDlg::OnInitDialog() 
{
    int port;
    CString param;
    CString baudrate;
    CString paritybit;
    CString databit;
    CString stopbit;
    CString str;
    int i;

    port = ((CMainFrame *)GetParent())->m_CommPort;
    param = ((CMainFrame *)GetParent())->m_CommParam;
    AfxExtractSubString(baudrate, param, 0, ',');
    AfxExtractSubString(paritybit, param, 1, ',');
    AfxExtractSubString(databit, param, 2, ',');
    AfxExtractSubString(stopbit, param, 3, ',');
    
    CDialog::OnInitDialog();

    // TODO: Add extra initialization here
    for (i = 1; i < 100; i++)
    {
        str.Format("COM%d", i);
        m_cboPort.AddString(str);
    }
    m_cboPort.SetCurSel(port-1);
    
    m_cboBaudRate.AddString("1200");
    m_cboBaudRate.AddString("2400");
    m_cboBaudRate.AddString("4800");
    m_cboBaudRate.AddString("9600");
    m_cboBaudRate.AddString("19200");
    m_cboBaudRate.AddString("38400");
    m_cboBaudRate.AddString("57600");
    m_cboBaudRate.AddString("115200");
    for (i = 0; i < m_cboBaudRate.GetCount(); i++)
    {
        m_cboBaudRate.GetLBText(i, str);
        if (str == baudrate)
        {
            m_cboBaudRate.SetCurSel(i);
            break;
        }
    }
    
    m_cboDataBit.AddString("5");
    m_cboDataBit.AddString("6");
    m_cboDataBit.AddString("7");
    m_cboDataBit.AddString("8");
    m_cboDataBit.SetCurSel(3);
    for (i = 0; i < m_cboDataBit.GetCount(); i++)
    {
        m_cboDataBit.GetLBText(i, str);
        if (str == databit)
        {
            m_cboDataBit.SetCurSel(i);
            break;
        }
    }
    
    m_cboParityBit.SetCurSel(0);
   
    m_cboStopBit.AddString("1");
    m_cboStopBit.AddString("1.5");
    m_cboStopBit.AddString("2");
    m_cboStopBit.SetCurSel(0);
    for (i = 0; i < m_cboStopBit.GetCount(); i++)
    {
        m_cboStopBit.GetLBText(i, str);
        if (str == stopbit)
        {
            m_cboStopBit.SetCurSel(i);
            break;
        }
    }
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}




















