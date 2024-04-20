
// ChatServerDlg.h: 헤더 파일
//

#pragma once

#include "stdAfx.h"

// CChatServerDlg 대화 상자
class CChatServerDlg : public CDialogEx
{
	// 생성입니다.
public:
	CChatServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다
	CSocServer m_socServer;//서버용 소켓
	//CSocCom* m_socCom;//통신용 소켓
	CSocCom* m_socCom[MAX_CLIENT_COUNT];
	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATSERVER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


	// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	//afx_msg virtual 같은거 아무의미없음
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnAccept(WPARAM wParam, LPARAM lParam);// 클라이언트 접속 요청이 왔을 때 실행되는 메세지 함수
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);// 클라이언트에서 오는 데이터 수신할때 실행되는 메세지 함수
	DECLARE_MESSAGE_MAP()
public:
	CWinThread* m_thread;
	BOOL exit_thread;
	/*static UINT File_send(LPVOID pParam);
	static UINT Voice_send(LPVOID pParam);
	static UINT Text_send(LPVOID pParam);*/
	CListBox m_List;
	CListBox m_List2;
	std::list<int> m_using;//유저리스트
	afx_msg void OnBnClickedButtonStart();
	CButton m_start;
//	CButton m_btn;
};
