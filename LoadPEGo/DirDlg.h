#pragma once

#include "PEFile.h"
// CDirDlg �Ի���

class CDirDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDirDlg)

public:
	CDirDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDirDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_DIR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	//����PE���Ա����
	CPEFile m_PeFile;
	// �����RVA
	CString m_Export_RVA;
	// �����Size
	CString m_Export_Size;
	// �����RVA
	CString m_Import_RVA;
	// �����Size
	CString m_Import_Size;
	// ��ԴRVA
	CString m_Res_RVA;
	// ��ԴSize
	CString m_Res_Size;
	// �쳣RVA
	CString m_Exa_RVA;
	// �쳣Size
	CString m_Exa_Size;
	// ��ȫRVA
	CString m_Sec_RVA;
	// ��ȫ
	CString m_Sec_Size;
	// �ض�λ��RVA
	CString m_Loc_RVA;
	// �ض�λ��Size
	CString m_Loc_Size;
	// ����RVA
	CString m_Dbg_RVA;
	// ����Size
	CString m_Dbg_Size;
	// ��ȨRVA
	CString m_Rev_RVA;
	// ��ȨSize
	CString m_Rev_Size;
	// ȫ������RVA
	CString m_Global_RVA;
	// ȫ������Size
	CString m_Global_Size;
	// TLS_RVA
	CString m_TLS_RVA;
	// TLS Size
	CString m_TLS_Size;
	// ��������RVA
	CString m_Load_RVA;
	// ��������
	CString m_Load_Size;
	// ������
	CString m_Bound_RVA;
	// ������Size
	CString m_Bound_Size;
	// IAT RVA
	CString m_IAT_RVA;
	// IAT Size
	CString m_IAT_Size;
	// �ӳ�����RVA
	CString m_Delay_RVA;
	// �ӳ�����size
	CString m_Delay_Size;
	// COM_RVA
	CString m_COM_RVA;
	// COM_Size
	CString m_COM_Size;
	// ����_RVA
	CString m_Other_RVA;
	// ���� Size
	CString m_Other_Size;
};
