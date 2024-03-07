// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "monitor.h"

#include "MainFrm.h"
#include "CommSetupDlg.h"
#include "ECGSetupDlg.h"
#include "NIBPSetupDlg.h"
#include "StaticPressDlg.h"
#include "NIBPAdjustDlg.h"
#include "TEMPAdjustDlg.h"
#include "VersionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    //{{AFX_MSG_MAP(CMainFrame)
    ON_WM_CREATE()
    ON_COMMAND(IDM_COM_SETUP, OnCommSetup)
    ON_COMMAND(IDM_TOOLBAR, OnToolbar)
    ON_COMMAND(IDM_VIEWBAR, OnViewbar)
    ON_UPDATE_COMMAND_UI(IDM_TOOLBAR, OnUpdateToolbar)
    ON_UPDATE_COMMAND_UI(IDM_VIEWBAR, OnUpdateViewbar)
    ON_WM_SIZE()
    ON_MESSAGE(ON_COM_RECEIVE,OnCommRecv)	//串口消息映射
    ON_COMMAND(ID_COM_START, OnCOMToggle)
	ON_COMMAND(ID_ECG_START, OnECGTest)
    ON_COMMAND(ID_NIBP_START, OnNIBPTest)
    ON_COMMAND(ID_SPO2_START, OnSPO2Test)
    ON_COMMAND(ID_TEMP_START, OnTEMPTest)
    ON_UPDATE_COMMAND_UI(ID_COM_START, OnUpdateCOMStart)
    ON_UPDATE_COMMAND_UI(ID_COM_STOP, OnUpdateCOMStop)
    ON_UPDATE_COMMAND_UI(ID_ECG_START, OnUpdateECGStart)
    ON_UPDATE_COMMAND_UI(ID_ECG_STOP, OnUpdateECGStop)
    ON_UPDATE_COMMAND_UI(ID_NIBP_START, OnUpdateNIBPStart)
    ON_UPDATE_COMMAND_UI(ID_NIBP_STOP, OnUpdateNIBPStop)
    ON_UPDATE_COMMAND_UI(ID_SPO2_START, OnUpdateSPO2Start)
    ON_UPDATE_COMMAND_UI(ID_SPO2_STOP, OnUpdateSPO2Stop)
    ON_UPDATE_COMMAND_UI(ID_TEMP_START, OnUpdateTEMPStart)
    ON_UPDATE_COMMAND_UI(ID_TEMP_STOP, OnUpdateTEMPStop)
    ON_COMMAND(IDM_ECG_SETUP, OnEcgSetup)
    ON_COMMAND(IDM_NIBP_SETUP, OnNIBPSetup)
    ON_COMMAND(IDM_STATIC_PRESS_ADJUST, OnStaticPressAdjust)
    ON_COMMAND(IDM_NIBP_ADJUST, OnNibpAdjust)
    ON_COMMAND(IDM_TEMP_ADJUST, OnTempAdjust)
    ON_COMMAND(IDM_GET_VERSION, OnGetVersion)
	ON_COMMAND(IDM_LEAKAGE_TEST, OnLeakageTest)
    ON_COMMAND(ID_COM_STOP, OnCOMToggle)
    ON_COMMAND(ID_ECG_STOP, OnECGTest)
    ON_COMMAND(ID_NIBP_STOP, OnNIBPTest)
    ON_COMMAND(ID_SPO2_STOP, OnSPO2Test)
    ON_COMMAND(ID_TEMP_STOP, OnTEMPTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
    ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};

void CMainFrame::LoadConfigFromRegistry(void)
{
    CString key;
    CString port, baudrate, bits, parity, stop;
    
    key = "Port";
    port = theApp.GetProfileString(CONFIG_SECTION, key, "COM1");
    port.TrimLeft("COM");
    m_CommPort = atoi(port);
    if (m_CommPort < 0 || m_CommPort >= 100)
    {
        MessageBox("Read RegistryKey(\"Port\") error, Port=%s", port);
        m_CommPort = 1;
    }

    key = "BaudRate";
    baudrate = theApp.GetProfileString(CONFIG_SECTION, key, "115200");
    key = "DataBits";
    bits = theApp.GetProfileString(CONFIG_SECTION, key, "8");
    key = "ParityBits";
    parity = theApp.GetProfileString(CONFIG_SECTION, key, "n");
    key = "StopBits";
    stop = theApp.GetProfileString(CONFIG_SECTION, key, "1");
    m_CommParam = baudrate + "," + parity + "," + bits + "," + stop;
}

void CMainFrame::LoadConfigFromINIFile(void)
{
    CString key;
    CString port, baudrate, bits, parity, stop;
    
    key = "Port";
    GetPrivateProfileString("Serial Port Setting", key, "COM1", port.GetBuffer(100), 100, CONFIG_INI_FILE);
    port.ReleaseBuffer();
    port.TrimLeft("COM");
    m_CommPort = atoi(port);
    if (m_CommPort < 0 || m_CommPort >= 100)
    {
        TRACE("Read INIFile(\"Port\") error, Port=%s", port);
        m_CommPort = 1;
    }

    key = "BaudRate";
    GetPrivateProfileString("Serial Port Setting", key, "9600", baudrate.GetBuffer(100), 100, CONFIG_INI_FILE);
    baudrate.ReleaseBuffer();
    
    key = "DataBits";
    GetPrivateProfileString("Serial Port Setting", key, "8", bits.GetBuffer(100), 100, CONFIG_INI_FILE);
    bits.ReleaseBuffer();
    
    key = "ParityBits";
    GetPrivateProfileString("Serial Port Setting", key, "n", parity.GetBuffer(100), 100, CONFIG_INI_FILE);
    parity.ReleaseBuffer();
    
    key = "StopBits";
    GetPrivateProfileString("Serial Port Setting", key, "1", stop.GetBuffer(100), 100, CONFIG_INI_FILE);
    stop.ReleaseBuffer();
    
    m_CommParam = baudrate + "," + parity + "," + bits + "," + stop;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    // TODO: add member initialization code here
    //从注册表读取当前串口设置
    LoadConfigFromRegistry();
    //LoadConfigFromINIFile();

    m_ECGMode = 1;
    m_ECGGain = 2;
    m_RESPGain = 2;
	m_ECGCmd = 3;

    m_NIBPMode = 0;
    m_PresetPress = 150;
    m_PressBias = 0;

    m_IsECGTest = false;
    m_IsNIBPTest = false;
    m_IsSPO2Test = false;
    m_IsTEMPTest = false;

    m_LeakageTestDlg.m_IsOpen = false;
    m_StaticPressDlg.m_IsOpen = false;
    m_NIBPAdjustDlg.m_IsOpen = false;
    m_TEMPAdjustDlg.m_IsOpen = false;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
        | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
        !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
    {
        TRACE("Failed to create toolbar\n");
        return -1;      // fail to create
    }

#if 0
    if (!m_wndStatusBar.Create(this) ||
        !m_wndStatusBar.SetIndicators(indicators,
          sizeof(indicators)/sizeof(UINT)))
    {
        TRACE("Failed to create status bar\n");
        return -1;      // fail to create
    }
#endif

    if (!m_wndViewBar.Create(this, IDD_VIEWBAR, CBRS_RIGHT, IDD_VIEWBAR))
    {
        TRACE("Failed to create m_wndViewBar\n");
        return -1;      // Fail to create.
    }

    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    // TODO: Delete these three lines if you don't want the toolbar to
    //  be dockable
    m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
    m_wndViewBar.EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndToolBar);
    DockControlBar(&m_wndViewBar);
    
    CMenu *pMenu = GetMenu();
    pMenu->CheckMenuItem(IDM_TOOLBAR, MF_CHECKED);
    pMenu->CheckMenuItem(IDM_VIEWBAR, MF_CHECKED);
    pMenu->CheckMenuItem(IDM_STATUSBAR, MF_CHECKED);
    //m_wndStatusBar.ShowWindow(SW_HIDE);
    
    InitChannel();

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if( !CFrameWnd::PreCreateWindow(cs) )
        return FALSE;
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs
    cs.style &= ~FWS_ADDTOTITLE;
    //cs.style &= ~(FWS_ADDTOTITLE|WS_THICKFRAME);
    m_Caption.LoadString(IDS_STR_1);
    cs.lpszName = m_Caption.GetBuffer(100);
    
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnCommSetup()
{
    // TODO: Add your command handler code here
    CComSetupDlg dlg;
    int result;
    
    result = dlg.DoModal();
    if (result == IDOK)
    {
        if (m_Comm.IsOpen()) {
            ClosePort();
        }
        OpenPort();
    }
}

