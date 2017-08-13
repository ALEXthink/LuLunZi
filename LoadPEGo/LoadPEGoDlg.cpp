
// LoadPEGoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LoadPEGo.h"
#include "LoadPEGoDlg.h"
#include "afxdialogex.h"
#include "DirDlg.h"
#include "ImportDlg.h"
#include "FLCDlg.h"
#include "ExportDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLoadPEGoDlg �Ի���



CLoadPEGoDlg::CLoadPEGoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOADPEGO_DIALOG, pParent)
	, m_entry(_T(""))
	, m_Mem(_T(""))
	, m_Section_Num(_T(""))
	, m_File_Alie(_T(""))
	, m_ImageBase(_T(""))
	, m_CodeStart(_T(""))
	, m_ImageSize(_T(""))
	, m_DataStart(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoadPEGoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEC_LIST, m_Section_list);
	DDX_Text(pDX, IDC_EDIT_ENTRY, m_entry);
	DDX_Text(pDX, IDC_EDIT_MEM, m_Mem);
	DDX_Text(pDX, IDC_EDIT_SECTION, m_Section_Num);
	DDX_Text(pDX, IDC_EDIT_FILEALIE, m_File_Alie);
	DDX_Text(pDX, IDC_EDIT_IMAGEBASE, m_ImageBase);
	DDX_Text(pDX, IDC_EDIT_CODE, m_CodeStart);
	DDX_Text(pDX, IDC_EDIT_IMAGESIZE, m_ImageSize);
	DDX_Text(pDX, IDC_EDIT_DATA, m_DataStart);
}

BEGIN_MESSAGE_MAP(CLoadPEGoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CLoadPEGoDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_DIR, &CLoadPEGoDlg::OnBnClickedBtnDir)
	ON_BN_CLICKED(IDC_BTN_IMPORT, &CLoadPEGoDlg::OnBnClickedBtnImport)
	ON_BN_CLICKED(IDC_BTN_FLC, &CLoadPEGoDlg::OnBnClickedBtnFlc)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &CLoadPEGoDlg::OnBnClickedBtnExport)
END_MESSAGE_MAP()


// CLoadPEGoDlg ��Ϣ�������

BOOL CLoadPEGoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// ��ʼ���б�ؼ�
	m_Section_list.ModifyStyle(0, LVS_REPORT);               // ����ģʽ  
	m_Section_list.SetExtendedStyle(m_Section_list.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);// �����+��ѡ��  
	//���ñ�ͷ
	m_Section_list.InsertColumn(0, "����", LVCFMT_LEFT, 100);
	m_Section_list.InsertColumn(1, "vOffset", LVCFMT_LEFT, 80);
	m_Section_list.InsertColumn(2, "vSize", LVCFMT_LEFT, 80);
	m_Section_list.InsertColumn(3, "rOffset", LVCFMT_LEFT, 80);
	m_Section_list.InsertColumn(4, "rSize", LVCFMT_LEFT, 80);
	m_Section_list.InsertColumn(5, "���", LVCFMT_LEFT, 120);
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLoadPEGoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLoadPEGoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLoadPEGoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLoadPEGoDlg::OnBnClickedBtnOpen()
{

	// ���ļ�
	BOOL isOpen = TRUE;     //�Ƿ��(����Ϊ����)  
	CString defaultDir = _T("E:\\");   //Ĭ�ϴ򿪵��ļ�·��  
	CString fileName = _T("");         //Ĭ�ϴ򿪵��ļ���  
	CString filter = _T("�ļ� (*.exe; *.dll)|*.exe;*.dll||");   //�ļ����ǵ�����  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = _T("E:\\");
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = _T("");
	if (result != IDOK) {
		return;
	}
	if (m_Section_list.GetItemCount()>0)
		m_Section_list.DeleteAllItems();
	filePath = openFileDlg.GetPathName();
	
	m_PeFile.Free();
	if (!m_PeFile.LoadPEFile(filePath.GetBuffer(0))) {
		MessageBox(_T("�ļ�����ʧ��!"), 0, 0);
		return;
	
	}
	if (!m_PeFile.IsPEFile())
	{
		MessageBox(_T("�ⲻ����Ч��PE�ļ�!"), 0, 0);
		return;
	}
	PIMAGE_FILE_HEADER FileHeader = m_PeFile.GetNtFileHeader();
	PIMAGE_OPTIONAL_HEADER OptionHeader = m_PeFile.GetNtOptionalHeader();
	//��ڵ�
	m_entry.Format(_T("0x%x"), OptionHeader->AddressOfEntryPoint);
	//�ڴ����
	m_Mem.Format(_T("0x%x"), OptionHeader->SectionAlignment);
	//��������
	m_Section_Num.Format(_T("0x%x"), FileHeader->NumberOfSections);
	//�ļ�����
	m_File_Alie.Format(_T("0x%x"), OptionHeader->FileAlignment);
	//�����ַ
	m_ImageBase.Format(_T("0x%x"), OptionHeader->ImageBase);
	//�������ʼ
	m_CodeStart.Format(_T("0x%x"), OptionHeader->BaseOfCode);
	//�����С
	m_ImageSize.Format(_T("0x%x"), OptionHeader->SizeOfImage);
	//���ݶ���ʼ
	m_DataStart.Format(_T("0x%x"), OptionHeader->BaseOfData);
	//��ʼ��������
	PIMAGE_SECTION_HEADER SectionHeader;
	CString sectionData;
	for (int i = 0; i < m_PeFile.GetSectionCount(); i++)
	{
		SectionHeader = m_PeFile.GetSection(i);
		sectionData = SectionHeader->Name;
		m_Section_list.InsertItem(0, sectionData);
		//RVA
		sectionData.Format(_T("0x%x"), SectionHeader->VirtualAddress);
		m_Section_list.SetItemText(0, 1, sectionData);
		//VSize
		sectionData.Format(_T("0x%x"), SectionHeader->Misc.VirtualSize);
		m_Section_list.SetItemText(0, 2, sectionData);
		//rOffset
		sectionData.Format(_T("0x%x"), SectionHeader->PointerToRawData);
		m_Section_list.SetItemText(0, 3, sectionData);
		//rSize
		sectionData.Format(_T("0x%x"), SectionHeader->SizeOfRawData);
		m_Section_list.SetItemText(0, 4, sectionData);
		//��ʶ
		sectionData.Format(_T("0x%x"), SectionHeader->Characteristics);
		m_Section_list.SetItemText(0, 5, sectionData);
	}
	UpdateData(FALSE);
			


	CWnd::SetDlgItemText(IDC_EDIT_FILE, filePath);
}


void CLoadPEGoDlg::OnBnClickedBtnDir()
{
	// ��Ŀ¼��
	CDirDlg dlg;

	dlg.m_PeFile = m_PeFile;
	dlg.DoModal();
	return;
}


void CLoadPEGoDlg::OnBnClickedBtnImport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CImportDlg dlg;
	dlg.importTable = m_PeFile;
	dlg.DoModal();
}


void CLoadPEGoDlg::OnBnClickedBtnFlc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFLCDlg flcDlg;
	flcDlg.peFile = m_PeFile;
	flcDlg.DoModal();
}


void CLoadPEGoDlg::OnBnClickedBtnExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CExportDlg dlg;
	dlg.exportTableFile = m_PeFile;
	dlg.DoModal();
}
