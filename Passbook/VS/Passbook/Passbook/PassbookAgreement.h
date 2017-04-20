#pragma once

#include "PasswordDefine.h"
#include "sha1.h"


#pragma comment(lib,"mbedTLS.lib")


//password结构
struct Pass {
	u4 size;
	char *data;
};


//item结构
struct Item
{
	u4 typeLen;
	char *type;
	u4 textLen;
	char *text;
};
//item包装结构
struct MapItem{
	u4 size;
	Item item;
};
//data结构
struct PasswordData{
	Pass pass;
	u4 count;
	MapItem items[2000];
};
//header结构 48大小
struct PasswdHeader {
	u1  magic[12];       //版本号
	u4  checksum;       //校验和 计算文件中checksum字段之后（16字节之后）的数据
	u1  signature[20];  //文件sha1 签名signature字段之后的数据（36字节之后）
	u4  fileSize;       //整个文件的大小
	u4  headerSize;     //header结构本身占用的字节数
	u4  dataSize;       //data结构本身占用的字节数
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

	//翻转字符串
	char* Reversal(char* text);

	void CreateHeader();
	char* CreateChecksum();
	char* CreateSignature();
};

