#pragma once

#include "PasswordDefine.h"
#include "sha1.h"
#include "sha256.h"
#include "aes.h"

#pragma comment(lib,"mbedTLS.lib")


struct Code {
	u4 size;
	char *data;
};

/************************************************************************/
/* �������ݴ���                                                         */
/************************************************************************/
class CPasswordHandler
{
public:
	CPasswordHandler(void);
	~CPasswordHandler(void);

	void SetPassword(const char *password,int len);

	//��������
	Code* encode(char *data,int len);
	Code* decode(char *data,int len);
private:
	char *m_Password;
	int m_PasswordLen;

	char* AesEncode(char *key,int *destLen,char *src,int srcLen);
	char* AesDecode(char *key,int *destLen,char *src,int srcLen);


};

