// PassbookMainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Passbook.h"
#include "PassbookMainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CPassbookMainDlg 对话框
IMPLEMENT_DYNAMIC(CPassbookMainDlg, CDialogEx)

CPassbookMainDlg::CPassbookMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPassbookMainDlg::IDD, pParent)
	, m_Type(_T(""))
	, m_Text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_IsNewModel = FALSE;
}
CPassbookMainDlg::~CPassbookMainDlg()
{
	
	if( m_Items.GetSize( ) > 0 )
		m_Items.RemoveAll( ) ;
}
void CPassbookMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TYPE, m_TypeList);
	DDX_Control(pDX, IDC_EDT_TYPE, m_TypeEdt);
	DDX_Control(pDX, IDC_EDT_TEXT, m_TextEdt);
	DDX_Control(pDX, IDC_BTN_NEW, m_NewBtn);
	DDX_Control(pDX, IDC_BTN_SAVE, m_SaveBtn);
	DDX_Text(pDX, IDC_EDT_TYPE, m_Type);
	DDX_Text(pDX, IDC_EDT_TEXT, m_Text);
}
BEGIN_MESSAGE_MAP(CPassbookMainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_NEW, &CPassbookMainDlg::OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CPassbookMainDlg::OnBnClickedBtnSave)
	ON_LBN_SELCHANGE(IDC_LIST_TYPE, &CPassbookMainDlg::OnLbnSelchangeListType)
END_MESSAGE_MAP()
BOOL CPassbookMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	
	// TODO: 在此添加额外的初始化代码
	SetWindowText(L"Passbook v1.0");
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
	//ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW,0);//任务栏隐藏


	LOG(L"%d",m_Sdk->GetCount());

	 //*********************
    // 设置字体
    m_Font.CreatePointFont(150,(LPCTSTR)_T("楷体_GB2312"));
	
	m_TypeList.SetFont(&m_Font,TRUE);
	m_TypeEdt.SetFont(&m_Font,TRUE);
	m_TextEdt.SetFont(&m_Font,TRUE);

	//
	Value* values=m_Sdk->GetValue();
	m_Sdk->Test();
	LOG(L"数量:%d \n", m_Sdk->GetCount());
	int i=0;
	for (i = 0; i < m_Sdk->GetCount();i++)
	{
		Value item=values[i];

		m_Items.Add(item);
	
		//倒序显示
		m_TypeList.InsertString(0,item.type);

	}
	m_TypeList.SetCurSel(0);
	OnLbnSelchangeListType();



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPassbookMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CPassbookMainDlg::OnPaint()
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
//************************************
// 方法名称: OnBnClickedBtnNew
// 创建日期: 2017/04/20
// 创 建 人: admin
// 函数说明: 新增按钮点击事件
// 返 回 值: void
//************************************
void CPassbookMainDlg::OnBnClickedBtnNew()
{
	// TODO: 在此添加控件通知处理程序代码
	Value value;
	m_Items.Add(value);
	m_TypeList.InsertString(0,L"新增");
	m_TypeList.SetCurSel(0);
	OnLbnSelchangeListType();//手动调用
	m_NewBtn.EnableWindow(FALSE);
	m_IsNewModel = TRUE;
}
//************************************
// 方法名称: OnBnClickedBtnSave
// 创建日期: 2017/04/20
// 创 建 人: admin
// 函数说明: 保存按钮点击事件
// 返 回 值: void
//************************************
void CPassbookMainDlg::OnBnClickedBtnSave()
{
	UpdateData(TRUE);
	int sel = m_TypeList.GetCurSel();

	int index = m_TypeList.GetCount()-1-sel;
	Value item = m_Items.GetAt(index);
	item.type = m_Type ;
	item.text = m_Text ;
	m_Items.SetAt(index,item);
	//刷新

	m_TypeList.DeleteString(sel);
	m_TypeList.InsertString(sel,m_Type);

	if(m_IsNewModel)//新增模式
	{
		m_IsNewModel = FALSE;
		m_NewBtn.EnableWindow(TRUE);
	}

	m_Sdk->SetValue(m_Items);
	//保存到文件
	m_Sdk->CreateFile(L"E:\\123.passwd");
}
//************************************
// 方法名称: OnLbnSelchangeListType
// 创建日期: 2017/04/20
// 创 建 人: admin
// 函数说明: List控件选择项改变的时候触发此事件
// 返 回 值: void
//************************************
void CPassbookMainDlg::OnLbnSelchangeListType()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_IsNewModel)
	{
		m_TypeList.SetCurSel(0);
		return ;
	}
	int sel = m_TypeList.GetCurSel();
	LOG(L"选择：%d \n",sel);
	//获取实际的索引值
	int index = m_TypeList.GetCount() - sel - 1;

	Value item = m_Items.GetAt(index);
	m_Type = item.type;
	m_Text = item.text;
	//刷新UI
	UpdateData(FALSE);
}
