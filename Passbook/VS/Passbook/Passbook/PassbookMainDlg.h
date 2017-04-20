#pragma once
#include "afxcmn.h"
#include "PasswordSdk.h"
#include "afxwin.h"




// CPassbookMainDlg 对话框

class CPassbookMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPassbookMainDlg)
// 构造
public:

	CPassbookMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPassbookMainDlg();
	// 对话框数据
	enum { IDD = IDD_DIALOG_MAIN };
// 实现
protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	

	DECLARE_MESSAGE_MAP()
public:
	 CFont m_Font;

	CListBox m_TypeList;

	CPasswordSdk *m_Sdk;

	CEdit m_TypeEdt;
	CEdit m_TextEdt;
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnSave();
	CButton m_NewBtn;
	CButton m_SaveBtn;

	bool m_IsNewModel;
	CArray<Value> m_Items;
	afx_msg void OnLbnSelchangeListType();
	CString m_Type;
	CString m_Text;
};
