#pragma once

#include "PasswordDefine.h"
#include "sha1.h"


#pragma comment(lib,"mbedTLS.lib")


//password�ṹ
struct Pass {
	u4 size;
	char *data;
};


//item�ṹ
struct Item
{
	u4 typeLen;
	char *type;
	u4 textLen;
	char *text;
};
//item��װ�ṹ
struct MapItem{
	u4 size;
	Item item;
};
//data�ṹ
struct PasswordData{
	Pass pass;
	u4 count;
	MapItem items[2000];
};
//header�ṹ 48��С
struct PasswdHeader {
	u1  magic[12];       //�汾��
	u4  checksum;       //У��� �����ļ���checksum�ֶ�֮��16�ֽ�֮�󣩵�����
	u1  signature[20];  //�ļ�sha1 ǩ��signature�ֶ�֮������ݣ�36�ֽ�֮��
	u4  fileSize;       //�����ļ��Ĵ�С
	u4  headerSize;     //header�ṹ����ռ�õ��ֽ���
	u4  dataSize;       //data�ṹ����ռ�õ��ֽ���
};
class CPassbookAgreement
{
public:
	CPassbookAgreement(void);
	~CPassbookAgreement(void);

	void SetPassword(char *password,int len);
	void Add(char *typeName,int typeNameLen,char *text,int textLen);
	void Reset();
	char* GetValue();
	int GetSize();
	void SetValue(const char* data,const int len);
	PasswordData GetData();
	Item *GetItems();
	int GetCount();
private:
	PasswdHeader m_Header;
	PasswordData m_Data;

	char* ToChar(PasswdHeader *header);
	char* ToChar(Item *item);
	char* ToChar(MapItem *item);
	char* ToChar(PasswordData *item);
	
	int getLength(Item *item);
	int getLength(MapItem *item);
	int getLength(PasswordData *item);

	//��ת�ַ���
	char* Reversal(char* text);

	void CreateHeader();
	char* CreateChecksum();
	char* CreateSignature();
};

