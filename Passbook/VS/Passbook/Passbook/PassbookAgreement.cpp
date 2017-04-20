#include "stdafx.h"
#include "PassbookAgreement.h"
#include "Adler32.h"

// 内存泄露信息中显示文件名和代码行号
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CPassbookAgreement::CPassbookAgreement(void)
{
	m_Data.count = 0;
}
CPassbookAgreement::~CPassbookAgreement(void)
{
	if(m_Data.count!=NULL){

		int count = m_Data.count;
		if(count > 0)
		{
			LOG(L"释放 m_Data \n");
			int i = 0;
			for (i = 0 ;i< count;i++)
			{

				delete[] m_Data.items[i].item.type;
				delete[] m_Data.items[i].item.text;
			}
			//
		}
		delete[] m_Data.pass.data;
		LOG(L"释放结束. \n");
	}
}

void CPassbookAgreement::SetPassword(char *password,int len)
{
	//释放之前保存的密码
	delete[] m_Data.pass.data;

	m_Data.pass.size = len;

	//重新初始化
	m_Data.pass.data = new char[len];
	memcpy(m_Data.pass.data,password,len);
}
//************************************
// 方法名称: ToChar
// 创建日期: 2017/04/13
// 创 建 人: admin
// 函数说明: data结构转char
// 函数参数: MapListData * item
// 返 回 值: char*
//************************************
char* CPassbookAgreement::ToChar(PasswordData *item)
{
	//存加密后的密码


	//总长度
	int len=getLength(item);
	//总数据
	char *dest=new char[len];
	//清空
	memset(dest,0,len);

	int offset = 0;
	int size = 0;
	//password-size
	char * temp1 = Reversal((char*)&m_Data.pass.size);
	size = 4;
	memcpy(&dest[offset],temp1,size);
	offset += size;
	delete[] temp1;
	//password-data
	size = m_Data.pass.size;
	memcpy(&dest[offset],m_Data.pass.data,size);
	offset += size;

	//count
	char * temp2 = Reversal((char*)&item->count);
	size = sizeof(temp2);
	memcpy(&dest[offset],temp2,size);
	offset += size;
	delete[] temp2;
	//item
	int count = item->count;
	int i = 0;
	for(i = 0;i < count; i++)
	{
		char * temp =ToChar(&item->items[i]);
		size =getLength(&item->items[i]);
		memcpy(&dest[offset],temp,size);
		offset += size;
		delete[] temp;
	}
	return dest;
}
//************************************
// 方法名称: ToChar
// 创建日期: 2017/04/13
// 创 建 人: admin
// 函数说明: item包装结构转char
// 函数参数: MapItem * item
// 返 回 值: char*
//************************************
char* CPassbookAgreement::ToChar(MapItem *mapItem){
	//总长度
	int len=getLength(mapItem);
	//总数据
	char *dest=new char[len];
	//清空
	memset(dest,0,len);
	//size
	int offset = 0;
	int size = 0;
	char * temp1 = Reversal((char*)&mapItem->size);
	size = sizeof(temp1);
	memcpy(&dest[offset],temp1,size);
	offset += size;
	delete[] temp1;
	//TextItem
	size = mapItem->size;
	char *item = ToChar(&mapItem->item);
	memcpy(&dest[offset],item,size);
	delete[] item;
	offset += size;

	return dest;
}
//************************************
// 方法名称: ToChar
// 创建日期: 2017/04/13
// 创 建 人: admin
// 函数说明: item结构转char
// 函数参数: TextItem * item
// 返 回 值: char*
//************************************
char* CPassbookAgreement::ToChar(Item *item)
{
	//总长度
	int len=getLength(item);
	//总数据
	char *dest=new char[len];
	//清空
	memset(dest,0,len);
	
	int offset = 0;
	int size = 0;
	//typeNameLen
	char * temp1 = Reversal((char*)&item->typeLen);
	size = sizeof(temp1);
	memcpy(&dest[offset],temp1,size);
	offset += size;
	delete[] temp1;
	//typeName
	size = item->typeLen;
	memcpy(&dest[offset],item->type,size);
	offset += size;
	//textLen
	char * temp2 = Reversal((char*)&item->textLen);
	size = sizeof(temp2);
	memcpy(&dest[offset],temp2,size);
	offset += size;
	delete[] temp2;
	//text
	size = item->textLen;
	memcpy(&dest[offset],item->text,size);
	offset += size;

	return dest;
}
//************************************
// 方法名称: ToChar
// 创建日期: 2017/04/18
// 创 建 人: admin
// 函数说明: Header结构转char
// 函数参数: PasswdHeader * header
// 返 回 值: char*
//************************************
char* CPassbookAgreement::ToChar(PasswdHeader *header)
{
	//总长度
	int len=48;
	//总数据
	char *dest=new char[len];
	//清空
	memset(dest,0,len);
	int offset = 0;
	int size = 0;
	//magic
	size = sizeof(header->magic);
	memcpy(&dest[offset],header->magic,size);
	offset += size;
	//checksum
	size = sizeof(header->checksum);
	memcpy(&dest[offset],&header->checksum,size);
	offset += size;
	//signature
	size = sizeof(header->signature);
	memcpy(&dest[offset],header->signature,size);
	offset += size;
	//fileSize
	size = sizeof(header->fileSize);
	memcpy(&dest[offset],&header->fileSize,size);
	offset += size;
	//headerSize
	size = sizeof(header->headerSize);
	memcpy(&dest[offset],&header->headerSize,size);
	offset += size;
	//dataSize
	size = sizeof(header->dataSize);
	memcpy(&dest[offset],&header->dataSize,size);
	offset += size;



	Print(dest,len);
	return dest;
}
//************************************
// 方法名称: getLength
// 创建日期: 2017/04/13
// 创 建 人: admin
// 函数说明: 获取data结构总长度
// 函数参数: MapListData * item
// 返 回 值: int
//************************************
int CPassbookAgreement::getLength(PasswordData *item)
{
	int size=item->count;
	int len=0;
	int i=0;
	for(i = 0;i < size; i++)
	{
		len+=getLength(&item->items[i]);
	}
	return len + 4 + m_Data.pass.size + 4;
}
//************************************
// 方法名称: getLength
// 创建日期: 2017/04/13
// 创 建 人: admin
// 函数说明: 获取item包装结构总长度
// 函数参数: MapItem * item
// 返 回 值: int
//************************************
int CPassbookAgreement::getLength(MapItem *item)
{
	return item->size + 4;;
}
//************************************
// 方法名称: getLength
// 创建日期: 2017/04/13
// 创 建 人: admin
// 函数说明: 获取Item结构总长度
// 函数参数: TextItem * item
// 返 回 值: int
//************************************
int CPassbookAgreement::getLength(Item *item)
{
	return item->textLen + item->typeLen+8;;
}
//************************************
// 方法名称: Reversal
// 创建日期: 2017/04/13
// 创 建 人: admin
// 函数说明: 翻转字符数组
// 函数参数: char * text
// 返 回 值: char*
//************************************
char* CPassbookAgreement::Reversal(char* text)
{
	size_t length = sizeof(text);
	char *temp = new char[length];
	int p = length-1;
	for (size_t i = 0; i <length; i++)
	{
		temp[i] = text[p];
		p--;
	}
	return temp;
}
//************************************
// 方法名称: CreateHeader
// 创建日期: 2017/04/18
// 创 建 人: admin
// 函数说明: 生成Header
// 返 回 值: void
//************************************
void CPassbookAgreement::CreateHeader()
{
	//协议版本号
	int c_version = 48;
	//从下往上计算
	int c_dataSize = getLength(&m_Data);
	int c_headerSize = 48;
	int c_fileSize = c_dataSize + c_headerSize;

	//协议前戳
	char *sign="passwd";
	char ver[4];
	char *flag=new char[1];
	//将版本号逐位转char
	sprintf_s(ver,"%03d",c_version);
	//初始化标志位
	flag[0] = (char)0x0A;
	//校验和
	char *s_fileSize=new char[4];
	char *s_headerSize=new char[4];
	char *s_dataSize=new char[4];

	memcpy(s_fileSize,&c_fileSize,sizeof(int));
	memcpy(s_headerSize,&c_headerSize,sizeof(int));
	memcpy(s_dataSize,&c_dataSize,sizeof(int));

	char *fileSize=Reversal(s_fileSize);
	char *headerSize=Reversal(s_headerSize);
	char *dataSize=Reversal(s_dataSize);

	delete[] s_fileSize;
	delete[] s_headerSize;
	delete[] s_dataSize;

	LOG(L"版本号:%d \n",c_version);
	LOG(L"FILE大小:%d \n",c_fileSize);
	LOG(L"HEADER大小:%d \n",c_headerSize);
	LOG(L"DATA大小:%d \n",c_dataSize);



	int size = 0;
	int offset = 0;

	memset(m_Header.magic,0,12);
	//magic-sign
	size = strlen(sign);
	memcpy(&m_Header.magic[offset],sign,size);
	offset += size;
	//magic-flag
	size = 1;
	memcpy(&m_Header.magic[offset],flag,size);
	offset += size;
	//magic-ver
	size =4;
	memcpy(&m_Header.magic[offset],ver,size);
	offset += size;
	//checksum 
	size = 4;
	//跳过;
	offset += size;
	//fileSize
	size =4;
	memcpy(&m_Header.fileSize,fileSize,size);
	//headerSize
	size =4;
	memcpy(&m_Header.headerSize,headerSize,size);
	//dataSize
	size =4;
	memcpy(&m_Header.dataSize,dataSize,size);
	//signature
	size = 20;
	char * signature = CreateSignature();
	memcpy(&m_Header.signature,signature,size);
	delete[] signature;
	//checksum
	size = 4;
	char * checksum = CreateChecksum();
	memcpy(&m_Header.checksum,checksum,size);
	delete[] checksum;

	delete[] flag;
	delete[] fileSize;
	delete[] headerSize;
	delete[] dataSize;
}
//************************************
// 方法名称: CreateSignature
// 创建日期: 2017/04/18
// 创 建 人: admin
// 函数说明: 获取文件签名
// 返 回 值: char*
//************************************
char* CPassbookAgreement::CreateSignature()
{
	LOG(L"[Agreement]计算签名[开始] \n");
	//data区数据
	char * data = ToChar(&m_Data);
	//data区长度
	int dataLen = getLength(&m_Data);
	//总长度
	int len = dataLen + 12;
	//总数据
	char *dest=new char[len];
	//清空
	memset(dest,0,len);

	int size = 0;
	int offset = 0;

	//fileSize
	size = 4;
	memcpy(&dest[offset],&m_Header.fileSize,size);
	offset += size;
	//headerSize
	size = 4;
	memcpy(&dest[offset],&m_Header.headerSize,size);
	offset += size;
	//dataSize
	size = 4;
	memcpy(&dest[offset],&m_Header.dataSize,size);
	offset += size;
	//data
	size = dataLen;
	memcpy(&dest[offset],data,size);
	offset += size;

	char *signature=new char[20];
	mbedtls_sha1((unsigned char *)dest,len,(unsigned char *)signature);

	delete[] data;
	delete[] dest;

	Print(signature,20);
	PrintHex(signature,20);
	LOG(L"[Agreement]计算签名[结束] \n");
	return signature;
}
//************************************
// 方法名称: CreateChecksum
// 创建日期: 2017/04/18
// 创 建 人: admin
// 函数说明: 获取校验和
// 返 回 值: char*
//************************************
char* CPassbookAgreement::CreateChecksum()
{
	LOG(L"[Agreement]计算校验和[开始] \n");
	//data区数据
	char * data = ToChar(&m_Data);
	//data区长度
	int dataLen = getLength(&m_Data);
	Print(data,dataLen);
	//总长度
	int len = dataLen + 32;
	//总数据
	char *dest=new char[len];
	//清空
	memset(dest,0,len);

	int size = 0;
	int offset = 0;
	//signature
	size = 20;
	memcpy(&dest[offset],m_Header.signature,size);
	offset += size;
	//fileSize
	size = 4;
	memcpy(&dest[offset],&m_Header.fileSize,size);
	offset += size;
	//headerSize
	size = 4;
	memcpy(&dest[offset],&m_Header.headerSize,size);
	offset += size;
	//dataSize
	size = 4;
	memcpy(&dest[offset],&m_Header.dataSize,size);
	offset += size;
	//data
	size = dataLen;
	memcpy(&dest[offset],data,size);
	offset += size;

	LOG(L"[Agreement]校验和数据长度:%d \n",len);
	Adler32 adler32;
	adler32.Update(dest,len);
	long value=adler32.getValue();
	LOG(L"[Agreement]校验和:%lu \n",value);

	//checksum
	char *s_checksum=new char[4];
	memcpy(s_checksum,&value,sizeof(long));
	char *checksum=Reversal(s_checksum);

	Print(checksum,4);
	LOG(L"[Agreement]计算校验和[结束] \n");

	delete[] s_checksum;
	delete[] data;
	delete[] dest;
	return checksum;
}
//************************************
// 方法名称: GetSize
// 创建日期: 2017/04/18
// 创 建 人: admin
// 函数说明: 获取数据大小
// 返 回 值: int
//************************************
int CPassbookAgreement::GetSize()
{
	//data区长度
	int dataLen = getLength(&m_Data);
	//总长度 = header + data;
	return dataLen + 48;
}
//************************************
// 方法名称: GetValue
// 创建日期: 2017/04/18
// 创 建 人: admin
// 函数说明: 获取数据
// 返 回 值: char*
//************************************
char* CPassbookAgreement::GetValue()
{
	LOG(L"[Agreement]开始创建.\n");
	//创建Header
	CreateHeader();
	//data区长度
	int dataLen = getLength(&m_Data);
	//总长度 = header + data;
	int len = dataLen + 48;
	LOG(L"[Agreement]生成文件大小: %d \n",len);
	//总数据
	char *dest=new char[len];
	//清空
	memset(dest,0,len);

	int size = 0;
	int offset = 0;
	//header
	char *header = ToChar(&m_Header);
	size = 48;
	memcpy(&dest[offset],header,size);
	delete header;
	offset += size;
	//date
	char *data = ToChar(&m_Data);
	size = dataLen;
	memcpy(&dest[offset],data,size);
	delete data;
	offset += size;

	Print(dest,len);
	LOG(L"[Agreement]创建完成. \n");
	return dest;
}
//************************************
// 方法名称: SetValue
// 创建日期: 2017/04/18
// 创 建 人: admin
// 函数说明: 设置数据
// 函数参数: const char * data
// 函数参数: const int len
// 返 回 值: void
//************************************
void CPassbookAgreement::SetValue(const char* data,const int len)
{
	LOG(L"[Agreement]开始解析.\n");

	

	int size = 0;
	int offset = 0;
	char *u4temp = new char[4];
	char *datatemp = NULL;
	int count = 0;
	int i = 0;
	//magic
	size = 12;
	memcpy(m_Header.magic,&data[offset],size);
	offset += size;
	//checksum
	size = 4;
	memcpy(u4temp,&data[offset],size);
	m_Header.checksum = C2I(u4temp);
	//delete[] temp;
	offset += size;
	LOG(L"[Agreement]校验和:%d   \n",m_Header.checksum);
	//signature
	size = 20;
	memcpy(m_Header.signature,&data[offset],size);
	offset += size;
	//fileSize
	size = 4;
	memcpy(u4temp,&data[offset],size);
	offset += size;
	m_Header.fileSize = C2I(u4temp);
	LOG(L"[Agreement]文件大小:%d   \n",m_Header.fileSize);
	//headerSize
	size = 4;
	memcpy(u4temp,&data[offset],size);
	m_Header.headerSize = C2I(u4temp);
	offset += size;
	//dataSize
	size = 4;
	memcpy(u4temp,&data[offset],size);
	m_Header.dataSize = C2I(u4temp);
	offset += size;

	
	//pass-len
	size = 4;
	memcpy(u4temp,&data[offset],size);
	m_Data.pass.size = C2I(u4temp);
	offset += size;

	//pass-data
	size = m_Data.pass.size;
	m_Data.pass.data = new char[size];//初始化内存
	memcpy(m_Data.pass.data,const_cast<char*>(&data[offset]),size);
	offset += size;
	
	//count
	size = 4;
	memcpy(u4temp,&data[offset],size);
	m_Data.count = C2I(u4temp);
	offset += size;
	
	count = m_Data.count;
	//MapItem
	for (i = 0 ;i< count;i++)
	{
		int off = 0;
		//size
		size = 4;
		memcpy(u4temp,&data[offset],size);
		m_Data.items[i].size = C2I(u4temp);
		offset += size;

		//data
		size =m_Data.items[i].size;
		datatemp = new char[size];
		memcpy(datatemp,&data[offset],size);
		offset += size;

		//TextItem-typeNameLen
		size = 4;
		memcpy(u4temp,&datatemp[off],size);
		m_Data.items[i].item.typeLen = C2I(u4temp);
		off += size;

		//TextItem-typeName
		size =m_Data.items[i].item.typeLen;
		m_Data.items[i].item.type = new char[size];//初始化内存
		memcpy(m_Data.items[i].item.type,&datatemp[off],size);
		off += size;

		//TextItem-textLen
		size = 4;
		memcpy(u4temp,&datatemp[off],size);
		m_Data.items[i].item.textLen = C2I(u4temp);
		off += size;

		//TextItem-text
		size =m_Data.items[i].item.textLen;
		m_Data.items[i].item.text = new char[size];//初始化内存
		memcpy(m_Data.items[i].item.text,&datatemp[off],size);
		off += size;

		delete[] datatemp;
	}
	delete[] u4temp;
	LOG(L"[Agreement]解析完成.\n");
}
//************************************
// 方法名称: GetData
// 创建日期: 2017/04/18
// 创 建 人: admin
// 函数说明: 获取数据区数据
// 返 回 值: PasswordData
//************************************
PasswordData CPassbookAgreement::GetData()
{
	return m_Data;
}
//************************************
// 方法名称: GetItems
// 创建日期: 2017/04/18
// 创 建 人: admin
// 函数说明: 获取所有item
// 返 回 值: Item*
//************************************
Item* CPassbookAgreement::GetItems()
{
	int count = m_Data.count;
	int i = 0;
	Item * items = new Item[m_Data.count];
	for (i = 0 ;i< count;i++)
	{
		items[i] = m_Data.items[i].item;
	}
	return items;
}
//************************************
// 方法名称: GetCount
// 创建日期: 2017/04/18
// 创 建 人: admin
// 函数说明: 获取item的数量
// 返 回 值: int
//************************************
int CPassbookAgreement::GetCount()
{
	return m_Data.count;
}
//************************************
// 方法名称: Reset
// 创建日期: 2017/04/18
// 创 建 人: admin
// 函数说明: 重置item
// 返 回 值: void
//************************************
void CPassbookAgreement::Reset()
{
	int count = m_Data.count;
	int i = 0;
	for (i = 0 ;i< count;i++)
	{
		Item item=m_Data.items[i].item;
	
		delete[] item.text;
		delete[] item.type;
		item.typeLen = 0;
		item.textLen = 0;
	}
	m_Data.count = 0;
}
//************************************
// 方法名称: Add
// 创建日期: 2017/04/18
// 创 建 人: admin
// 函数说明: 添加item
// 函数参数: char * type
// 函数参数: int typeLen
// 函数参数: char * text
// 函数参数: int textLen
// 返 回 值: void
//************************************
void CPassbookAgreement::Add(char *type,int typeLen,char *text,int textLen)
{
	MapItem mapItem = m_Data.items[m_Data.count];

	Item item = mapItem.item;
	item.type = type;
	item.typeLen = typeLen;
	item.text = text;
	item.textLen = textLen;

	mapItem.item = item;
	mapItem.size = getLength(&item);

	m_Data.items[m_Data.count] = mapItem;
	m_Data.count += 1;

	//ToChar(&m_Data);
}
