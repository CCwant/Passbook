#include "stdafx.h"
#include "PasswordVerify.h"

// �ڴ�й¶��Ϣ����ʾ�ļ����ʹ����к�
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

	//Э��ǰ��
	char sign[6];
	memcpy(&sign,&magic,6);
	//Э��汾��
	char ver[3];
	memcpy(&ver,&magic[7],3);

	char src_sign[6];
	src_sign[0] = 'p';
	src_sign[1] = 'a';
	src_sign[2] = 's';
	src_sign[3] = 's';
	src_sign[4] = 'w';
	src_sign[5] = 'd';
	//У���ļ�Э��ǰ��
	if(sign[0] == src_sign[0] &&
		sign[1] == src_sign[1] &&
		sign[2] == src_sign[2] &&
		sign[3] == src_sign[3] &&
		sign[4] == src_sign[4] &&
		sign[5] == src_sign[5] &&
		sizeof(sign) == sizeof(src_sign) ){
		LOG(L"[�ļ�У��]�ļ�У��ɹ�. \n");
	}
	else
	{
		LOG(L"[�ļ�У��]�ļ�У��ʧ��. \n");
		return 1;
	}
	int sum = ver[0] + ver[1] + ver[2] - 3*'0';
	LOG(L"[�ļ�У��]�汾��У���: %d \n",sum);
	if(sum < 0){
		return 2;
	}
	int version =(ver[0] - '0')*100 + (ver[1] - '0')*10 + (ver[2] - '0') ;
	LOG(L"[�ļ�У��]�汾��: %d \n",version);
	if(version < 0 || version > 999){
		return 3;
	}
	if(version != PASSWD_VERSION){
		LOG(L"[�ļ�У��]�汾���޷�����. \n");
		return 4;
	}
	return 0;
}
