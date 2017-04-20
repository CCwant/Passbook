#pragma once
#include "afxcmn.h"
#include "PasswordSdk.h"
#include "afxwin.h"




// CPassbookMainDlg �Ի���

class CPassbookMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPassbookMainDlg)
// ����
public:

	CPassbookMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPassbookMainDlg();
	// �Ի�������
	enum { IDD = IDD_DIALOG_MAIN };
// ʵ��
protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	// ���ɵ���Ϣӳ�亯��
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
