// CClientsock.cpp: 구현 파일
//

#include "pch.h"
#include "project_server.h"
#include "CClientsock.h"
#include "afxdialogex.h"
#include "project_serverDlg.h"


// CClientsock

CClientsock::CClientsock()
{
}

CClientsock::~CClientsock()
{
}


// CClientsock 멤버 함수

void CClientsock::setlisten_sock(CAsyncSocket* client)
{
	m_pclientSocket = client;
}
void CClientsock::connect_python(CAsyncSocket* client)
{
	m_pySocket = client;
}

void CClientsock::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CprojectserverDlg* dlg = (CprojectserverDlg*)::AfxGetMainWnd();//메인 dlg 호출하려고
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	char recv_msg[1024];
	CString msg;
	CString emotion;
	emotion = "";
	memset(recv_msg, '\0', 1024);
	m_pclientSocket->Receive(recv_msg, sizeof(recv_msg));
	recv_msg[strlen(recv_msg)] = 0;
	msg.Format(_T("%s"), recv_msg);
	AfxExtractSubString(emotion, msg, 0, '/');
	insert_qry(emotion);
	AfxMessageBox(msg);
	m_pySocket->Send(recv_msg, sizeof(recv_msg));
	

	CSocket::OnReceive(nErrorCode);
}

void CClientsock::Create_table()
{

}
void CClientsock::insert_qry(CString emotion)
{
	CString qry;
	//qry.Format(_T("INSERT INTO interview_result(emotion) VALUES('+"emotion"+')"));
}