#include "stdafx.h"
#include "ImportTable.h"


CImportTable::CImportTable()
{
}


CImportTable::~CImportTable()
{
}

//ThunkRvaΪIMAGE_THUNK_DATA���ڵ�RVA
PIMAGE_IMPORT_BY_NAME CImportTable::GetFuncByName(DWORD ThunkRva)
{
	PIMAGE_IMPORT_BY_NAME apiName = (PIMAGE_IMPORT_BY_NAME)RVAToVA(ThunkRva);
	if (!apiName->Name)
		return NULL;
	return apiName;
}
//numΪ������еĸ���
PIMAGE_IMPORT_DESCRIPTOR CImportTable::GetImportDes(int nIndex, int num)
{
	PIMAGE_IMPORT_DESCRIPTOR firstImportDes = GetFirstImportDes();
	if (nIndex<0 ||num <= nIndex)
		return NULL;
		
	return &firstImportDes[nIndex];
}
//��ȡ������������ĸ���
int CImportTable::GetImportDesCount()
{
	int i = 0;
	PIMAGE_IMPORT_DESCRIPTOR firstImportDes = GetFirstImportDes();
	while (firstImportDes&&firstImportDes->FirstThunk)
	{
		i++;
		firstImportDes++;
	}
		
	return i;
}
//��ȡ������еĵ�һ������
PIMAGE_IMPORT_DESCRIPTOR CImportTable::GetFirstImportDes()
{
	PIMAGE_IMPORT_DESCRIPTOR firstImportDes = (PIMAGE_IMPORT_DESCRIPTOR)GetDirectoryEntry(IMAGE_DIRECTORY_ENTRY_IMPORT);
	if (!firstImportDes)
		return NULL;

	return firstImportDes;
}

void CImportTable::operator=(CPEFile & pefile)
{
	SetInfo(pefile.GetInfo());
}
//��ȡ��һ��ThunkData
PIMAGE_THUNK_DATA CImportTable::GetFirstThunkData(DWORD ThunkDataRva)
{
	PIMAGE_THUNK_DATA pThunkData= (PIMAGE_THUNK_DATA)RVAToVA(ThunkDataRva);
	if (!pThunkData->u1.Ordinal)
		return NULL;
	return pThunkData;

}
//��ȡָ����ThunkData
PIMAGE_THUNK_DATA CImportTable::GetThunkData(int nIndex, DWORD ThunkDataRva, int num)
{
	PIMAGE_THUNK_DATA pThunkData = GetFirstThunkData(ThunkDataRva);
	if (nIndex < 0 || nIndex >= num)
		return NULL;
	return &pThunkData[nIndex];
}
//��ȡThunkData����
int CImportTable::GetThunkDataCount(DWORD ThunkDataRva)
{
	int i = 0;
	PIMAGE_THUNK_DATA pThunkData = GetFirstThunkData(ThunkDataRva);
	while (pThunkData&&pThunkData->u1.Ordinal)
	{
		i++;
		pThunkData++;
	}

	return i;
}