void CMainFrame::OnEcgSetup() 
{
    // TODO: Add your command handler code here
    CECGSetupDlg dlg;
    unsigned char cmd[6];
    int result;
    int i;
    
    result = dlg.DoModal();
    if (result == IDOK)
    {
        cmd[0] = 0x55;
        cmd[1] = 0xaa;
        cmd[2] = 0x04;
        cmd[3] = 0x07;
        cmd[4] = m_ECGGain + 1;
        cmd[5] = CalcSum(cmd, 6);
        m_Comm.Write(cmd, 6);

        cmd[3] = 0x08;
        cmd[4] = m_ECGMode + 1;
        cmd[5] = CalcSum(cmd, 6);
        m_Comm.Write(cmd, 6);

        cmd[3] = 0x0f;
        cmd[4] = m_RESPGain + 1;
        cmd[5] = CalcSum(cmd, 6);
        m_Comm.Write(cmd, 6);

		cmd[3] = 0x05;
        cmd[4] = m_ECGCmd + 1;
        cmd[5] = CalcSum(cmd, 6);
		//PrintHexData("cmd=", cmd, 6);
        m_Comm.Write(cmd, 6);

        for (i = 0; i < CHANNEL_NUM; i++) {
            m_ChannelView[i]->RefreshChannel();
        }
    }
}

void CMainFrame::OnNIBPSetup() 
{
    // TODO: Add your command handler code here
    CNIBPSetupDlg dlg;
    int result;
    unsigned char cmd[6];
    CString str;
    
    result = dlg.DoModal();
    if (result == IDOK)
    {
        cmd[0] = 0x55;
        cmd[1] = 0xaa;
        cmd[2] = 0x04;
        cmd[3] = 0x09;
        cmd[4] = m_NIBPMode + 1;    //wdl, 血压测量模式的参数从0x01开始
        cmd[5] = CalcSum(cmd, 6);
        m_Comm.Write(cmd, 6);
        
        cmd[3] = 0x0a;
        cmd[4] = (unsigned char)(m_PresetPress / 2);
        cmd[5] = CalcSum(cmd, 6);
        m_Comm.Write(cmd, 6);
    }
}

void CMainFrame::OnGetVersion() 
{
    // TODO: Add your command handler code here
    unsigned char cmd[6];
    
    cmd[0] = 0x55;
    cmd[1] = 0xaa;
    cmd[2] = 0x04;
    cmd[3] = 0xfc;
    cmd[4] = 0x00;
    cmd[5] = CalcSum(cmd, 6);
    m_Comm.Write(cmd, 6);
    cmd[0] = 0x55;
    cmd[1] = 0xaa;
    cmd[2] = 0x04;
    cmd[3] = 0xfd;
    cmd[4] = 0x00;
    cmd[5] = CalcSum(cmd, 6);
    m_Comm.Write(cmd, 6);

    m_VersionDlg.DoModal();
}

void CMainFrame::OnToolbar() 
{
    // TODO: Add your command handler code here
    CMenu *pMenu = GetMenu();

    if (m_wndToolBar.IsWindowVisible())
    {
        m_wndToolBar.ShowWindow(SW_HIDE);
        if (m_wndToolBar.IsFloating())
        {
            m_wndToolBar.GetParentFrame()->ShowWindow(SW_HIDE);
        }
        pMenu->CheckMenuItem(IDM_TOOLBAR, MF_UNCHECKED);
    }
    else
    {
        m_wndToolBar.ShowWindow(SW_SHOW);
        if (m_wndToolBar.IsFloating())
        {
            m_wndToolBar.GetParentFrame()->ShowWindow(SW_SHOW);
            m_wndToolBar.GetParentFrame()->RecalcLayout();
        }
        pMenu->CheckMenuItem(IDM_TOOLBAR, MF_CHECKED);
    }
    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        m_ChannelView[i]->RefreshChannel();
    }
    PostMessage(WM_SIZE);    
}

void CMainFrame::OnViewbar() 
{
    // TODO: Add your command handler code here
    CMenu *pMenu = GetMenu();
    
    if (m_wndViewBar.IsWindowVisible())
    {
        m_wndViewBar.ShowWindow(SW_HIDE);
        if (m_wndViewBar.IsFloating())
        {
            m_wndViewBar.GetParentFrame()->ShowWindow(SW_HIDE);
        }
        pMenu->CheckMenuItem(IDM_VIEWBAR, MF_UNCHECKED);
    }
    else
    {
        m_wndViewBar.ShowWindow(SW_SHOW);
        if (m_wndViewBar.IsFloating())
        {
            m_wndViewBar.GetParentFrame()->ShowWindow(SW_SHOW);
            m_wndViewBar.GetParentFrame()->RecalcLayout();
        }
        pMenu->CheckMenuItem(IDM_VIEWBAR, MF_CHECKED);
    }
    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        m_ChannelView[i]->RefreshChannel();
    }
    PostMessage(WM_SIZE);    
}

