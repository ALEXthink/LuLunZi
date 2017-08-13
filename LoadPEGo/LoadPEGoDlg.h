
// LoadPEGoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include "PEFile.h"
// CLoadPEGoDlg �Ի���
class CLoadPEGoDlg : public CDialogEx
{
// ����
public:
	CLoadPEGoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOADPEGO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpen();
	CListCtrl m_Section_list;
	// ��ڵ�
	CString m_entry;
	// �ڴ����
	CString m_Mem;
	// ��������
	CString m_Section_Num;
	// �ļ�����
	CString m_File_Alie;
	// �����ַ
	CString m_ImageBase;
	// �������ʼ
	CString m_CodeStart;
	// �����С
	CString m_ImageSize;
	// ���ݶ���ʼ
	CString m_DataStart;
	//����PE���Ա����
	CPEFile m_PeFile;
	afx_msg void OnBnClickedBtnDir();
	afx_msg void OnBnClickedBtnImport();
	afx_msg void OnBnClickedBtnFlc();
	afx_msg void OnBnClickedBtnExport();
};
