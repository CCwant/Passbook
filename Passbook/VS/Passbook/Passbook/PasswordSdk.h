#pragma once
#include <Afxtempl.h>  
#include "PassbookAgreement.h"
#include "PasswordHandler.h"
#include "PasswordVerify.h"

struct Value {
	CString type;
	CString text;
};
class CPasswordSdk
{
public:
	CPasswordSdk(void);
	~CPasswordSdk(void);

	void Add(CString type,CString text);

	void SetPassword(CString password);

	int OpenFile(CString path);

	int CreateFile(CString path);

	Value* GetValue();

	void SetValue(CArray<Value> &values);

	void Clear();

	int GetCount();



	void Test();
private:
	Value m_Value[2000];
	int m_Count;
	////º”√‹∫Ûµƒ√‹¬Î
	Code m_Password;



	CPassbookAgreement m_PassbookAgreement;
	CPasswordHandler m_PasswordHandler;
	CPasswordVerify m_PasswordVerify;

};