#if 0
void CMainFrame::OnStatusbar() 
{
    // TODO: Add your command handler code here
    CMenu *pMenu = GetMenu();
    
    if (m_wndStatusBar.IsWindowVisible())
    {
        m_wndStatusBar.ShowWindow(SW_HIDE);
        pMenu->CheckMenuItem(IDM_STATUSBAR, MF_UNCHECKED);
    }
    else
    {
        m_wndStatusBar.ShowWindow(SW_SHOW);
        pMenu->CheckMenuItem(IDM_STATUSBAR, MF_CHECKED);
    }
    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        m_ChannelView[i]->RefreshChannel();
    }
    PostMessage(WM_SIZE);
}
#endif

void CMainFrame::OnUpdateToolbar(CCmdUI* pCmdUI) 
{
    // TODO: Add your command update UI handler code here
    if (m_wndToolBar.IsWindowVisible())
    {
        pCmdUI->SetCheck(1);
    }
    else
    {
        pCmdUI->SetCheck(0);
    }
}

void CMainFrame::OnUpdateViewbar(CCmdUI* pCmdUI) 
{
    // TODO: Add your command update UI handler code here
    if (m_wndViewBar.IsWindowVisible())
    {
        pCmdUI->SetCheck(1);
    }
    else
    {
        pCmdUI->SetCheck(0);
    }
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
    // TODO: Add your specialized code here and/or call the base class
    if (!m_wndSplitter.CreateStatic(this, CHANNEL_NUM, 1))
    {
        TRACE("Failed to CreateStaticSplitter\n");
        return FALSE;
    }
    m_wndSplitter.m_IsCreated = true;
    
    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        if (!m_wndSplitter.CreateView(i, 0,
            RUNTIME_CLASS(CChannelView), CSize(0, 0), pContext))
        {
            TRACE("Failed to create splitter pane\n");
            return FALSE;
        }
    }
    return TRUE;    
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
    CFrameWnd::OnSize(nType, cx, cy);
    
    // TODO: Add your message handler code here
}

void CMainFrame::InitChannel()
{
    m_ChannelView[0] = (CChannelView *)m_wndSplitter.GetPane(0, 0);
    m_ChannelView[0]->m_ChannelType = ECG;
    m_ChannelView[0]->m_Title = "I";
    m_ChannelView[0]->m_ChannelColor = RGB(0, 255, 0);
    m_ChannelView[0]->m_BaseValue = ECG_BASEVALUE;
    m_ChannelView[0]->m_OldValue = ECG_BASEVALUE;
    m_ChannelView[0]->m_CurValue = ECG_BASEVALUE;
    m_ChannelView[0]->m_CurPos = 0;

    m_ChannelView[1] = (CChannelView *)m_wndSplitter.GetPane(1, 0);
    m_ChannelView[1]->m_ChannelType = ECG;
    m_ChannelView[1]->m_Title = "II";
    m_ChannelView[1]->m_ChannelColor = RGB(0, 255, 0);
    m_ChannelView[1]->m_BaseValue = ECG_BASEVALUE;
    m_ChannelView[1]->m_OldValue = ECG_BASEVALUE;
    m_ChannelView[1]->m_CurValue = ECG_BASEVALUE;
    m_ChannelView[1]->m_CurPos = 0;

    m_ChannelView[2] = (CChannelView *)m_wndSplitter.GetPane(2, 0);
    m_ChannelView[2]->m_ChannelType = ECG;
    m_ChannelView[2]->m_Title = "V";
    m_ChannelView[2]->m_ChannelColor = RGB(0, 255, 0);
    m_ChannelView[2]->m_BaseValue = ECG_BASEVALUE;
    m_ChannelView[2]->m_OldValue = ECG_BASEVALUE;
    m_ChannelView[2]->m_CurValue = ECG_BASEVALUE;
    m_ChannelView[2]->m_CurPos = 0;
    
    m_ChannelView[4] = (CChannelView *)m_wndSplitter.GetPane(3, 0);
    m_ChannelView[4]->m_ChannelType = RESP;
    m_ChannelView[4]->m_Title = "RESP";
    m_ChannelView[4]->m_ChannelColor = RGB(255, 255, 0);
    m_ChannelView[4]->m_BaseValue = RESP_BASEVALUE;
    m_ChannelView[4]->m_OldValue = RESP_BASEVALUE;
    m_ChannelView[4]->m_CurValue = RESP_BASEVALUE;
    m_ChannelView[4]->m_CurPos = 0;

    m_ChannelView[3] = (CChannelView *)m_wndSplitter.GetPane(4, 0);
    m_ChannelView[3]->m_ChannelType = SPO2;
    m_ChannelView[3]->m_Title = "SPO2";
    m_ChannelView[3]->m_ChannelColor = RGB(255, 0, 0);
    m_ChannelView[3]->m_BaseValue = SPO2_BASEVALUE;
    m_ChannelView[3]->m_OldValue = SPO2_BASEVALUE;
    m_ChannelView[3]->m_CurValue = SPO2_BASEVALUE;
    m_ChannelView[3]->m_CurPos = 0;
}

void CMainFrame::PrintHexData(char *prefix, unsigned char *data, int len)
{
#if 0   //wdl, format version
    if (prefix) {
        TRACE("%s\n", prefix);
    }
    for (int i = 0; i < len; i++) {
        if (i > 0 && data[i] == 0x55) {
            TRACE("\n");
        }
        TRACE(" 0x%02X", data[i]);
    }
    if (len == 0) {
        TRACE("(null), length=%d\n", len);
    }
    else {
        TRACE(", length=%d\n", len);
    }
#else
    if (prefix) {
        TRACE("%s\n", prefix);
    }
    for (int i = 0; i < len; i++) {
        TRACE(" 0x%02X", data[i]);
    }
    if (len == 0) {
        TRACE("(null), length=%d\n", len);
    }
    else {
        TRACE(", length=%d\n", len);
    }
#endif
}

unsigned char CMainFrame::CalcSum(unsigned char *pkg, int len)
{
    int i;
    unsigned char sum = 0;

    for (i = 2; i < len - 1; i++) {
        sum += pkg[i];
    }

    return ~sum;
}

