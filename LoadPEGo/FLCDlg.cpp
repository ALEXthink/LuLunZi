// FLCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LoadPEGo.h"
#include "FLCDlg.h"
#include "afxdialogex.h"


// CFLCDlg �Ի���

IMPLEMENT_DYNAMIC(CFLCDlg, CDialogEx)

CFLCDlg::CFLCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_FLC, pParent)

{
	
}

CFLCDlg::~CFLCDlg()
{
}

void CFLCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_VA, m_edit_VA);
	DDX_Control(pDX, IDC_EDIT_RVA, m_edit_RVA);
	DDX_Control(pDX, IDC_EDIT_FileOffset, m_edit_FileOffset);

}


BEGIN_MESSAGE_MAP(CFLCDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_VA, &CFLCDlg::OnBnClickedBtnVa)
	ON_BN_CLICKED(IDC_BTN_RVA, &CFLCDlg::OnBnClickedBtnRva)
	ON_BN_CLICKED(IDC_BTN_FILEOFFSET, &CFLCDlg::OnBnClickedBtnFileoffset)
	ON_BN_CLICKED(IDC_BTN_CALC, &CFLCDlg::OnBnClickedBtnCalc)
END_MESSAGE_MAP()


// CFLCDlg ��Ϣ�������
BOOL CFLCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return TRUE;

}

void CFLCDlg::OnBnClickedBtnVa()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_edit_VA.SetReadOnly(FALSE);
	m_edit_RVA.SetReadOnly(TRUE);
	m_edit_FileOffset.SetReadOnly(TRUE);
	m_edit_VA.SetWindowTextA(_T(""));
	m_edit_RVA.SetWindowTextA(_T(""));
	m_edit_FileOffset.SetWindowTextA(_T(""));

	m_VA = FALSE;
	m_RVA = m_FileOffset = TRUE;
	
}


void CFLCDlg::OnBnClickedBtnRva()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_edit_VA.SetReadOnly(TRUE);
	m_edit_RVA.SetReadOnly(FALSE);
	m_edit_FileOffset.SetReadOnly(TRUE);
	m_edit_VA.SetWindowTextA(_T(""));
	m_edit_RVA.SetWindowTextA(_T(""));
	m_edit_FileOffset.SetWindowTextA(_T(""));

	m_RVA = FALSE;
	m_VA = m_FileOffset = TRUE;
}


void CFLCDlg::OnBnClickedBtnFileoffset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_edit_VA.SetReadOnly(TRUE);
	m_edit_RVA.SetReadOnly(TRUE);
	m_edit_FileOffset.SetReadOnly(FALSE);
	m_edit_VA.SetWindowTextA(_T(""));
	m_edit_RVA.SetWindowTextA(_T(""));
	m_edit_FileOffset.SetWindowTextA(_T(""));

	m_FileOffset = FALSE;
	m_VA = m_RVA = TRUE;
}


void CFLCDlg::OnBnClickedBtnCalc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strVA, strRVA, strFileOffset;
	DWORD dwVA, dwRVA, dwFileOffset;
	GetDlgItemText(IDC_EDIT_VA, strVA);
	GetDlgItemText(IDC_EDIT_RVA, strRVA);
	GetDlgItemText(IDC_EDIT_FileOffset, strFileOffset);
	if (!m_VA&&strVA.GetLength() > 0)
	{//����ΪVAʱ
		long iVA = strtol(strVA, NULL, 16);

		if (peFile.VA2(iVA, dwRVA, dwFileOffset))
		{
			strRVA.Format(_T("%x"), dwRVA);
			strFileOffset.Format(_T("%x"), dwFileOffset);
			goto Exit1;
		}
		else
		{
			goto Exit0;
		}
		
		
	}
	else if (!m_RVA&&strRVA.GetLength()>0)
	{
		//����ΪRVAʱ
		long iRVA = strtol(strRVA, NULL, 16);

		if (peFile.RVA2(iRVA, dwVA, dwFileOffset))
		{
			strVA.Format(_T("%x"), dwVA);
			strFileOffset.Format(_T("%x"), dwFileOffset);
			goto Exit1;
		}
		else
		{
			goto Exit0;
		}
	}
	else if (!m_FileOffset&&strFileOffset.GetLength() > 0)
	{
		//����ΪFileOffsetʱ
		long iFileOffset = strtol(strFileOffset, NULL, 16);

		if (peFile.FileOffset2(iFileOffset, dwRVA, dwVA))
		{
			strRVA.Format(_T("%x"), dwRVA);
			strVA.Format(_T("%x"), dwVA);
			goto Exit1;
		}
		else
		{
			goto Exit0;
		}
	}
	else {
	
		MessageBox(_T("������16��������"), 0, 0);
	}

Exit0:
	MessageBox(_T("�������ֳ�����Χ����δ����PE�ļ�"), 0, 0);
	return;
Exit1:
	m_edit_VA.SetWindowTextA(strVA);
	m_edit_RVA.SetWindowTextA(strRVA);
	m_edit_FileOffset.SetWindowTextA(strFileOffset);
	return;

}
