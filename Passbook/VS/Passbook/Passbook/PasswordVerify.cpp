#include "stdafx.h"
#include "PasswordVerify.h"

// 内存泄露信息中显示文件名和代码行号
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPasswordVerify::CPasswordVerify(void)
{

}
CPasswordVerify::~CPasswordVerify(void)
{

}
int CPasswordVerify::IsPasswdFile(const char *data)
{
	u1 magic[12];
	memcpy(&magic,data,12);

	//协议前戳
	char sign[6];
	memcpy(&sign,&magic,6);
	//协议版本号
	char ver[3];
	memcpy(&ver,&magic[7],3);

	char src_sign[6];
	src_sign[0] = 'p';
	src_sign[1] = 'a';
	src_sign[2] = 's';
	src_sign[3] = 's';
	src_sign[4] = 'w';
	src_sign[5] = 'd';
	//校验文件协议前戳
	if(sign[0] == src_sign[0] &&
		sign[1] == src_sign[1] &&
		sign[2] == src_sign[2] &&
		sign[3] == src_sign[3] &&
		sign[4] == src_sign[4] &&
		sign[5] == src_sign[5] &&
		sizeof(sign) == sizeof(src_sign) ){
		LOG(L"[文件校验]文件校验成功. \n");
	}
	else
	{
		LOG(L"[文件校验]文件校验失败. \n");
		return 1;
	}
	int sum = ver[0] + ver[1] + ver[2] - 3*'0';
	LOG(L"[文件校验]版本号校验和: %d \n",sum);
	if(sum < 0){
		return 2;
	}
	int version =(ver[0] - '0')*100 + (ver[1] - '0')*10 + (ver[2] - '0') ;
	LOG(L"[文件校验]版本号: %d \n",version);
	if(version < 0 || version > 999){
		return 3;
	}
	if(version != PASSWD_VERSION){
		LOG(L"[文件校验]版本号无法解析. \n");
		return 4;
	}
	return 0;
}