LRESULT CMainFrame::OnCommRecv(WPARAM wParam, LPARAM lParam)
{
    static UCHAR buffer[256];
    static UINT parseIndex = 0;
    static UINT emptyIndex = 0;
    UCHAR readBuff[100];
    UINT count, i, j;
    UCHAR pkgData[PKG_DATA_LEN];
    BOOL pkgStart;
    UCHAR pkgIndex;
    UINT pkgLength;
    
    count = m_Comm.Read(readBuff, sizeof(readBuff));
    if (count <= 0) {
        //TRACE("com received count=%d\n", count);
        return 0;
    }
    //TRACE("count=%d\n", count);
    //PrintHexData("readBuff:", readBuff, count);

    //TRACE("emptyIndex=%d\n", emptyIndex);
    for (i = 0; i < count; i++) {
        buffer[emptyIndex] = readBuff[i];
        emptyIndex = (emptyIndex + 1) < sizeof(buffer) ? (emptyIndex + 1) : 0;
        if (emptyIndex == parseIndex) {
            TRACE("buffer[%d] is over flow!\n", sizeof(buffer));
            parseIndex = 0;
            emptyIndex = 0;
            return 0;
        }
    }

    //TRACE("\nbefore parse, parseIndex=%d, emptyIndex=%d\n", parseIndex, emptyIndex);
#if 1
    //PrintHexData("buffer:", buffer, sizeof(buffer));
#else
    TRACE("buffer[%d]:\n", count);
    i = parseIndex;
    count = 0;
    do {
        if (i != parseIndex && buffer[i] == 0x55) {
            TRACE("\n");
        }
        TRACE(" 0x%02X", buffer[i]);
        i = (i + 1) < sizeof(buffer) ? (i + 1) : 0;
        count++;
    } while (i != emptyIndex);
    if (count == 0) {
        TRACE("(null), length=%d\n", count);
    }
    else {
        TRACE(", length=%d\n", count);
    }
    TRACE("parseIndex=%d, emptyIndex=%d\n", parseIndex, emptyIndex);
#endif

    pkgStart = false;
    pkgIndex = 0;
    i = parseIndex;
    while (i != emptyIndex) {
        //判断是否为数据头字节(0x55 0xaa)
        if (buffer[i] == 0x55) {
            j = (i + 1) < sizeof(buffer) ? (i + 1) : 0;
            if (j != emptyIndex && buffer[j] == 0xaa) {
                pkgStart = true;
                pkgIndex = 0;
                pkgLength = 0;
                parseIndex = i;
            }
        }
        if (pkgStart) {
            pkgData[pkgIndex] = buffer[i];
            pkgIndex++;
            if (pkgIndex == 3) {
                pkgLength = buffer[i];
            }
            if ((pkgLength != 0) && (pkgIndex == pkgLength + 2)) {
                if (CalcSum(pkgData, pkgIndex) != pkgData[pkgIndex - 1]) {
                    TRACE("received data package checksum error!\n");
                    PrintHexData("pkgData:", pkgData, pkgIndex);
                    //PrintHexData("buffer:", buffer, sizeof(buffer));
                    //TRACE("parseIndex=%d, emptyIndex=%d\n", parseIndex, emptyIndex);
                }
                else {
                    // 处理数据包中的内容
                    ParsePackage(pkgData, pkgIndex);
                }
                pkgStart = false;
                parseIndex = (i + 1) < sizeof(buffer) ? (i + 1) : 0;
            }
        }
        i = (i + 1) < sizeof(buffer) ? (i + 1) : 0;
    }
	return 0;
    //TRACE("after parse, parseIndex=%d, emptyIndex=%d\n\n", parseIndex, emptyIndex);
}

#define ABS(VAL1, VAL2) ((VAL1) >= (VAL2) ? (VAL1) - (VAL2) : (VAL2) - (VAL1))
void CMainFrame::CheckPackageError(UCHAR pkgType, UCHAR pkgIndex)
{
    static UCHAR oldIndex[256];
    static UCHAR oldIndexInit[256];
    static BOOL isFirstInit = false;
    static BOOL isCheckAllType = false;   //wdl, 是否允许所有包类型的检测

    if (!isFirstInit) {
        for (int i = 0; i < sizeof(oldIndexInit); i++) {
            oldIndexInit[i] = false;
        }
        isFirstInit = true;
        return;
    }

    if (!oldIndexInit[pkgType]) {
        oldIndexInit[pkgType] = true;
        oldIndex[pkgType] = pkgIndex;
        return;
    }

    if (ABS(pkgIndex, oldIndex[pkgType]) != 1 && !(oldIndex[pkgType] == 0xff && pkgIndex == 0x00)) {
        if (pkgType == PKG_ECG_WAVE ||
            pkgType == PKG_ECG_PARAM ||
            pkgType == PKG_NIBP ||
            pkgType == PKG_SPO2 ||
            pkgType == PKG_TEMP ||
            pkgType == PKG_SPO2_WAVE ||
            pkgType == PKG_RESP_WAVE ||
            isCheckAllType) {
            TRACE("Pkg(0x%02x) index missing: (0x%02x, 0x%02x)\n", pkgType, oldIndex[pkgType], pkgIndex);
        }
    }
    oldIndex[pkgType] = pkgIndex;
}

void CMainFrame::CheckSampleRate(UCHAR pkgType)
{
    static CString checkName[256];
    static DWORD oldTime[256];
    static INT loopCount[256];
    static INT delayCount[256];
    static BOOL isFirstInit = false;
    static BOOL isCheckAllType = false;   //wdl, 是否允许所有包类型的检测
    int timeSpan;
    DWORD now;
    
    if (!isFirstInit) {
        for (int i = 0; i < 256; i++) {
            oldTime[i] = 0;
        }
        isFirstInit = true;
        return;
    }

    if (oldTime[pkgType] == 0) {
        oldTime[pkgType] = GetTickCount();
        switch (pkgType) {
        case PKG_ECG_WAVE:
            checkName[pkgType] = "ECG WAVE";
            loopCount[pkgType] = 1000;
            break;
        case PKG_ECG_PARAM:
            checkName[pkgType] = "ECG PARAM";
            loopCount[pkgType] = 10;
            break;
        case PKG_NIBP:
            checkName[pkgType] = "NIBP PARAM";
            loopCount[pkgType] = 20;
            break;
        case PKG_SPO2:
            checkName[pkgType] = "SPO2 PARAM";
            loopCount[pkgType] = 10;
            break;
        case PKG_TEMP:
            checkName[pkgType] = "TEMP PARAM";
            loopCount[pkgType] = 10;
            break;
        case PKG_SPO2_WAVE:
            checkName[pkgType] = "SPO2 WAVE";
            loopCount[pkgType] = 200;
            break;
        case PKG_RESP_WAVE:
            checkName[pkgType] = "RESP WAVE";
            loopCount[pkgType] = 200;
            break;
        default:
            TRACE("unsupport package type = %d!\n", pkgType);
            return;
        }
        delayCount[pkgType] = loopCount[pkgType];
        return;
    }
    
    if (delayCount[pkgType]--)
        return;
    
    now = GetTickCount();
    timeSpan = (now - oldTime[pkgType]) / loopCount[pkgType];
    if (pkgType == PKG_ECG_WAVE ||
        pkgType == PKG_ECG_PARAM ||
        pkgType == PKG_NIBP ||
        pkgType == PKG_SPO2 ||
        pkgType == PKG_TEMP ||
        pkgType == PKG_SPO2_WAVE ||
        pkgType == PKG_RESP_WAVE ||
        isCheckAllType) {
        TRACE("Time span=%f sec, %s rate=%d bps\n", (double)timeSpan / 1000, checkName[pkgType], (int)(1000 / (double)timeSpan + 0.5));
    }
    oldTime[pkgType] = now;
    delayCount[pkgType] = loopCount[pkgType];
}

