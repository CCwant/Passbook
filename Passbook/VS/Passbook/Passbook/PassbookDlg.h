
// PassbookDlg.h : 头文件
//

#pragma once
#include "PasswordSdk.h"
#include "afxwin.h"
#include "FileEdit.h"
#include "PassbookMainDlg.h"


// CPassbookDlg 对话框
class CPassbookDlg : public CDialogEx
{
// 构造
public:
	CPassbookDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CPassbookDlg();
// 对话框数据
	enum { IDD = IDD_PASSBOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLogin();
	CPassbookMainDlg  m_MainDlg;


	CPasswordSdk m_Sdk;
	CFileEdit m_FileEdit;
	CString m_Password;
	afx_msg void OnBnClickedBtnOpen();
	CString m_FilePath;
};
