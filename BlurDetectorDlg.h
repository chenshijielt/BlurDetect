
// BlurDetectorDlg.h : ͷ�ļ�
//

#pragma once


// CBlurDetectorDlg �Ի���
class CBlurDetectorDlg : public CDialogEx
{
// ����
public:
	CBlurDetectorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BLURDETECTOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CImage m_Image;

	void OnBlurDetect();

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
	afx_msg void OnFileOpen();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