void CMainFrame::ParsePackage(UCHAR *pkgData, UINT pkgLength)
{
    UCHAR pkgType;
    CHAR version[8];
    UINT i;
    CString str;

    //CheckPackageError(pkgData[3], pkgData[4]);//  return; //wdl, just for debug
    //CheckSampleRate(pkgData[3]);
    //PrintHexData(NULL, pkgData, pkgLength);
    // 处理数据包中的内容
    pkgType = pkgData[3];    // 数据包类型
    switch (pkgType) {
        case PKG_ECG_WAVE:  // 心电波形数据
            //PrintHexData("pkgData:", pkgData, pkgLength);
            for (i = 0; i < 7; i++) {
                m_ECGWave[i] = pkgData[i + 4];
            }
            UpdateECGWave();
            break;
        case PKG_ECG_PARAM:  // 心电参数数据
            //PrintHexData("pkgData:", pkgData, pkgLength);
            m_ECGStatus = pkgData[4];
            m_HeartRate = pkgData[5];
            m_RespRate = pkgData[6];
            m_ST = pkgData[7];
            m_ArrCode = pkgData[8];
            //TRACE("m_ArrCode=%d\n", m_ArrCode);
            UpdateECGParam();
            m_IsECGTest = true;
            break;
        case PKG_NIBP:  // 血压数据
            //PrintHexData("pkgData:", pkgData, pkgLength);
            m_NIBPStatus = pkgData[4];
            //TRACE("m_NIBPStatus=0x%02x\n", m_NIBPStatus);
            m_CuffPress = pkgData[5] * 2;
            m_SysPress = pkgData[6];
            m_MeanPress = pkgData[7];
            m_DiaPress = pkgData[8];
            UpdateNIBP();
           break;
        case PKG_SPO2:  // 血氧数据
            //PrintHexData("pkgData:", pkgData, pkgLength);
            m_SPO2Status = pkgData[4];
            m_SPO2Sat = pkgData[5];
            m_PulseRate = pkgData[6];
            UpdateSPO2Param();
            m_IsSPO2Test = true;
            break;
        case PKG_TEMP:  // 体温数据
            //PrintHexData("pkgData:", pkgData, pkgLength);
            m_TEMPStatus = pkgData[4];
            m_BodyTemp1 = pkgData[5] + (double)pkgData[6] / 10;
            if (pkgLength == 8) {    // 好医生协议不支持体温2
                m_BodyTemp2 = 0;
            }
            else {
                m_BodyTemp2 = pkgData[7] + (double)pkgData[8] / 10;
            }
            //TRACE("m_BodyTemp1=%.1f, m_BodyTemp2=%.1f\n", m_BodyTemp1, m_BodyTemp2);
            UpdateTEMP();
            m_IsTEMPTest = true;
            break;
        case PKG_SW_VER:  // 软件版本号
            //PrintHexData("pkgData:", pkgData, pkgLength);
            memset(version, 0, sizeof(version));
            for (i = 4; i < pkgLength - 1; i++) {
                version[i - 4] = pkgData[i];
            }
            version[i - 4] = 0;
            TRACE("software version=%s\n", version);
            m_VersionDlg.SetDlgItemText(IDC_SW_VER, version);
            break;
        case PKG_HW_VER:  // 硬件版本号
            //PrintHexData("pkgData:", pkgData, pkgLength);
            memset(version, 0, sizeof(version));
            for (i = 4; i < pkgLength - 1; i++) {
                version[i - 4] = pkgData[i];
            }
            version[i - 4] = 0;
            TRACE("hardware version=%s\n", version);
            m_VersionDlg.SetDlgItemText(IDC_HW_VER, version);
            break;
        case PKG_SPO2_WAVE:  // 血氧波形数据
            //PrintHexData("pkgData:", pkgData, pkgLength);
            m_SPO2Wave = pkgData[4];
            UpdateSPO2Wave();
            m_IsSpo2WaveTest = true;
            break;
        case PKG_RESP_WAVE:  // 呼吸波形数据
            //PrintHexData("pkgData=", pkgData, pkgLength);
            m_RESPWave = pkgData[4];
            UpdateRESPWave();
            m_IsRespWaveTest = true;
            break;
        default:
            PrintHexData("invalid package=", pkgData, pkgLength);
            break;
    }
}

void CMainFrame::OpenPort() 
{
    CString str1, str2;

    // TODO: Add your control notification handler code here
    int port = m_CommPort;
    
    try
    {
        if (m_Comm.Open(m_CommPort, (char*)(LPCTSTR)m_CommParam))
        {
            m_Comm.SetWnd(this->m_hWnd);		//设置消息处理窗口
            m_Comm.SetNotifyNum(8);   //设定发送通知, 接受字符最小值
        }
        else
        {
            m_Comm.Close();
            str2.LoadString(IDS_STR_3);
            str1.Format("COM%d %s", m_CommPort, str2);
            str2.LoadString(IDS_STR_2);
            MessageBox(str1, str2, MB_ICONERROR);
        }
    }
    catch(CException *e)
    {
        char errMsg[1024];
        e->GetErrorMessage(errMsg, 1024);
        TRACE("errMsg: %s", errMsg);
        return;
    }
}

void CMainFrame::ClosePort() 
{
	// TODO: Add your command handler code here
    try
    {
        m_Comm.Close();
    }
    catch(CException* e)
    {
        char errMsg[1024];
        e->GetErrorMessage(errMsg, 1024);
        TRACE("errMsg: %s", errMsg);
        return;
    }
}

void CMainFrame::OnCOMToggle() 
{
    // TODO: Add your command handler code here
    if (!m_Comm.IsOpen()) {
        OpenPort();
    }
    else {
        ClosePort();
    }
}

void CMainFrame::OnECGTest() 
{
    // TODO: Add your command handler code here
    unsigned char cmd[6];
    
    m_IsECGTest = !m_IsECGTest;
    cmd[0] = 0x55;
    cmd[1] = 0xaa;
    cmd[2] = 0x04;
    cmd[3] = 0x01;
    cmd[4] = m_IsECGTest;
    cmd[5] = CalcSum(cmd, 6);
    m_Comm.Write(cmd, 6);

    cmd[3] = 0xfb;
    cmd[4] = m_IsECGTest;
    cmd[5] = CalcSum(cmd, 6);
    m_Comm.Write(cmd, 6);

    cmd[3] = 0xff;
    cmd[4] = m_IsECGTest;
    cmd[5] = CalcSum(cmd, 6);
    m_Comm.Write(cmd, 6);

    if (!m_IsECGTest) {
        m_wndViewBar.SetDlgItemText(IDC_HR, "---");
        m_wndViewBar.SetDlgItemText(IDC_RESP, "---");
        m_wndViewBar.SetDlgItemText(IDC_ST, "---");
        m_wndViewBar.SetDlgItemText(IDC_ARR, "---");
        m_wndViewBar.SetDlgItemText(IDC_ECG_LEAD_STATE, "");
        m_wndViewBar.SetDlgItemText(IDC_ECG_SIGNAL, "");
        m_wndViewBar.SetDlgItemText(IDC_ECG_MODE, "");
        m_wndViewBar.SetDlgItemText(IDC_ECG_GAIN, "");
    }
}

