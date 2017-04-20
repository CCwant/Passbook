
// PassbookDlg.h : ͷ�ļ�
//

#pragma once
#include "PasswordSdk.h"
#include "afxwin.h"
#include "FileEdit.h"
#include "PassbookMainDlg.h"


// CPassbookDlg �Ի���
class CPassbookDlg : public CDialogEx
{
// ����
public:
	CPassbookDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CPassbookDlg();
// �Ի�������
	enum { IDD = IDD_PASSBOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
