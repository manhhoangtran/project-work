// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__CB0091E3_2A56_4A9E_84D9_E998259F04D5__INCLUDED_)
#define AFX_MAINFRM_H__CB0091E3_2A56_4A9E_84D9_E998259F04D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChannelView.h"
#include "ViewBar.h"
#include "Splitter.h"
#include "CnComm.h"
#include "LeakageTestDlg.h"
#include "StaticPressDlg.h"
#include "NIBPAdjustDlg.h"
#include "TEMPAdjustDlg.h"
#include "VersionDlg.h"

#define PKG_DATA_LEN 12                     // HYS协议的上行数据包的最大长度为12个字节

typedef enum {
    PKG_ECG_WAVE        = 0x01,
    PKG_ECG_PARAM       = 0x02,
    PKG_NIBP            = 0x03,
    PKG_SPO2            = 0x04,
    PKG_TEMP            = 0x05,
#ifdef TXY_SUPPORT
    PKG_TXY             = 0x06,
#endif
#ifdef FGN_SUPPORT
    PKG_FGN             = 0x07,
    PKG_FGN_RATIO       = 0x0e,
#endif
    PKG_SW_VER          = 0xfc,
    PKG_HW_VER          = 0xfd,
    PKG_SPO2_WAVE       = 0xfe,
    PKG_RESP_WAVE       = 0xff
}PKG_TYPE;

const unsigned char BIT0 = 0x01;
const unsigned char BIT1 = 0x02;
const unsigned char BIT2 = 0x04;
const unsigned char BIT3 = 0x08;
const unsigned char BIT4 = 0x10;
const unsigned char BIT5 = 0x20;
const unsigned char BIT6 = 0x40;
const unsigned char BIT7 = 0x80;

const unsigned char CHANNEL_NUM = 5;

const unsigned char ECG_BASEVALUE = 128;
const unsigned char SPO2_BASEVALUE = 0;
const unsigned char RESP_BASEVALUE = 128;

const unsigned char ECG_WAVE_RANGE = 250;
const unsigned char SPO2_WAVE_RANGE = 100;
const unsigned char RESP_WAVE_RANGE = 250;

const double ECG_XSCALE = 0.5f;
const double SPO2_XSCALE = 3.0f;
const double RESP_XSCALE = 2.0f;


class CMainFrame : public CFrameWnd
{
    
protected: // create from serialization only
    CMainFrame();
    DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
    void LoadConfigFromRegistry(void);
    void LoadConfigFromINIFile(void);
    void PrintHexData(char *prefix, unsigned char *data, int len);
    static unsigned char CalcSum(unsigned char *pkg, int len);
    void CheckPackageError(UCHAR pkgType, UCHAR pkgIndex);
    void CheckSampleRate(UCHAR pkgType);
    void ParsePackage(UCHAR *pkgData, UINT pkgLength);
    void InitChannel();
    void OpenPort();
    void ClosePort();
    void UpdateECGWave();
    void UpdateECGParam();
    void UpdateRESPWave();
    void UpdateNIBP();
    void UpdateSPO2Wave();
    void UpdateSPO2Param();
    void UpdateTEMP();
    
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMainFrame)
    public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    protected:
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    //}}AFX_VIRTUAL

