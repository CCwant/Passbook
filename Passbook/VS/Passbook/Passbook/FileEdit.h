#pragma once
#include "afxwin.h"
class CFileEdit :public CEdit
{
	DECLARE_DYNAMIC(CFileEdit)
public:
	CFileEdit(void);
	~CFileEdit(void);

	afx_msg void OnDropFiles(HDROP hDropInfo);
protected:
	DECLARE_MESSAGE_MAP()

public:
	CString m_FilePath;
	CString getFilePath();
};

