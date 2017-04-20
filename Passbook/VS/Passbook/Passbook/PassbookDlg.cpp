
// PassbookDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Passbook.h"
#include "PassbookDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPassbookDlg 对话框



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


// CPassbookDlg 消息处理程序
BOOL CPassbookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 初始化
	SetWindowText(L"Passbook v1.0");
	UpdateData(TRUE);
	
	m_FilePath =L"E:\\123.passwd";
	m_Password = L"12345678910";
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CPassbookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPassbookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//************************************
// 方法名称: OnBnClickedBtnOpen
// 创建日期: 2017/04/18
// 创 建 人: admin
// 函数说明: Open按钮点击事件
// 返 回 值: void
//************************************
void CPassbookDlg::OnBnClickedBtnOpen()
{
	UpdateData(TRUE);
	if(m_FilePath.IsEmpty() || m_FilePath.GetLength() < 2){
		MessageBox(L"文件路径不合法.");
		return ;
	}
	if(m_Password.IsEmpty() || m_Password.GetLength() < 2){
		MessageBox(L"密码不合法.");
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
		MessageBox(L"密码错误.");
	}else if(error == -1){
		MessageBox(L"文件打开错误.");
	}else if(error == -2){
		MessageBox(L"文件校验失败.");
	}else if(error == -3){
		MessageBox(L"文件协议版本无法解析.");
	}else{
		MessageBox(L"未知异常.");
	}
}