// Implementation
public:
    cnComm          m_Comm;
    int             m_CommPort;
    CString         m_CommParam;
    BOOL            m_IsECGTest;
    BOOL            m_IsNIBPTest;
    BOOL            m_IsSPO2Test;
    BOOL            m_IsTEMPTest;
    BOOL            m_IsSpo2WaveTest;    // 血氧波形调试开关
    BOOL            m_IsRespWaveTest;    // 呼吸波形调试开关
    CChannelView    *m_ChannelView[CHANNEL_NUM];
    CLeakageTestDlg m_LeakageTestDlg;
    CStaticPressDlg m_StaticPressDlg;
    CNIBPAdjustDlg  m_NIBPAdjustDlg;
    CTEMPAdjustDlg  m_TEMPAdjustDlg;
    CVersionDlg     m_VersionDlg;
    CString         m_Caption;

    // ECG WAVE数据
    unsigned char m_ECGWave[7]; // 心电7通道波形数据
    
    // ECG PARAM数据
    unsigned char m_ECGStatus;  // 心电状态
    unsigned char m_HeartRate;  // 心率
    unsigned char m_RespRate;   // 呼吸率
    signed char   m_ST;         // ST电位(以二进制补码表示：-100~+100表示	-1mV~+1mV)
    unsigned char m_ArrCode;    // 心率异常代码
    
    // RESP WAVE数据
    unsigned char m_RESPWave;   // 呼吸波形数据

    // NIBP数据
    unsigned char m_NIBPStatus; // 无创血压状态
    unsigned int  m_CuffPress;  // 袖带压力 / 2
    unsigned char m_SysPress;   // 收缩压
    unsigned char m_DiaPress;   // 舒张压
    unsigned char m_MeanPress;  // 平均压

    // SPO2 WAVE数据
    unsigned char m_SPO2Wave;   // 血氧波形数据
    
    // SPO2 PARAM数据
    unsigned char m_SPO2Status; // 血氧状态
    unsigned char m_SPO2Sat;    // 血氧饱和度
    unsigned char m_PulseRate;  // 脉率
    
    // TEMP数据
    unsigned char m_TEMPStatus; // 体温状态
    double        m_BodyTemp1;   // 体温1
    double        m_BodyTemp2;   // 体温2

    // TXY数据
    unsigned char m_TXYStatus;  // 胎心率状态
    unsigned char m_FHeartRate; // 胎心率
    unsigned char m_UPress;     // 宫缩压

    // FGN数据
    unsigned char m_FGNStatus;  // 肺功能状态
    unsigned int  m_LungVC;     // 肺活量
    unsigned int  m_FLungVC;  // 用力肺活量
    
    // ECGSetupDlg相关变量
    unsigned char m_ECGMode;
    unsigned char m_ECGGain;
    unsigned char m_RESPGain;
    unsigned char m_ECGCmd;
	

    // NIBPSetupDlg相关变量
    unsigned char m_NIBPMode;
    unsigned int  m_PresetPress;
    signed char   m_PressBias;

    virtual ~CMainFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
    //CStatusBar  m_wndStatusBar;
    CToolBar    m_wndToolBar;
    CViewBar    m_wndViewBar;
    CSplitter   m_wndSplitter;
    
// Generated message map functions
protected:
    //{{AFX_MSG(CMainFrame)
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnCommSetup();
    afx_msg void OnToolbar();
    afx_msg void OnViewbar();
    afx_msg void OnUpdateToolbar(CCmdUI* pCmdUI);
    afx_msg void OnUpdateViewbar(CCmdUI* pCmdUI);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg LRESULT OnCommRecv(WPARAM wParam, LPARAM lParam);	//注册串口消息处理函数
    afx_msg void OnCOMToggle();
    afx_msg void OnECGTest();
    afx_msg void OnNIBPTest();
    afx_msg void OnSPO2Test();
    afx_msg void OnTEMPTest();
    afx_msg void OnUpdateCOMStart(CCmdUI* pCmdUI);
    afx_msg void OnUpdateCOMStop(CCmdUI* pCmdUI);
    afx_msg void OnUpdateECGStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateECGStop(CCmdUI* pCmdUI);
    afx_msg void OnUpdateNIBPStart(CCmdUI* pCmdUI);
    afx_msg void OnUpdateNIBPStop(CCmdUI* pCmdUI);
    afx_msg void OnUpdateSPO2Start(CCmdUI* pCmdUI);
    afx_msg void OnUpdateSPO2Stop(CCmdUI* pCmdUI);
    afx_msg void OnUpdateTEMPStart(CCmdUI* pCmdUI);
    afx_msg void OnUpdateTEMPStop(CCmdUI* pCmdUI);
    afx_msg void OnEcgSetup();
	afx_msg void OnNIBPSetup();
	afx_msg void OnStaticPressAdjust();
	afx_msg void OnNibpAdjust();
	afx_msg void OnTempAdjust();
	afx_msg void OnGetVersion();
	afx_msg void OnLeakageTest();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__CB0091E3_2A56_4A9E_84D9_E998259F04D5__INCLUDED_)
