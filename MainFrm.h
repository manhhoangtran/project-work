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

#define PKG_DATA_LEN 12                     // HYSЭ����������ݰ�����󳤶�Ϊ12���ֽ�

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
    BOOL            m_IsSpo2WaveTest;    // Ѫ�����ε��Կ���
    BOOL            m_IsRespWaveTest;    // �������ε��Կ���
    CChannelView    *m_ChannelView[CHANNEL_NUM];
    CLeakageTestDlg m_LeakageTestDlg;
    CStaticPressDlg m_StaticPressDlg;
    CNIBPAdjustDlg  m_NIBPAdjustDlg;
    CTEMPAdjustDlg  m_TEMPAdjustDlg;
    CVersionDlg     m_VersionDlg;
    CString         m_Caption;

    // ECG WAVE����
    unsigned char m_ECGWave[7]; // �ĵ�7ͨ����������
    
    // ECG PARAM����
    unsigned char m_ECGStatus;  // �ĵ�״̬
    unsigned char m_HeartRate;  // ����
    unsigned char m_RespRate;   // ������
    signed char   m_ST;         // ST��λ(�Զ����Ʋ����ʾ��-100~+100��ʾ	-1mV~+1mV)
    unsigned char m_ArrCode;    // �����쳣����
    
    // RESP WAVE����
    unsigned char m_RESPWave;   // ������������

    // NIBP����
    unsigned char m_NIBPStatus; // �޴�Ѫѹ״̬
    unsigned int  m_CuffPress;  // ���ѹ�� / 2
    unsigned char m_SysPress;   // ����ѹ
    unsigned char m_DiaPress;   // ����ѹ
    unsigned char m_MeanPress;  // ƽ��ѹ

    // SPO2 WAVE����
    unsigned char m_SPO2Wave;   // Ѫ����������
    
    // SPO2 PARAM����
    unsigned char m_SPO2Status; // Ѫ��״̬
    unsigned char m_SPO2Sat;    // Ѫ�����Ͷ�
    unsigned char m_PulseRate;  // ����
    
    // TEMP����
    unsigned char m_TEMPStatus; // ����״̬
    double        m_BodyTemp1;   // ����1
    double        m_BodyTemp2;   // ����2

    // TXY����
    unsigned char m_TXYStatus;  // ̥����״̬
    unsigned char m_FHeartRate; // ̥����
    unsigned char m_UPress;     // ����ѹ

    // FGN����
    unsigned char m_FGNStatus;  // �ι���״̬
    unsigned int  m_LungVC;     // �λ���
    unsigned int  m_FLungVC;  // �����λ���
    
    // ECGSetupDlg��ر���
    unsigned char m_ECGMode;
    unsigned char m_ECGGain;
    unsigned char m_RESPGain;
    unsigned char m_ECGCmd;
	

    // NIBPSetupDlg��ر���
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
    afx_msg LRESULT OnCommRecv(WPARAM wParam, LPARAM lParam);	//ע�ᴮ����Ϣ������
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
