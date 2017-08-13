#pragma once
#include "PEFile.h"

// CFLCDlg �Ի���

class CFLCDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFLCDlg)

public:
	CFLCDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFLCDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CPEFile peFile;
	afx_msg void OnBnClickedBtnVa();
	afx_msg void OnBnClickedBtnRva();
	afx_msg void OnBnClickedBtnFileoffset();
	CEdit m_edit_RVA;
	CEdit m_edit_VA;
	CEdit m_edit_FileOffset;
	BOOL m_RVA = FALSE;
	BOOL m_VA = TRUE;
	BOOL m_FileOffset=TRUE;
	afx_msg void OnBnClickedBtnCalc();

};

