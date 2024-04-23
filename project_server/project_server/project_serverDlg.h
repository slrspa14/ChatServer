
// project_serverDlg.h: 헤더 파일
//

#pragma once
#include "CListen.h"


// CprojectserverDlg 대화 상자
class CprojectserverDlg : public CDialogEx
{
// 생성입니다.
public:
	CprojectserverDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CListen serv_sock;//서버 소켓
	CClientsock* wpf_socket;//통신
	Topython* py_sock;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	CprojectserverDlg* dlg;
	CListen m_ListenSocket;
	CListBox m_list2;
	CListBox m_list1;
	afx_msg void OnBnClickedButtonStart();
};
