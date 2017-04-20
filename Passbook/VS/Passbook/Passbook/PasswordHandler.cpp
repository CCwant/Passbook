#include "stdafx.h"
#include "PasswordHandler.h"

// 内存泄露信息中显示文件名和代码行号
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
		LOG(L"释放 m_Password \n");
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
	////处理KEY

	//sha256加密
	unsigned char digest[32];  
	mbedtls_sha256((unsigned char *)m_Password,m_PasswordLen, digest, 0); 
	//取前16个字符
	char key[16];
	memcpy(key,digest,16);

	//加密数据

	//加密后数据长度
	int destLen = 0;
	char *dest=AesEncode(key,&destLen,data,len);

	Code *code = new Code;
	code->data = dest;
	code->size = destLen;
	return code;
}
Code* CPasswordHandler::decode(char *data,int len)
{
	//sha256加密
	unsigned char digest[32];  
	mbedtls_sha256((unsigned char *)m_Password,m_PasswordLen, digest, 0); 
	//取前16个字符
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
	//设置加密密钥  
	mbedtls_aes_setkey_enc( &aes_ctx,(unsigned char *)key, 128);
	//获取块的数量
	int block=srcLen/16+1;
	//动态分配内存
	*destLen = block*16;
	char *dest=new char[*destLen];
	//清空
	memset(dest,0,*destLen);
	//分块加密，每块16字节长度
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
		//加密
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
	//设置加密密钥  
	mbedtls_aes_setkey_dec( &aes_ctx,(unsigned char *)key, 128);
	//获取块的数量
	int block=srcLen/16+1;
	//动态分配内存
	*destLen = block*16;
	char *dest=new char[*destLen];
	//清空
	memset(dest,0,*destLen);
	//分块加密，每块16字节长度
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
		//解密
		mbedtls_aes_crypt_ecb( &aes_ctx, MBEDTLS_AES_DECRYPT, input, outout ); 
		memcpy(&dest[b*16],outout,16);
		b++;
	}
	return dest;
}