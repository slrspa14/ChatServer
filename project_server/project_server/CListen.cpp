// CListen.cpp: 구현 파일
//

#include "pch.h"
#include "project_server.h"
#include "CListen.h"

#include "CClientsock.h"
#include "Topython.h"
#include "project_serverDlg.h"


// CListen
CListen::CListen()
{
}

CListen::~CListen()
{
}


// CListen 멤버 함수

void CListen::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CClientsock* client = new CClientsock;

	if (m_pWPFClient == NULL && m_pyClient == NULL)
	{
		m_pyClient = new Topython;
		if (!Accept(*m_pyClient))
			AfxMessageBox(_T("ERROR : Failed can't accept new Client!"));
		m_pyClient->set_wpfsocket(m_pyClient);
	}
	else
	{
		m_pWPFClient = new CClientsock;
		if (!Accept(*m_pWPFClient))
			AfxMessageBox(_T("ERROR : Failed can't accept new Client!"));
		m_pWPFClient->setlisten_sock(m_pWPFClient);
		m_pWPFClient->connect_python(m_pyClient);
		m_pyClient->connect_wpf(m_pWPFClient);
	}

	CAsyncSocket::OnAccept(nErrorCode);
}
