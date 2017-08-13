#ifndef _PEFILE_H_
#define _PEFILE_H_

#if _MSC_VER > 1000
#pragma once
#endif

typedef struct _MAP_FILE_STRUCT
{
	HANDLE hFile;//�򿪵��ļ����
	HANDLE hMapping;//�ļ�ӳ�䵽�ڴ�ľ��
	LPVOID ImageBase;//�ļ��� ����
	DWORD dwFileSize;//�ļ��Ĵ�С


} MAP_FILE_STRUCT,*PMAP_FILE_STRUCT;

enum {
	LFILE_FROM_NOMAL = 0,       //�ļ���ʱ�Ĵ���ʽ
	LFILE_FROM_FILE,
	LFILE_FROM_MEMORY
};

class CPEFile
{
public:
	PIMAGE_SECTION_HEADER GetSection(int nIndex);
	BOOL IsPEFile();
	PIMAGE_SECTION_HEADER GetFirstSecHeader();
	int GetSectionCount();
	PIMAGE_DATA_DIRECTORY GetDataDirectory(int nIndex);
	PIMAGE_DATA_DIRECTORY GetDataDirectory();
	PIMAGE_OPTIONAL_HEADER GetNtOptionalHeader();
	PIMAGE_FILE_HEADER GetNtFileHeader();
	PIMAGE_NT_HEADERS GetNtHeader();
	PIMAGE_DOS_HEADER GetDosHeader();
	DWORD GetImageSize();
	BYTE* GetImage();
	BOOL Free();
	BOOL LoadPEFile(char* lpFileName);
	BOOL SetInfo(MAP_FILE_STRUCT* pMapFileMsg);
	MAP_FILE_STRUCT* GetInfo();
	void operator=(CPEFile& lPeFile);
	CPEFile();
	virtual ~CPEFile();
	LPVOID RVAToVA(DWORD dwRVA);//��RVAתΪVA
	LPVOID GetDirectoryEntry(int DirectoryEntry);//��ȡָ������Ŀ¼��ĵ�ַ

	BOOL RVA2(DWORD dwRVA,DWORD& dwVa, DWORD& dwFileOffset);//ͨ���ļ�ͷ�Ļ�ַ
	BOOL VA2(DWORD dwVA, DWORD& dwRVA, DWORD& dwFileOffset);
	BOOL FileOffset2(DWORD dwFileOffset, DWORD& dwRVA, DWORD& dwVA);
	BOOL GetOffsetByMenRVA(DWORD dwRVA, DWORD& dwSecHRVA, DWORD& dwFileHRVA);//ͨ���ڴ��RVA��ȡ�����ڽڵ�RVA���ļ�ƫ��
	BOOL GetOffsetByFileRVA(DWORD dwRVA, DWORD& dwSecHRVA, DWORD& dwFileHRVA);//ͨ���ļ��е�Offset��ȡ�����ڽڵ�RVA���ļ�ƫ��
private:
	//���ڱ�ʶ�ļ��Ĵ�״̬//���ڱ�ʶ�ļ��Ĵ�״̬
	BYTE bLoadStart;
	//���ڴ洢�򿪵��ļ�������ļ����ݣ��ļ���С
	MAP_FILE_STRUCT *pstMapFile;

	
};

#endif // !_PEFILE_H_