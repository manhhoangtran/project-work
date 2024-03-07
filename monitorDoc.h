// monitorDoc.h : interface of the CMonitorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONITORDOC_H__9C0F4229_1695_40F9_86DA_81909851C4D3__INCLUDED_)
#define AFX_MONITORDOC_H__9C0F4229_1695_40F9_86DA_81909851C4D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMonitorDoc : public CDocument
{
protected: // create from serialization only
    CMonitorDoc();
    DECLARE_DYNCREATE(CMonitorDoc)

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMonitorDoc)
    public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CMonitorDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(CMonitorDoc)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITORDOC_H__9C0F4229_1695_40F9_86DA_81909851C4D3__INCLUDED_)
