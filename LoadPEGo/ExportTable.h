#pragma once
#include "PEFile.h"
class CExportTable :
	public CPEFile
{
public:
	CExportTable();
	virtual ~CExportTable();
	void operator=(CPEFile& pefile);
	//��ȡ������е�
	PIMAGE_EXPORT_DIRECTORY GetExportDir();
	DWORD GetNumOfFuns();
	DWORD GetNumOfNames();
	DWORD GetFirstFun();//��ȡ����������׵�ַ
	DWORD GetFun(DWORD nIndex);//��ȡָ������
	DWORD GetRVAOfFun(DWORD nIndex);//��ȡ�������ڵ�RVA,����ȡ�����������е�ֵ(����洢��RVA);

	DWORD GetFirstName();//��ȡ���к��������������ַ
	DWORD GetName(DWORD nIndex);//��ȡָ������λ�õ�����
	PBYTE GetNameValue(DWORD nIndex);//��ȡ����

	DWORD GetFirstNameOrd();//��ȡindex�����ַ
	DWORD GetNameOrd(DWORD nIndex);//��ȡָ������λ
	WORD GetNameOrdValue(DWORD nIndex);//��ȡord index
};

