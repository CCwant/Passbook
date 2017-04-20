#include "stdafx.h"
#include "PassbookAgreement.h"
#include "Adler32.h"

// �ڴ�й¶��Ϣ����ʾ�ļ����ʹ����к�
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
			LOG(L"�ͷ� m_Data \n");
			int i = 0;
			for (i = 0 ;i< count;i++)
			{

				delete[] m_Data.items[i].item.type;
				delete[] m_Data.items[i].item.text;
			}
			//
		}
		delete[] m_Data.pass.data;
		LOG(L"�ͷŽ���. \n");
	}
}

void CPassbookAgreement::SetPassword(char *password,int len)
{
	//�ͷ�֮ǰ���������
	delete[] m_Data.pass.data;

	m_Data.pass.size = len;

	//���³�ʼ��
	m_Data.pass.data = new char[len];
	memcpy(m_Data.pass.data,password,len);
}
//************************************
// ��������: ToChar
// ��������: 2017/04/13
// �� �� ��: admin
// ����˵��: data�ṹתchar
// ��������: MapListData * item
// �� �� ֵ: char*
//************************************
char* CPassbookAgreement::ToChar(PasswordData *item)
{
	//����ܺ������


	//�ܳ���
	int len=getLength(item);
	//������
	char *dest=new char[len];
	//���
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
// ��������: ToChar
// ��������: 2017/04/13
// �� �� ��: admin
// ����˵��: item��װ�ṹתchar
// ��������: MapItem * item
// �� �� ֵ: char*
//************************************
char* CPassbookAgreement::ToChar(MapItem *mapItem){
	//�ܳ���
	int len=getLength(mapItem);
	//������
	char *dest=new char[len];
	//���
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
// ��������: ToChar
// ��������: 2017/04/13
// �� �� ��: admin
// ����˵��: item�ṹתchar
// ��������: TextItem * item
// �� �� ֵ: char*
//************************************
char* CPassbookAgreement::ToChar(Item *item)
{
	//�ܳ���
	int len=getLength(item);
	//������
	char *dest=new char[len];
	//���
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
// ��������: ToChar
// ��������: 2017/04/18
// �� �� ��: admin
// ����˵��: Header�ṹתchar
// ��������: PasswdHeader * header
// �� �� ֵ: char*
//************************************
char* CPassbookAgreement::ToChar(PasswdHeader *header)
{
	//�ܳ���
	int len=48;
	//������
	char *dest=new char[len];
	//���
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
// ��������: getLength
// ��������: 2017/04/13
// �� �� ��: admin
// ����˵��: ��ȡdata�ṹ�ܳ���
// ��������: MapListData * item
// �� �� ֵ: int
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
// ��������: getLength
// ��������: 2017/04/13
// �� �� ��: admin
// ����˵��: ��ȡitem��װ�ṹ�ܳ���
// ��������: MapItem * item
// �� �� ֵ: int
//************************************
int CPassbookAgreement::getLength(MapItem *item)
{
	return item->size + 4;;
}
//************************************
// ��������: getLength
// ��������: 2017/04/13
// �� �� ��: admin
// ����˵��: ��ȡItem�ṹ�ܳ���
// ��������: TextItem * item
// �� �� ֵ: int
//************************************
int CPassbookAgreement::getLength(Item *item)
{
	return item->textLen + item->typeLen+8;;
}
//************************************
// ��������: Reversal
// ��������: 2017/04/13
// �� �� ��: admin
// ����˵��: ��ת�ַ�����
// ��������: char * text
// �� �� ֵ: char*
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
// ��������: CreateHeader
// ��������: 2017/04/18
// �� �� ��: admin
// ����˵��: ����Header
// �� �� ֵ: void
//************************************
void CPassbookAgreement::CreateHeader()
{
	//Э��汾��
	int c_version = 48;
	//�������ϼ���
	int c_dataSize = getLength(&m_Data);
	int c_headerSize = 48;
	int c_fileSize = c_dataSize + c_headerSize;

	//Э��ǰ��
	char *sign="passwd";
	char ver[4];
	char *flag=new char[1];
	//���汾����λתchar
	sprintf_s(ver,"%03d",c_version);
	//��ʼ����־λ
	flag[0] = (char)0x0A;
	//У���
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

	LOG(L"�汾��:%d \n",c_version);
	LOG(L"FILE��С:%d \n",c_fileSize);
	LOG(L"HEADER��С:%d \n",c_headerSize);
	LOG(L"DATA��С:%d \n",c_dataSize);



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
	//����;
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
// ��������: CreateSignature
// ��������: 2017/04/18
// �� �� ��: admin
// ����˵��: ��ȡ�ļ�ǩ��
// �� �� ֵ: char*
//************************************
char* CPassbookAgreement::CreateSignature()
{
	LOG(L"[Agreement]����ǩ��[��ʼ] \n");
	//data������
	char * data = ToChar(&m_Data);
	//data������
	int dataLen = getLength(&m_Data);
	//�ܳ���
	int len = dataLen + 12;
	//������
	char *dest=new char[len];
	//���
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
	LOG(L"[Agreement]����ǩ��[����] \n");
	return signature;
}
//************************************
// ��������: CreateChecksum
// ��������: 2017/04/18
// �� �� ��: admin
// ����˵��: ��ȡУ���
// �� �� ֵ: char*
//************************************
char* CPassbookAgreement::CreateChecksum()
{
	LOG(L"[Agreement]����У���[��ʼ] \n");
	//data������
	char * data = ToChar(&m_Data);
	//data������
	int dataLen = getLength(&m_Data);
	Print(data,dataLen);
	//�ܳ���
	int len = dataLen + 32;
	//������
	char *dest=new char[len];
	//���
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

	LOG(L"[Agreement]У������ݳ���:%d \n",len);
	Adler32 adler32;
	adler32.Update(dest,len);
	long value=adler32.getValue();
	LOG(L"[Agreement]У���:%lu \n",value);

	//checksum
	char *s_checksum=new char[4];
	memcpy(s_checksum,&value,sizeof(long));
	char *checksum=Reversal(s_checksum);

	Print(checksum,4);
	LOG(L"[Agreement]����У���[����] \n");

	delete[] s_checksum;
	delete[] data;
	delete[] dest;
	return checksum;
}
//************************************
// ��������: GetSize
// ��������: 2017/04/18
// �� �� ��: admin
// ����˵��: ��ȡ���ݴ�С
// �� �� ֵ: int
//************************************
int CPassbookAgreement::GetSize()
{
	//data������
	int dataLen = getLength(&m_Data);
	//�ܳ��� = header + data;
	return dataLen + 48;
}
//************************************
// ��������: GetValue
// ��������: 2017/04/18
// �� �� ��: admin
// ����˵��: ��ȡ����
// �� �� ֵ: char*
//************************************
char* CPassbookAgreement::GetValue()
{
	LOG(L"[Agreement]��ʼ����.\n");
	//����Header
	CreateHeader();
	//data������
	int dataLen = getLength(&m_Data);
	//�ܳ��� = header + data;
	int len = dataLen + 48;
	LOG(L"[Agreement]�����ļ���С: %d \n",len);
	//������
	char *dest=new char[len];
	//���
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
	LOG(L"[Agreement]�������. \n");
	return dest;
}
//************************************
// ��������: SetValue
// ��������: 2017/04/18
// �� �� ��: admin
// ����˵��: ��������
// ��������: const char * data
// ��������: const int len
// �� �� ֵ: void
//************************************
void CPassbookAgreement::SetValue(const char* data,const int len)
{
	LOG(L"[Agreement]��ʼ����.\n");

	

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
	LOG(L"[Agreement]У���:%d   \n",m_Header.checksum);
	//signature
	size = 20;
	memcpy(m_Header.signature,&data[offset],size);
	offset += size;
	//fileSize
	size = 4;
	memcpy(u4temp,&data[offset],size);
	offset += size;
	m_Header.fileSize = C2I(u4temp);
	LOG(L"[Agreement]�ļ���С:%d   \n",m_Header.fileSize);
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
	m_Data.pass.data = new char[size];//��ʼ���ڴ�
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
		m_Data.items[i].item.type = new char[size];//��ʼ���ڴ�
		memcpy(m_Data.items[i].item.type,&datatemp[off],size);
		off += size;

		//TextItem-textLen
		size = 4;
		memcpy(u4temp,&datatemp[off],size);
		m_Data.items[i].item.textLen = C2I(u4temp);
		off += size;

		//TextItem-text
		size =m_Data.items[i].item.textLen;
		m_Data.items[i].item.text = new char[size];//��ʼ���ڴ�
		memcpy(m_Data.items[i].item.text,&datatemp[off],size);
		off += size;

		delete[] datatemp;
	}
	delete[] u4temp;
	LOG(L"[Agreement]�������.\n");
}
//************************************
// ��������: GetData
// ��������: 2017/04/18
// �� �� ��: admin
// ����˵��: ��ȡ����������
// �� �� ֵ: PasswordData
//************************************
PasswordData CPassbookAgreement::GetData()
{
	return m_Data;
}
//************************************
// ��������: GetItems
// ��������: 2017/04/18
// �� �� ��: admin
// ����˵��: ��ȡ����item
// �� �� ֵ: Item*
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
// ��������: GetCount
// ��������: 2017/04/18
// �� �� ��: admin
// ����˵��: ��ȡitem������
// �� �� ֵ: int
//************************************
int CPassbookAgreement::GetCount()
{
	return m_Data.count;
}
//************************************
// ��������: Reset
// ��������: 2017/04/18
// �� �� ��: admin
// ����˵��: ����item
// �� �� ֵ: void
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
// ��������: Add
// ��������: 2017/04/18
// �� �� ��: admin
// ����˵��: ���item
// ��������: char * type
// ��������: int typeLen
// ��������: char * text
// ��������: int textLen
// �� �� ֵ: void
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
