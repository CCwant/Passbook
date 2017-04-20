
// PassbookDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Passbook.h"
#include "PassbookDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPassbookDlg �Ի���



CPassbookDlg::CPassbookDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPassbookDlg::IDD, pParent)
	, m_Password(_T(""))
	, m_FilePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CPassbookDlg::~CPassbookDlg()
{
	//m_Sdk.Close();
}

void CPassbookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_FILE, m_FileEdit);
	DDX_Text(pDX, IDC_EDT_PASSWORD, m_Password);
	DDX_Text(pDX, IDC_EDT_FILE, m_FilePath);
}

BEGIN_MESSAGE_MAP(CPassbookDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CPassbookDlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()


// CPassbookDlg ��Ϣ�������
BOOL CPassbookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// ��ʼ��
	SetWindowText(L"Passbook v1.0");
	UpdateData(TRUE);
	
	m_FilePath =L"E:\\123.passwd";
	m_Password = L"12345678910";
	UpdateData(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
void CPassbookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPassbookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//************************************
// ��������: OnBnClickedBtnOpen
// ��������: 2017/04/18
// �� �� ��: admin
// ����˵��: Open��ť����¼�
// �� �� ֵ: void
//************************************
void CPassbookDlg::OnBnClickedBtnOpen()
{
	UpdateData(TRUE);
	if(m_FilePath.IsEmpty() || m_FilePath.GetLength() < 2){
		MessageBox(L"�ļ�·�����Ϸ�.");
		return ;
	}
	if(m_Password.IsEmpty() || m_Password.GetLength() < 2){
		MessageBox(L"���벻�Ϸ�.");
		return ;
	}
	m_Sdk.SetPassword(m_Password);
	int error = m_Sdk.OpenFile(m_FilePath);
	if(error == 1){
		int count= m_Sdk.GetCount();
		if (count > 0)
		{
			ShowWindow(SW_HIDE);
			m_MainDlg.m_Sdk = &m_Sdk;
			if (IDOK == m_MainDlg.DoModal())  
			{  
				Sleep(100);  
				ShowWindow(SW_SHOW);  
			}  
			else  
			{  
				OnOK();
			}  
		}
	}else if(error == 0){
		MessageBox(L"�������.");
	}else if(error == -1){
		MessageBox(L"�ļ��򿪴���.");
	}else if(error == -2){
		MessageBox(L"�ļ�У��ʧ��.");
	}else if(error == -3){
		MessageBox(L"�ļ�Э��汾�޷�����.");
	}else{
		MessageBox(L"δ֪�쳣.");
	}
}
