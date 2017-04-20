#include "stdafx.h"
#include "PasswordHandler.h"

// �ڴ�й¶��Ϣ����ʾ�ļ����ʹ����к�
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CPasswordHandler::CPasswordHandler(void)
{
}


CPasswordHandler::~CPasswordHandler(void)
{
	if(NULL != m_Password)
	{
		LOG(L"�ͷ� m_Password \n");
		delete[] m_Password;
	}
	
}
void CPasswordHandler::SetPassword(const char *password,int len)
{
	m_PasswordLen = len;
	m_Password = new char[len];
	memcpy(m_Password,password,len);
}


Code* CPasswordHandler::encode(char *data,int len)
{
	////����KEY

	//sha256����
	unsigned char digest[32];  
	mbedtls_sha256((unsigned char *)m_Password,m_PasswordLen, digest, 0); 
	//ȡǰ16���ַ�
	char key[16];
	memcpy(key,digest,16);

	//��������

	//���ܺ����ݳ���
	int destLen = 0;
	char *dest=AesEncode(key,&destLen,data,len);

	Code *code = new Code;
	code->data = dest;
	code->size = destLen;
	return code;
}
Code* CPasswordHandler::decode(char *data,int len)
{
	//sha256����
	unsigned char digest[32];  
	mbedtls_sha256((unsigned char *)m_Password,m_PasswordLen, digest, 0); 
	//ȡǰ16���ַ�
	char key[16];
	memcpy(key,digest,16);

	int destLen = 0;
	char *dest=AesDecode(key,&destLen,data,len);

	Code *code = new Code;
	code->data = dest;
	code->size = destLen;

	return code;
}

char* CPasswordHandler::AesEncode(char *key,int *destLen,char *src,int srcLen)
{
	mbedtls_aes_context aes_ctx; 
	mbedtls_aes_init( &aes_ctx );  
	//���ü�����Կ  
	mbedtls_aes_setkey_enc( &aes_ctx,(unsigned char *)key, 128);
	//��ȡ�������
	int block=srcLen/16+1;
	//��̬�����ڴ�
	*destLen = block*16;
	char *dest=new char[*destLen];
	//���
	memset(dest,0,*destLen);
	//�ֿ���ܣ�ÿ��16�ֽڳ���
	unsigned char input[16];
	unsigned char outout[16];

	int b = 0;
	while( b < block ){
		int offset = b * 16;
		int len = 0;
		if((srcLen-16-offset) > 0 ){
			len = 16;
		}else{
			len = srcLen-offset;
		}
		memset(input,0,16);
		memset(outout,0,16);
		memcpy(input,&src[offset],len);
		//����
		mbedtls_aes_crypt_ecb( &aes_ctx, MBEDTLS_AES_ENCRYPT, input, outout ); 
		memcpy(&dest[b*16],outout,16);
		b++;
	}
	return dest;
}
char* CPasswordHandler::AesDecode(char *key,int *destLen,char *src,int srcLen)
{
	mbedtls_aes_context aes_ctx; 
	mbedtls_aes_init( &aes_ctx );  
	//���ü�����Կ  
	mbedtls_aes_setkey_dec( &aes_ctx,(unsigned char *)key, 128);
	//��ȡ�������
	int block=srcLen/16+1;
	//��̬�����ڴ�
	*destLen = block*16;
	char *dest=new char[*destLen];
	//���
	memset(dest,0,*destLen);
	//�ֿ���ܣ�ÿ��16�ֽڳ���
	unsigned char input[16];
	unsigned char outout[16];

	int b = 0;
	while( b < block ){
		int offset = b * 16;
		int len = 0;
		if((srcLen-16-offset) > 0 ){
			len = 16;
		}else{
			len = srcLen-offset;
		}
	
		memset(input,0,16);
		memset(outout,0,16);
		memcpy(input,&src[offset],len);
		//����
		mbedtls_aes_crypt_ecb( &aes_ctx, MBEDTLS_AES_DECRYPT, input, outout ); 
		memcpy(&dest[b*16],outout,16);
		b++;
	}
	return dest;
}