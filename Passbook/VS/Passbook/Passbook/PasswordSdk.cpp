#include "stdafx.h"
#include "PasswordSdk.h"

// 内存泄露信息中显示文件名和代码行号
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CPasswordSdk::CPasswordSdk(void)
{
	m_Password.data = NULL;
}
CPasswordSdk::~CPasswordSdk(void)
{
	if(m_Password.data != NULL)
	{
		LOG(L"释放 m_Password.data  \n");
		delete[] m_Password.data;
	}
	/*int i = 0;
	for (i = 0; i<m_Count ;i++)
	{
	Value value = m_Value[i];
	delete[] &value.text;
	delete[] &value.type;
	}*/
	

}

int CPasswordSdk::OpenFile(CString path)
{
	USES_CONVERSION;
	const char *c_path=W2A(path);

	FILE *fp;
	fopen_s(&fp,c_path,"rb");
	if(fp == NULL)
	{
		return -1;
	}

	fseek(fp,0,SEEK_END);
	long fileSize = ftell(fp);
	fseek(fp,0,SEEK_SET);
	char *fileData=new char[fileSize];
	char *buffer = new char[1024]; 
	int size = 0;
	while(size < fileSize){
		int len = fread(buffer,sizeof(char),1024,fp);
		if(len > 0){
			memcpy(fileData,buffer,len);
		}
		size += len;
	}
	delete[] buffer; 
	fclose(fp);
	LOG(L"[SDK]文件大小: %d \n",fileSize);
	//Print(fileData,fileSize);
	int res = m_PasswordVerify.IsPasswdFile(fileData);
	if(res != 0)
	{
		if(res == 4)
		{
			return -3;
		}
		return -2;
	}
	//解析数据
	m_PassbookAgreement.SetValue(fileData,fileSize);
	delete[] fileData;
	//验证密码
	PasswordData data = m_PassbookAgreement.GetData();
	if(!strcmp(data.pass.data,m_Password.data)){
		LOG(L"[SDK]密码正确. \n");
	}else{
		LOG(L"[SDK]密码错误. \n");
		return 0;
	}
	Item *items = m_PassbookAgreement.GetItems();
	//获取大小
	m_Count = _msize(items)/sizeof(Item);
	int i = 0;
	for (i = 0; i<m_Count ;i++)
	{
		
		Value *value =new Value();
		Item item = items[i];

		//text
		Code *textCode = m_PasswordHandler.decode(item.text,item.textLen);
		//type
		Code *typeCode = m_PasswordHandler.decode(item.type,item.typeLen);

		value->type = UNCOIDE2UTF8(typeCode->data,typeCode->size);
		value->text = UNCOIDE2UTF8(textCode->data,textCode->size);

		m_Value[i] = *value;

		delete[] textCode->data;
		delete[] typeCode->data;
		delete textCode;
		delete typeCode;
		delete value;
	}
	delete[] items;
	return 1;
}
int CPasswordSdk::CreateFile(CString path)
{
	LOG(L"[SDK]CreateFile: %s \n",path);
	USES_CONVERSION;
	const char *c_path=W2A(path);

	//生成协议
	m_PassbookAgreement.Reset();//重置
	//设置密码
	m_PassbookAgreement.SetPassword(m_Password.data,m_Password.size);

	LOG(L"[SDK]写入数据数量:%d \n",m_Count);
	int i = 0;
	for (i = 0; i<m_Count ;i++)
	{
		Value *value= &m_Value[i];

		char* b_type = STCUTF8(value->type);
		char* b_text = STCUTF8(value->text);
		//加密
		Code *typeCode = m_PasswordHandler.encode(b_type,strlen(b_type));
		Code *textCode = m_PasswordHandler.encode(b_text,strlen(b_text));

		m_PassbookAgreement.Add(typeCode->data,typeCode->size,textCode->data,textCode->size);

		delete[] b_type;
		delete[] b_text;
		delete typeCode;
		delete textCode;
	}
	char *data = m_PassbookAgreement.GetValue();
	int size = m_PassbookAgreement.GetSize();
	LOG(L"[SDK]写入:%d \n",size);


	FILE *fp;
	fopen_s(&fp,c_path,"wb");
	if(fp == NULL)
	{
		return -1;
	}
	//写入文件
	fwrite(data,sizeof(char),size,fp);
	fclose(fp);

	delete[] data;
	return 0;
}
void CPasswordSdk::SetPassword(CString password)
{
	USES_CONVERSION;
	char* data=W2A(password);

	Print(data,password.GetLength());
	//(LPSTR)(LPCTSTR)
	m_PasswordHandler.SetPassword((char*)data,password.GetLength());
	//加密密码
	Code *code = m_PasswordHandler.encode((char*)data,password.GetLength());
	m_Password = *code;
	delete code;
}
void CPasswordSdk::SetValue(CArray<Value> &values)
{
	Clear();
	int i = 0;
	for (i = 0; i < values.GetCount();i++)
	{
		Value value = values.GetAt(i);
		Add(value.type,value.text);
	}
}
void CPasswordSdk::Clear()
{
	int i = 0;
	for (i = 0; i < GetCount();i++)
	{
		Value va=m_Value[i];
		va.text.ReleaseBuffer();
		va.type.ReleaseBuffer();
	}
	m_Count = 0;
}

void CPasswordSdk::Add(CString type,CString text)
{
	int index = m_Count++;
	m_Value[index].type = type;
	m_Value[index].text = text;
}

Value* CPasswordSdk::GetValue()
{
	/*Value* values=new Value[m_Count];
	int i = 0;
	for (i = 0; i<m_Count ;i++)
	{
	values[i] = m_Value[i];
	}*/
	return m_Value;
}
int CPasswordSdk::GetCount()
{
	return m_Count;
}
void CPasswordSdk::Test()
{
	//m_PassbookAgreement.Reset();
}

