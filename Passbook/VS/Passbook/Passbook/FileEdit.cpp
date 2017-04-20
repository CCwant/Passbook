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
	 int DropCount=DragQueryFile(hDropInfo,-1,NULL,0);//取得被拖动文件的数目  
	 for(int i=0;i< DropCount;i++)  
	 {  
		 WCHAR path[MAX_PATH];  
		 DragQueryFile(hDropInfo,i,path,MAX_PATH);//获得拖曳的第i个文件的文件名
		 m_FilePath.Format(L"%s",path);
		 SetWindowText(m_FilePath);
	 }
	 DragFinish(hDropInfo);  //拖放结束后,释放内存  
	 CEdit::OnDropFiles(hDropInfo);  
}