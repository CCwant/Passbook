#include "stdafx.h"
#include "FileEdit.h"

IMPLEMENT_DYNAMIC(CFileEdit, CEdit)

CFileEdit::CFileEdit(void)
{
}


CFileEdit::~CFileEdit(void)
{
}
BEGIN_MESSAGE_MAP(CFileEdit, CEdit)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()
void CFileEdit::OnDropFiles(HDROP hDropInfo)
{
	 int DropCount=DragQueryFile(hDropInfo,-1,NULL,0);//ȡ�ñ��϶��ļ�����Ŀ  
	 for(int i=0;i< DropCount;i++)  
	 {  
		 WCHAR path[MAX_PATH];  
		 DragQueryFile(hDropInfo,i,path,MAX_PATH);//�����ҷ�ĵ�i���ļ����ļ���
		 m_FilePath.Format(L"%s",path);
		 SetWindowText(m_FilePath);
	 }
	 DragFinish(hDropInfo);  //�ϷŽ�����,�ͷ��ڴ�  
	 CEdit::OnDropFiles(hDropInfo);  
}