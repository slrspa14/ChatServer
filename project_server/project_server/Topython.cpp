// Topython.cpp: 구현 파일
//

#include "pch.h"
#include "project_server.h"
#include "Topython.h"


// Topython

Topython::Topython()
{
}

Topython::~Topython()
{
}


// Topython 멤버 함수

void Topython::set_wpfsocket(CAsyncSocket * client)
{
	m_pyClient = client;
}
void Topython::connect_wpf(CAsyncSocket* client)
{
	m_pWPFClient = client;
}
void Topython::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CSocket::OnReceive(nErrorCode);
}