void CMainFrame::OnNIBPTest() 
{
    // TODO: Add your command handler code here
    unsigned char cmd[6];
    
    m_IsNIBPTest = !m_IsNIBPTest;
    cmd[0] = 0x55;
    cmd[1] = 0xaa;
    cmd[2] = 0x04;
    cmd[3] = 0x02;
    cmd[4] = m_IsNIBPTest;
    cmd[5] = CalcSum(cmd, 6);
    m_Comm.Write(cmd, 6);

    if (!m_IsNIBPTest) {
        m_wndViewBar.SetDlgItemText(IDC_SYS, "---");
        m_wndViewBar.SetDlgItemText(IDC_DIA, "---");
        m_wndViewBar.SetDlgItemText(IDC_MEAN, "---");
        m_wndViewBar.SetDlgItemText(IDC_CUFF, "---");
    }
}

void CMainFrame::OnSPO2Test() 
{
    // TODO: Add your command handler code here
    unsigned char cmd[6];
    
    m_IsSPO2Test = !m_IsSPO2Test;
    cmd[0] = 0x55;
    cmd[1] = 0xaa;
    cmd[2] = 0x04;
    cmd[3] = 0x03;
    cmd[4] = m_IsSPO2Test;
    cmd[5] = CalcSum(cmd, 6);
    m_Comm.Write(cmd, 6);

    cmd[3] = 0xfe;
    cmd[4] = m_IsSPO2Test;
    cmd[5] = CalcSum(cmd, 6);
    m_Comm.Write(cmd, 6);    

    if (!m_IsSPO2Test) {
        m_wndViewBar.SetDlgItemText(IDC_SPO2, "---");
        m_wndViewBar.SetDlgItemText(IDC_PR, "---");
        m_wndViewBar.SetDlgItemText(IDC_SPO2_STATE, "");
    }
}

void CMainFrame::OnTEMPTest() 
{
    // TODO: Add your command handler code here
    unsigned char cmd[6];
    
    m_IsTEMPTest = !m_IsTEMPTest;
    cmd[0] = 0x55;
    cmd[1] = 0xaa;
    cmd[2] = 0x04;
    cmd[3] = 0x04;
    cmd[4] = m_IsTEMPTest;
    cmd[5] = CalcSum(cmd, 6);
    m_Comm.Write(cmd, 6);

    if (!m_IsTEMPTest) {
        m_wndViewBar.SetDlgItemText(IDC_TEMP1, "---");
        m_wndViewBar.SetDlgItemText(IDC_TEMP2, "---");
       m_wndViewBar.SetDlgItemText(IDC_TEMP_STATE, "");
    }
}

void CMainFrame::OnUpdateCOMStart(CCmdUI* pCmdUI) 
{
    // TODO: Add your command update UI handler code here
    if (m_Comm.IsOpen())
        pCmdUI->Enable(false);
    else
        pCmdUI->Enable(true);
}

void CMainFrame::OnUpdateCOMStop(CCmdUI* pCmdUI) 
{
    // TODO: Add your command update UI handler code here
    if (!m_Comm.IsOpen())
        pCmdUI->Enable(false);
    else
        pCmdUI->Enable(true);
}

void CMainFrame::OnUpdateECGStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if (m_IsECGTest)
        pCmdUI->Enable(false);
    else
        pCmdUI->Enable(true);
}

void CMainFrame::OnUpdateECGStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    if (!m_IsECGTest)
        pCmdUI->Enable(false);
    else
        pCmdUI->Enable(true);
}

void CMainFrame::OnUpdateNIBPStart(CCmdUI* pCmdUI) 
{
    // TODO: Add your command update UI handler code here
    if (m_IsNIBPTest)
        pCmdUI->Enable(false);
    else
        pCmdUI->Enable(true);
}

void CMainFrame::OnUpdateNIBPStop(CCmdUI* pCmdUI) 
{
    // TODO: Add your command update UI handler code here
    if (!m_IsNIBPTest)
        pCmdUI->Enable(false);
    else
        pCmdUI->Enable(true);
}
void CMainFrame::OnUpdateSPO2Start(CCmdUI* pCmdUI) 
{
    // TODO: Add your command update UI handler code here
    if (m_IsSPO2Test)
        pCmdUI->Enable(false);
    else
        pCmdUI->Enable(true);
}

void CMainFrame::OnUpdateSPO2Stop(CCmdUI* pCmdUI) 
{
    // TODO: Add your command update UI handler code here
    if (!m_IsSPO2Test)
        pCmdUI->Enable(false);
    else
        pCmdUI->Enable(true);
}
void CMainFrame::OnUpdateTEMPStart(CCmdUI* pCmdUI) 
{
    // TODO: Add your command update UI handler code here
    if (m_IsTEMPTest)
        pCmdUI->Enable(false);
    else
        pCmdUI->Enable(true);
}

void CMainFrame::OnUpdateTEMPStop(CCmdUI* pCmdUI) 
{
    // TODO: Add your command update UI handler code here
    if (!m_IsTEMPTest)
        pCmdUI->Enable(false);
    else
        pCmdUI->Enable(true);
}

void CMainFrame::UpdateECGWave()
{
    int i;

    for (i = 0; i < 3; i++) {
        m_ChannelView[i]->m_OldValue = m_ChannelView[i]->m_CurValue;
        m_ChannelView[i]->m_CurValue = m_ECGWave[i];
        m_ChannelView[i]->DrawCurve();
        m_ChannelView[i]->m_CurPos++;
    }
}

