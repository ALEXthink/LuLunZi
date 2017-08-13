#pragma once
#include "afxcmn.h"
#include "ImportTable.h"

// CImportDlg �Ի���

class CImportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImportDlg)

public:
	CImportDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CImportDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_IMPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	// �����
	CListCtrl m_list_import;
	// API�����б�
	CListCtrl m_list_apiName;
	//��������
	CImportTable importTable;
	afx_msg void OnNMClickListImport(NMHDR *pNMHDR, LRESULT *pResult);
};
