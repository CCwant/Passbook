// PassbookMainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Passbook.h"
#include "PassbookMainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CPassbookMainDlg �Ի���
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetWindowText(L"Passbook v1.0");
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
	//ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW,0);//����������


	LOG(L"%d",m_Sdk->GetCount());

	 //*********************
    // ��������
    m_Font.CreatePointFont(150,(LPCTSTR)_T("����_GB2312"));
	
	m_TypeList.SetFont(&m_Font,TRUE);
	m_TypeEdt.SetFont(&m_Font,TRUE);
	m_TextEdt.SetFont(&m_Font,TRUE);

	//
	Value* values=m_Sdk->GetValue();
	m_Sdk->Test();
	LOG(L"����:%d \n", m_Sdk->GetCount());
	int i=0;
	for (i = 0; i < m_Sdk->GetCount();i++)
	{
		Value item=values[i];

		m_Items.Add(item);
	
		//������ʾ
		m_TypeList.InsertString(0,item.type);

	}
	m_TypeList.SetCurSel(0);
	OnLbnSelchangeListType();



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPassbookMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void CPassbookMainDlg::OnPaint()
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
//************************************
// ��������: OnBnClickedBtnNew
// ��������: 2017/04/20
// �� �� ��: admin
// ����˵��: ������ť����¼�
// �� �� ֵ: void
//************************************
void CPassbookMainDlg::OnBnClickedBtnNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Value value;
	m_Items.Add(value);
	m_TypeList.InsertString(0,L"����");
	m_TypeList.SetCurSel(0);
	OnLbnSelchangeListType();//�ֶ�����
	m_NewBtn.EnableWindow(FALSE);
	m_IsNewModel = TRUE;
}
//************************************
// ��������: OnBnClickedBtnSave
// ��������: 2017/04/20
// �� �� ��: admin
// ����˵��: ���水ť����¼�
// �� �� ֵ: void
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
	//ˢ��

	m_TypeList.DeleteString(sel);
	m_TypeList.InsertString(sel,m_Type);

	if(m_IsNewModel)//����ģʽ
	{
		m_IsNewModel = FALSE;
		m_NewBtn.EnableWindow(TRUE);
	}

	m_Sdk->SetValue(m_Items);
	//���浽�ļ�
	m_Sdk->CreateFile(L"E:\\123.passwd");
}
//************************************
// ��������: OnLbnSelchangeListType
// ��������: 2017/04/20
// �� �� ��: admin
// ����˵��: List�ؼ�ѡ����ı��ʱ�򴥷����¼�
// �� �� ֵ: void
//************************************
void CPassbookMainDlg::OnLbnSelchangeListType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_IsNewModel)
	{
		m_TypeList.SetCurSel(0);
		return ;
	}
	int sel = m_TypeList.GetCurSel();
	LOG(L"ѡ��%d \n",sel);
	//��ȡʵ�ʵ�����ֵ
	int index = m_TypeList.GetCount() - sel - 1;

	Value item = m_Items.GetAt(index);
	m_Type = item.type;
	m_Text = item.text;
	//ˢ��UI
	UpdateData(FALSE);
}
