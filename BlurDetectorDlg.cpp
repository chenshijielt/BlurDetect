
// BlurDetectorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BlurDetector.h"
#include "BlurDetectorDlg.h"
#include "afxdialogex.h"
#include "blurDetect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBlurDetectorDlg �Ի���



CBlurDetectorDlg::CBlurDetectorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBlurDetectorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBlurDetectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBlurDetectorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_OPEN, &CBlurDetectorDlg::OnFileOpen)
	ON_COMMAND(ID_BLUR_DETECT, &CBlurDetectorDlg::OnBlurDetect)
END_MESSAGE_MAP()


// CBlurDetectorDlg ��Ϣ�������

BOOL CBlurDetectorDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	calcuXabs();
	cv::ocl::setUseOpenCL(true);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBlurDetectorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBlurDetectorDlg::OnPaint()
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
	else if (!m_Image.IsNull())
	{
		CRect rect;
		GetClientRect(&rect);
		CPaintDC dc(this);
		m_Image.Draw(dc.GetSafeHdc(), rect);
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBlurDetectorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBlurDetectorDlg::OnFileOpen()
{
	CFileDialog dlg(TRUE);
	if (IDOK == dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		m_Image.Destroy();
		HRESULT hr = S_OK;
		try {
			hr = m_Image.Load(path);
		} catch (...){ hr = S_FALSE; }
		Invalidate(TRUE);
	}
}


void CBlurDetectorDlg::OnBlurDetect()
{
	if (!m_Image.IsNull())
	{
		int w = m_Image.GetWidth(), h = m_Image.GetHeight(), 
			C = m_Image.GetBPP() / 8, L = m_Image.GetPitch();
		if (1 == C || 3 == C || 4 == C)
		{
			BYTE *addr = (BYTE*)m_Image.GetBits() + (h-1) * L;
			Mat m(h, w, CV_MAKETYPE(CV_8U, C), addr, abs(L)), gray;
			if (1 != C) cvtColor(m, gray, CV_RGB2GRAY);
			char result[64] = { 0 };
			sprintf_s(result, "%f", BlurDetect(1 == C ? m : gray));
			MessageBox(CString(result), _T("Info"), MB_ICONINFORMATION);
		}
	}
}


BOOL CBlurDetectorDlg::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN == pMsg->message)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE: case VK_RETURN:
			return TRUE;
		case VK_F2:
			OnFileOpen();
			return TRUE;
		case VK_F5:
			OnBlurDetect();
			return TRUE;
		default:
			break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
