// Accept.cpp: 구현 파일
//

#include "pch.h"
#include "ChatServer.h"
#include "Accept.h"

// Accept

Accept::Accept()
{
}

Accept::~Accept()
{
}


// Accept 멤버 함수
void Accept::Init(HWND hWnd)
{
	// 메인 윈도우 포인터 받기
	m_hWnd = hWnd;
}

void Accept::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//Accept(m_socCom);// m_socCom은 연결 요청을 한 클라이언트 서버와 실제 연결이 되는 소켓

	//Accept(m_socCom[m_index.front()]);
	SendMessage(m_hWnd, UM_ACCEPT, 0, 0);
	CAsyncSocket::OnAccept(nErrorCode);
}
CSocCom* Accept::GetAcceptSocCom() {
	// 통신소켓을 return
	// 반환되는 통신 소켓은 클라이언트와 연결됨
	return &m_socCom[m_index.front()];
}