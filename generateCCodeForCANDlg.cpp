
// generateCCodeForCANDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "generateCCodeForCAN.h"
#include "generateCCodeForCANDlg.h"
#include "afxdialogex.h"
#include "DBC\DBC.h"
#include <fstream>

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


// CgenerateCCodeForCANDlg �Ի���



CgenerateCCodeForCANDlg::CgenerateCCodeForCANDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GENERATECCODEFORCAN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgenerateCCodeForCANDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, dbc_fullfile);
}

BEGIN_MESSAGE_MAP(CgenerateCCodeForCANDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GET_DBC_BUTTON, &CgenerateCCodeForCANDlg::OnBnClickedGetDbcButton)
END_MESSAGE_MAP()


// CgenerateCCodeForCANDlg ��Ϣ�������

BOOL CgenerateCCodeForCANDlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CgenerateCCodeForCANDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CgenerateCCodeForCANDlg::OnPaint()
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
HCURSOR CgenerateCCodeForCANDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

string getDBCUnit(int size) {
	if (size == 1) {
		return "Bool";
	}
	else if (size <= 8) {
		return "UInt8";
	}
	else if (size <= 16) {
		return "UInt16";
	}
	else {
		return "UInt32";
	}
}

void generateXML(DBC dbc,CString path) {
	path.Replace(_T(".dbc"), _T(".xml"));
	ofstream outfile(path);
	outfile << "\<\?xml version=\"1.0\" encoding=\"ISO-8859-1\"\?\>" << endl;
	outfile << "\<ddObj Name=\"CAN Interface (from DBC File)\" Kind=\"VariableGroup\" xmlns=\"http:\/\/www.dspace.de\/DataDictionaryExtended\" xmlns:xsi=\"http:\/\/www.w3.org\/2001\/XMLSchema-instance\"\>" << endl;
	for (Message message : dbc.get_messages()) {
		outfile << "  \<ddObj Name=\"CANMsg_" << message.get_message_name() << "_" << message.get_message_id() << "\" Kind=\"VariableGroup\"\>"<< endl;
		for (Signal signal : message.get_signals()) {
			outfile << "    \<ddObj Name=\"" << signal.get_signal_name() << "\" Kind=\"Variable\"\>" << endl;
			if (signal.get_factor() != 1) {
				outfile << "      \<ddProperty Name=\"Description\">Signal " << signal.get_signal_name() << ". " << signal.get_receiver() << ". CAN format Motorola, CAN start bit: " << signal.get_start_bit() << ", length: " << signal.get_signal_size() << ", unsigned. World value = " << signal.get_factor() << "*" << signal.get_signal_name() << ".\<\/ddProperty\>" << endl;
			}
			else {
				outfile << "      \<ddProperty Name=\"Description\">Signal " << signal.get_signal_name() << ". " << signal.get_receiver() << ". CAN format Motorola, CAN start bit: " << signal.get_start_bit() << ", length: " << signal.get_signal_size() << ", unsigned. World value = " << signal.get_signal_name() << ".\<\/ddProperty\>" << endl;
			}
			outfile << "      \<ddProperty Name=\"Class\"\>GLOBAL\<\/ddProperty\>" << endl;
			outfile << "      \<ddProperty Name=\"Type\"\>" << getDBCUnit(signal.get_signal_size()) << "\<\/ddProperty\>" << endl;
			outfile << "      \<ddProperty Name=\"Scaling\"\>./LocalScaling\<\/ddProperty\>" << endl;
			outfile << "      \<ddProperty Name=\"Width\"\/>" << endl;
			outfile << "      \<ddProperty Name=\"Value\"\/>" << endl;
			outfile << "      \<ddProperty Name=\"Min\"\>" << signal.get_minimum() << "\<\/ddProperty\>" << endl;
			outfile << "      \<ddProperty Name=\"Max\"\>" << signal.get_maximum() << "\<\/ddProperty\>" << endl;
			outfile << "      \<ddProperty Name=\"Address\"\/>" << endl;
			outfile << "      \<ddProperty Name=\"NameTemplate\"\>$D\<\/ddProperty\>" << endl;
			outfile << "      \<ddObj Name=\"LocalScaling\" Kind=\"ScalingObject\">" << endl;
			outfile << "        \<ddProperty Name=\"Description\"\>Linear scaling, identical to scaling of source DBC file\<\/ddProperty\>" << endl;
			outfile << "        \<ddProperty Name=\"ConversionType\"\>LINEAR\<\/ddProperty\>" << endl;
			outfile << "        \<ddProperty Name=\"LSB\"\>" << signal.get_factor() << "\<\/ddProperty\>" << endl;
			outfile << "        \<ddProperty Name=\"Offset\"\>" << signal.get_offset() <<"\<\/ddProperty\>" << endl;
			outfile << "        \<ddProperty Name=\"Format\"\>%g\<\/ddProperty\>" << endl;
			outfile << "        \<ddProperty Name=\"Unit\"\>" << signal.get_unit() << "\<\/ddProperty\>" << endl;
			outfile << "      \<\/ddObj\>" << endl;
			outfile << "    \<\/ddObj\>" << endl;
		}
		outfile << "  \<\/ddObj\>" << endl;
	}
	outfile << "\<\/ddObj\>" << endl;

	outfile.close();
}

void CgenerateCCodeForCANDlg::OnBnClickedGetDbcButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL isOpen = TRUE;     //�Ƿ��(����Ϊ����)  
	CString defaultDir = L"C:\\";   //Ĭ�ϴ򿪵��ļ�·��  
	CString fileName = L"";         //Ĭ�ϴ򿪵��ļ���  
	CString filter = L"�ļ� (*.dbc)|*.dbc||";   //�ļ����ǵ�����  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"C:\\demo.dbc";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + _T("\\demo.dbc");
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	DBC dbc = DBC();
	dbc.read(filePath);

	dbc_fullfile.SetWindowTextW(filePath);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	generateXML(dbc, filePath);
}