void CMainFrame::UpdateECGParam()
{
    CString str;
        
    //TRACE("m_ECGStatus=0x%02x\n", m_ECGStatus);
    if (m_ECGStatus & BIT1) {
        str.LoadString(IDS_STR_5);
    }
    else {
        str.LoadString(IDS_STR_4);
    }
    m_wndViewBar.SetDlgItemText(IDC_ECG_LEAD_STATE, str);
    
    m_ECGGain = (m_ECGStatus & (BIT3|BIT2)) >> 2;
    switch(m_ECGGain) {
    case 0x00:
        str.Format("%s", "x0.25");
        break;
    case 0x01:
        str.Format("%s", "x0.5");
        break;
    case 0x02:
        str.Format("%s", "x1");
        break;
    case 0x03:
        str.Format("%s", "x2");
        break;
    default:
        TRACE("invalid ECG gain=%d\n", m_ECGGain);
        break;
    }
    m_wndViewBar.SetDlgItemText(IDC_ECG_GAIN, str);
    
    m_ECGMode = (m_ECGStatus & (BIT5|BIT4)) >> 4;
    switch(m_ECGMode) {
    case 0x00:
        str.LoadString(IDS_STR_6);
        break;
    case 0x01:
        str.LoadString(IDS_STR_7);
        break;
    case 0x02:
        str.LoadString(IDS_STR_8);
        break;
    default:
        break;
    }
    m_wndViewBar.SetDlgItemText(IDC_ECG_MODE, str);
    
    if (m_ECGStatus & BIT0) {
        str.LoadString(IDS_STR_9);
    }
    else {
        if (m_ECGStatus & BIT1) {
            str = "";
        }
        else {
            str.LoadString(IDS_STR_43);
        }
    }
    m_wndViewBar.SetDlgItemText(IDC_ECG_SIGNAL, str);

    if (m_ECGStatus & BIT1) {
        str.Format("%s", "---");
    }
    else {
        str.Format("%d", m_HeartRate);
    }
    m_wndViewBar.SetDlgItemText(IDC_HR, str);

    if (m_ECGStatus & BIT1) {
        str.Format("%s", "---");
    }
    else {
        str.Format("%d", m_RespRate);
    }
    m_wndViewBar.SetDlgItemText(IDC_RESP, str);

    if (m_ECGStatus & BIT1) {
        str.Format("%s", "---");
    }
    else {
        str.Format("%.2f", (float)m_ST / 100);
    }
    m_wndViewBar.SetDlgItemText(IDC_ST, str);

    if (m_ECGStatus & BIT1) {
        str.Format("%s", "---");
    }
    else {
        switch(m_ArrCode) {
        case 0x00:
            str.LoadString(IDS_STR_10);
        	break;
        case 0x01:
            str = "";
            break;
        case 0x02:
            str.LoadString(IDS_STR_11);
            break;
        case 0x03:
            str.LoadString(IDS_STR_12);
            break;
        case 0x04:
            str.LoadString(IDS_STR_13);
            break;
        case 0x05:
            str.LoadString(IDS_STR_14);
            break;
        case 0x06:
            str.LoadString(IDS_STR_15);
            break;
        case 0x07:
            str.LoadString(IDS_STR_16);
            break;
        case 0x08:
            str.LoadString(IDS_STR_17);
            break;
        case 0x09:
            str.LoadString(IDS_STR_18);
            break;
        case 0x0a:
            str.LoadString(IDS_STR_19);
            break;
        case 0x0b:
            str.LoadString(IDS_STR_20);
            break;
        case 0x0c:
            str.LoadString(IDS_STR_21);
            break;
        default:
            TRACE("invalid ARR code=%d\n", m_ArrCode);
            return;
        }
    }
    m_wndViewBar.SetDlgItemText(IDC_ARR, str);
}

void CMainFrame::UpdateRESPWave()
{
    m_ChannelView[4]->m_OldValue = m_ChannelView[4]->m_CurValue;
    m_ChannelView[4]->m_CurValue = m_RESPWave;
    m_ChannelView[4]->DrawCurve();
    m_ChannelView[4]->m_CurPos++;
}

void CMainFrame::UpdateNIBP()
{
    CString str;
    UCHAR mode, state;
    
    mode = m_NIBPStatus & (BIT1 | BIT0);
    switch(mode) {
    case 0x00:
        m_NIBPMode = mode;
        str.LoadString(IDS_STR_22);
        break;
    case 0x01:
        m_NIBPMode = mode;
        str.LoadString(IDS_STR_23);
        break;
    case 0x02:
        m_NIBPMode = mode;
        str.LoadString(IDS_STR_24);
        break;
    default:
        TRACE("invalid NIBP mode=%d\n", mode);
        break;
    }
    m_wndViewBar.SetDlgItemText(IDC_NIBP_MODE, str);

    state = (m_NIBPStatus & (BIT5 | BIT4 | BIT3 | BIT2)) >> 2;
    switch(state) {
    case 0x00:
        str.LoadString(IDS_STR_25);
        m_IsNIBPTest = false;
        break;
    case 0x01:
        str.LoadString(IDS_STR_26);
        m_IsNIBPTest = true;
        break;
    case 0x02:
        str.LoadString(IDS_STR_27);
        m_IsNIBPTest = false;
        break;
    case 0x03:
        str.LoadString(IDS_STR_28);
        m_IsNIBPTest = false;
        break;
    case 0x04:
        str.LoadString(IDS_STR_29);
        m_IsNIBPTest = false;
        break;
    case 0x05:
        str.LoadString(IDS_STR_30);
        m_IsNIBPTest = false;
        break;
    case 0x06:
        str.LoadString(IDS_STR_31);
        m_IsNIBPTest = false;
        break;
    case 0x07:
        str.LoadString(IDS_STR_32);
        m_IsNIBPTest = false;
        break;
    case 0x08:
        str.LoadString(IDS_STR_33);
        m_IsNIBPTest = false;
        break;
    case 0x09:
        str.LoadString(IDS_STR_34);
        break;
    case 0x0a:
        str.LoadString(IDS_STR_35);
        break;
    default:
        TRACE("invalid NIBP status=%d\n", state);
        break;
    }
    m_wndViewBar.SetDlgItemText(IDC_NIBP_STATE, str);

    if (m_LeakageTestDlg.m_IsOpen) {
        LPTSTR p;
        if (state == 0x01 && m_LeakageTestDlg.m_IsLeakageTest) {
            str.LoadString(IDS_STR_45);
            p = str.GetBuffer(10);
            m_LeakageTestDlg.SetDlgItemText(ID_LEAKAGE_TEST, p);
            str.ReleaseBuffer();
        }
        else {
            m_LeakageTestDlg.m_IsLeakageTest = false;
            str.LoadString(IDS_STR_44);
            p = str.GetBuffer(10);
            m_LeakageTestDlg.SetDlgItemText(ID_LEAKAGE_TEST, p);
            str.ReleaseBuffer();
        }
    }

    if ((state == 0x00) || (state == 0x07)) {
        str.Format("%d", m_SysPress);
        m_wndViewBar.SetDlgItemText(IDC_SYS, str);
        str.Format("%d", m_MeanPress);
        m_wndViewBar.SetDlgItemText(IDC_MEAN, str);
        str.Format("%d", m_DiaPress);
        m_wndViewBar.SetDlgItemText(IDC_DIA, str);
    }
    else {
        m_wndViewBar.SetDlgItemText(IDC_SYS, "---");
        m_wndViewBar.SetDlgItemText(IDC_MEAN, "---");
        m_wndViewBar.SetDlgItemText(IDC_DIA, "---");
    }
 
    str.Format("%d", m_CuffPress);
    m_wndViewBar.SetDlgItemText(IDC_CUFF, str); //wdl, 实时显示袖带压力值

    if (m_StaticPressDlg.m_IsOpen) {
        str.Format("%d", m_CuffPress);
        m_StaticPressDlg.SetDlgItemText(IDC_CUFF_PRESS, str);
    }
    if (m_NIBPAdjustDlg.m_IsOpen) {
        str.Format("%d", m_CuffPress);
        m_NIBPAdjustDlg.SetDlgItemText(IDC_REAL_PRESS, str);
    }
}

