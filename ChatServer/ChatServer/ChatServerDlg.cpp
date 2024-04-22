// ChatServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CChatServerDlg 대화 상자

CChatServerDlg::CChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATSERVER_DIALOG, pParent)
	, m_thread(nullptr)
	, exit_thread(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_LIST2, m_List2);
	DDX_Control(pDX, IDC_BUTTON_START, m_start);
	//  DDX_Control(pDX, IDC_BUTTON_SEND, m_btn);
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_ACCEPT, OnAccept)
	ON_MESSAGE(UM_RECEIVE, OnReceive)
	ON_BN_CLICKED(IDC_BUTTON_START, &CChatServerDlg::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// CChatServerDlg 메시지 처리기

BOOL CChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 클라이언트 연결 요청이 왔기 때문에 Accept 함수로 접속
// 실제 접속을 담당하는 것은 CSocServer
// 이렇게 접속한 소켓은 GetAcceptSocCom을 이용해 얻어옴
// OnAccept 실행 이후 서버용 소켓인 m_socServer의 역활은 끝나고, 실제 모든 통신은 통신용 소켓인 m_socCom을 이용
LRESULT CChatServerDlg::OnAccept(WPARAM wParam, LPARAM lParam) 
{
	// 클라이언트에서 접속 요청이 왔을 때
	try 
	{
		// 통신용 소켓을 생선한 뒤
		int tmp = m_socServer.m_index.front();

		CString number;// 클라이언트 번호
		number.Format(_T("%d"), tmp);

		m_socCom[tmp] = new CSocCom();
		// 서버소켓과 통신소켓을 연결한다.
		m_socCom[tmp] = m_socServer.GetAcceptSocCom();

		m_socServer.m_index.pop_front();
		m_using.push_back(tmp);

		m_socCom[tmp]->m_index = tmp;
		m_socCom[tmp]->Init(this->m_hWnd);

		AfxMessageBox(_T("클라이언트 접속"));
		//thread
	}
	catch (CException* ex) 
	{
		ex->ReportError();
	}
	UpdateData(FALSE);
	return TRUE;
}

// 데이터를 보내는 것은 소켓 클래스의 멤버 함수인 Send를 이용
// 데이터를 받을 때는 통신 소켓 클래스에 오버라이딩한 OnReceive 메시지 함수를 사용
LRESULT CChatServerDlg::OnReceive(WPARAM wParam, LPARAM lParam) {
	// 접속된 곳에서 데이터가 도착했을 때
	char pTmp[1024];
	CString strTmp;
	memset(pTmp, '\0', 1024);

	// 데이터를 pTmp에 받는다.
	m_socCom[wParam]->Receive(pTmp, 1024);// wParam = 클라이언트 번호
	strTmp.Format(_T("%s"), pTmp);

	if (strTmp.Compare(SOC_CLIENT_DISCONNECT) == 0)//접속종료
	{
		m_socServer.m_socCom[wParam].Close();
		m_socCom[wParam]->Close();
		m_socServer.m_index.push_back((int)wParam);
		m_using.erase(std::remove(m_using.begin(), m_using.end(), wParam), m_using.end());
	}
	else
	{
		int bytesread;
		int file_size = 0;
		int file_num = 1;
		CString file_save_path = "C:/Users/aiot/Desktop/file_test/receive_video" + file_num;
		CString voice_save_path = "C:/Users/aiot/Desktop/file_test/voice/receive_video" + file_num;
		CFile file;
		// 리스트박스
		/*CString id;
		id.Format("%d", (int)wParam);*/
		
		CString recv_msg = (LPSTR)pTmp;
		CString num = "";
		CString size = "";
		AfxExtractSubString(num, recv_msg, 0, '/');
		//들어옴
		switch (_ttoi(num))
		{
		case 1://wpf(음성,영상,텍스트)
			m_List2.AddString("WPF 클라이언트 접속");
			//m_socCom[0]->Send("접속확인", 256);
			break;
		case 99://python
			m_List2.AddString("PYTHON 클라이언트 접속");
			//m_socCom[1]->Send("접속확인", 256);
			break;
		case 2://영상
			AfxExtractSubString(size, recv_msg, 1, '/');
			int file_size = _ttoi(size);
			char file_buf[1024];
			//do
			//{
			//	bytesread = m_socCom[wParam]->Receive(file_buf, sizeof(file_buf));
			//	if (bytesread > 0)
			//	{
			//		file.Write(file_buf, bytesread);
			//	}
			//} while (bytesread > 0);
			//file.Open(save_path, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
			if (file.Open(file_save_path, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
			{
				while (bytesread < file_size)
				{
					bytesread = m_socCom[wParam]->Receive(file_buf, sizeof(file_buf));
					file.Write(file_buf, bytesread);
				}
			}
			file_num++;
			break;
		case 3://음성 //3/파일 사이즈
			if (file.Open(voice_save_path, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
			{
				while (bytesread < file_size)
				{
					bytesread = m_socCom[wParam]->Receive(file_buf, sizeof(file_buf));
				}
			}
			file_num++;
			break;
		case 4://텍스트
			m_List2.AddString(recv_msg);// 4/asdfasfdw
			//strcpy(send_text, (LPSTR)(LPCSTR)recv_msg);
			m_socCom[1]->Send(strTmp, sizeof(strTmp));
			break;
		default:
			break;
		}

		/*int i = m_List.GetCount();
		m_List.InsertString(i, (CString("사용자") + id + " : " + strTmp));*/

		// 이 부분 제외하면 서버만 다중 클라이언트로 부터 채팅 가능.
		//for each (int i in m_using) 
		//{
		//	if (i != _ttoi(id))
		//	{    // 보낸 클라이언트 제외 모든 클라이언트한테 보냄
		//		m_socCom[i]->Send((CString("사용자") + id + " : " + strTmp), 256);
		//	}
		//}
	}
	return TRUE;
}


void CChatServerDlg::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	try
	{
		AfxMessageBox("서버 오픈");
		//m_socCom = NULL;
		for (int i = 0; i < MAX_CLIENT_COUNT; i++)
		{
			m_socServer.m_index.push_back(i);
		}
		// 서버 소켓을 생성(포트번호 9195)
		m_socServer.Create(9195);
		// 클라이언트의 접속을 기다림
		m_socServer.Listen();
		// 소켓 클래스와 메인 윈도우(여기에서는 CChatServerDlg)를 연결
		m_socServer.Init(this->m_hWnd);

		GetDlgItem(IDC_BUTTON_START)->ShowWindow(SW_HIDE);//버튼 숨기고
	}
	catch (CException* ex)
	{
		ex->ReportError();
	}
}
