#pragma once
#include "PasswordDefine.h"


class CPasswordVerify
{
public:
	CPasswordVerify(void);
	~CPasswordVerify(void);

	int IsPasswdFile(const char *data);
	
};