void CMainFrame::UpdateSPO2Wave()
{
    m_ChannelView[3]->m_OldValue = m_ChannelView[3]->m_CurValue;
    m_ChannelView[3]->m_CurValue = m_SPO2Wave;
    m_ChannelView[3]->DrawCurve();
    m_ChannelView[3]->m_CurPos++;
}

void CMainFrame::UpdateSPO2Param()
{
    CString str;
    
    switch(m_SPO2Status) {
    case 0x00:
        str = "";
        break;
    case 0x01:
        str.LoadString(IDS_STR_36);
        break;
    case 0x02:
        str.LoadString(IDS_STR_37);
        break;
    case 0x03:
        str.LoadString(IDS_STR_38);
        break;
    case 0x04:
        str.LoadString(IDS_STR_39);
        break;
    default:
        TRACE("invalid SPO2 status=%d\n", m_SPO2Status);
        break;
    }
    m_wndViewBar.SetDlgItemText(IDC_SPO2_STATE, str);

    if (m_SPO2Status != 0x00) {
        str.Format("%s", "---");
    }
    else {
        str.Format("%d", m_SPO2Sat);
    }
    m_wndViewBar.SetDlgItemText(IDC_SPO2, str);

    if (m_SPO2Status != 0x00) {
        str.Format("%s", "---");
    }
    else {
        str.Format("%d", m_PulseRate);
    }
    m_wndViewBar.SetDlgItemText(IDC_PR, str);
}

void CMainFrame::UpdateTEMP()
{
    CString str;
    
    if (m_TEMPStatus == 0x00) {
        str.Format("%.1f", m_BodyTemp1);
        m_wndViewBar.SetDlgItemText(IDC_TEMP1, str);
        str.Format("%.1f", m_BodyTemp2);
        m_wndViewBar.SetDlgItemText(IDC_TEMP2, str);
        str = "";
        m_wndViewBar.SetDlgItemText(IDC_TEMP_STATE, str);
    }
    else if (m_TEMPStatus == 0x01) {
        m_wndViewBar.SetDlgItemText(IDC_TEMP1, "---");
        str.Format("%.1f", m_BodyTemp2);
        m_wndViewBar.SetDlgItemText(IDC_TEMP2, str);
        str.LoadString(IDS_STR_40);
        m_wndViewBar.SetDlgItemText(IDC_TEMP_STATE, str);
    }
    else if (m_TEMPStatus == 0x02) {
        str.Format("%.1f", m_BodyTemp1);
        m_wndViewBar.SetDlgItemText(IDC_TEMP1, str);
        m_wndViewBar.SetDlgItemText(IDC_TEMP2, "---");
        str.LoadString(IDS_STR_41);
        m_wndViewBar.SetDlgItemText(IDC_TEMP_STATE, str);
    }
    else {
        m_wndViewBar.SetDlgItemText(IDC_TEMP1, "---");
        m_wndViewBar.SetDlgItemText(IDC_TEMP2, "---");
        str.LoadString(IDS_STR_42);
        m_wndViewBar.SetDlgItemText(IDC_TEMP_STATE, str);
    }
}

void CMainFrame::OnLeakageTest() 
{
    // TODO: Add your command handler code here
    // TODO: Add your command handler code here
    m_LeakageTestDlg.DoModal();
}

void CMainFrame::OnStaticPressAdjust() 
{
    // TODO: Add your command handler code here
    unsigned char cmd[6];

    cmd[0] = 0x55;
    cmd[1] = 0xaa;
    cmd[2] = 0x04;
    cmd[3] = 0x0b;
    cmd[4] = 0x01;
    cmd[5] = CalcSum(cmd, 6);
    m_Comm.Write(cmd, 6);

    m_StaticPressDlg.DoModal();

    cmd[0] = 0x55;
    cmd[1] = 0xaa;
    cmd[2] = 0x04;
    cmd[3] = 0x0b;
    cmd[4] = 0x00;
    cmd[5] = CalcSum(cmd, 6);
    m_Comm.Write(cmd, 6);

    m_wndViewBar.SetDlgItemText(IDC_SYS, "---");
    m_wndViewBar.SetDlgItemText(IDC_DIA, "---");
    m_wndViewBar.SetDlgItemText(IDC_MEAN, "---");
    m_wndViewBar.SetDlgItemText(IDC_CUFF, "---");
    m_wndViewBar.SetDlgItemText(IDC_NIBP_MODE, "");
    m_wndViewBar.SetDlgItemText(IDC_NIBP_STATE, "");
}

void CMainFrame::OnNibpAdjust() 
{
    // TODO: Add your command handler code here
    unsigned char cmd[6];
    
    cmd[0] = 0x55;
    cmd[1] = 0xaa;
    cmd[2] = 0x04;
    cmd[3] = 0x0b;
    cmd[4] = 0x01;
    cmd[5] = CalcSum(cmd, 6);
    m_Comm.Write(cmd, 6);

    m_NIBPAdjustDlg.DoModal();

    cmd[0] = 0x55;
    cmd[1] = 0xaa;
    cmd[2] = 0x04;
    cmd[3] = 0x0b;
    cmd[4] = 0x00;
    cmd[5] = CalcSum(cmd, 6);
    m_Comm.Write(cmd, 6);

    m_wndViewBar.SetDlgItemText(IDC_SYS, "---");
    m_wndViewBar.SetDlgItemText(IDC_DIA, "---");
    m_wndViewBar.SetDlgItemText(IDC_MEAN, "---");
    m_wndViewBar.SetDlgItemText(IDC_CUFF, "---");
    m_wndViewBar.SetDlgItemText(IDC_NIBP_MODE, "");
    m_wndViewBar.SetDlgItemText(IDC_NIBP_STATE, "");
}

void CMainFrame::OnTempAdjust() 
{
    // TODO: Add your command handler code here
    unsigned char cmd[6];
    
    if (!m_IsTEMPTest) {
        cmd[0] = 0x55;
        cmd[1] = 0xaa;
        cmd[2] = 0x04;
        cmd[3] = 0x04;
        cmd[4] = 0x01;
        cmd[5] = CalcSum(cmd, 6);
        m_Comm.Write(cmd, 6);
    }
    
    m_TEMPAdjustDlg.DoModal();

    if (!m_IsTEMPTest) {
        cmd[0] = 0x55;
        cmd[1] = 0xaa;
        cmd[2] = 0x04;
        cmd[3] = 0x04;
        cmd[4] = 0x00;
        cmd[5] = CalcSum(cmd, 6);
        m_Comm.Write(cmd, 6);
    }
}
