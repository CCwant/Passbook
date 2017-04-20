#include "stdafx.h"

#define countof(x) (sizeof((x)) / sizeof(x)[0])
#define LOG CLog

class CLog
{
public:
	CLog(LPCWSTR pszFormat,...){

		va_list argList;
		va_start( argList, pszFormat );
		
		CString message;
		message.FormatV(pszFormat,argList);
		OutputDebugString(message);

		va_end( argList );
	}

};

inline void Print(const char *data,int len)
{
	int i = 0;
	for (i=0;i<len;i++)
	{
		LOG(L"%d ",data[i]);
	}
	LOG(L"\n");

}
inline void PrintHex(const char *data,int len)
{
	int i = 0;
	for (i=0;i<len;i++)
	{
		LOG(L"%x ",data[i]);
	}
	LOG(L"\n");

}
inline CString UNCOIDE2UTF8(char* data,int len)  
{  
	if (NULL == data)  
	{  
		return FALSE;  
	}  
	//pUTF8Text=CatChar(pUTF8Text,len);
	int  unicodeLen = ::MultiByteToWideChar( CP_UTF8,  
		0,  
		data,  
		len,  
		NULL,  
		0 );   
	wchar_t*  pUnicode = new  wchar_t[unicodeLen+1];  
	if (NULL == pUnicode)  
	{  
		return FALSE;  
	}  

	MultiByteToWideChar( CP_UTF8, 0, data, len, (LPWSTR)pUnicode, unicodeLen );  

	CString text = pUnicode;  
	//ɾ�����������
	text.Delete(unicodeLen,text.GetLength()-unicodeLen);

	delete []pUnicode;  
	return text;  
}  
inline wchar_t* UTF82UNICODE(const char* utf)  
{  
	if(!utf || !strlen(utf))  
	{  
		return NULL;  
	}  
	int dwUnicodeLen = MultiByteToWideChar(CP_UTF8,0,utf,-1,NULL,0);  
	size_t num = dwUnicodeLen*sizeof(wchar_t);  
	//wchar_t *pwText = (wchar_t*)malloc(num); 
	wchar_t *pwText = new wchar_t[num];
	memset(pwText,0,num);  
	MultiByteToWideChar(CP_UTF8,0,utf,-1,pwText,dwUnicodeLen);  
	return pwText;  
}  
inline char* STCUTF8(CString strValue)  
{  
	char *buffer = NULL;  
	int  length;  

#ifdef _UNICODE  
	length = WideCharToMultiByte(CP_UTF8, 0, strValue, -1, NULL, 0, NULL, NULL);  
#else  
	return NULL;  
#endif  
	if (length <= 0)  
	{  
		return NULL;  
	}  

	buffer = new char[length];  
	if (buffer == NULL)  
	{  
		return NULL;  
	}  

	ZeroMemory(buffer, length);  

#ifdef _UNICODE  
	WideCharToMultiByte(CP_UTF8, 0, strValue, -1, buffer, length, NULL, NULL);  
#else  
	strcpy_s(buffer, length, strValue);  
#endif  

	return buffer;  
}  
inline int UTF8LEN(const char* utf)  
{
	return MultiByteToWideChar(CP_UTF8,0,utf,-1,NULL,0)*sizeof(wchar_t); 
}
inline char * S2C(CString text){
 
	int n = text.GetLength(); //��ȡstr���ַ���  
	int len = WideCharToMultiByte(CP_ACP, 0, text.GetBuffer(text.GetLength()), n, NULL, 0, NULL, NULL); //��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����  
	LOG(L"���ֽڳ��ȣ� %d \n",len);
	char *pChar = new char[len + 1]; //���ֽ�Ϊ��λ  
	WideCharToMultiByte(CP_ACP, 0, text, n, pChar, len, NULL, NULL); //���ֽڱ���ת���ɶ��ֽڱ���  
	pChar[len + 1] = '\0'; //���ֽ��ַ���'\0'����  

	
	return pChar;
}
inline CString C2S(char *data){

	//��char����ת��Ϊwchar_t����  
	int charLen = strlen(data); //����pChar��ָ����ַ�����С�����ֽ�Ϊ��λ��һ������ռ�����ֽ�  
	int len = MultiByteToWideChar(CP_ACP, 0, data, charLen, NULL, 0); //������ֽ��ַ��Ĵ�С�����ַ�����  
	wchar_t *pWChar = new wchar_t[len + 1]; //Ϊ���ֽ��ַ�������ռ䣬  
	MultiByteToWideChar(CP_ACP, 0, data, charLen, pWChar, len); //���ֽڱ���ת���ɿ��ֽڱ���  
	pWChar[len] = '\0';  

	return pWChar;
}

