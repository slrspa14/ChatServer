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
	memset(recv_msg, '\0', 1024);
	m_pclientSocket->Receive(recv_msg, sizeof(recv_msg));
	recv_msg[strlen(recv_msg)] = 0;
	msg.Format(_T("%s"), recv_msg);
	AfxMessageBox(msg);
	m_pySocket->Send(recv_msg, sizeof(recv_msg));


	//CString file_save_path, voice_save_path;
	//file_save_path.Format(_T("C:/Users/aiot/Desktop/file_test/%d"), file_num);
	////voice_save_path = "C:/Users/aiot/Desktop/file_test/voice/" + file_num;
	//CFile recv_file;
	//Receive((char*)&file_length, 4);//3851836 -> 825571379
	//AfxMessageBox(_T("%d"), file_length);
	//int bytesread = 0;
	//byte* file = new byte[file_length];

	//recv_file.Open(file_save_path, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	//DWORD word;//CPU가 한번에 처리할 수 있는 데이터의 크기 단위를 WORD 라고 한다.DWORD는 나중에 나온거 더블
	//word = Receive(file, file_length);
	//recv_file.Write(file, word);//file_length x
	//delete[] file;
	//recv_file.Close();
	////file = nullptr;

	//CFile send_file;
	//send_file.Open(file_save_path, send_file.modeRead | send_file.typeBinary);
	//file_length = ntohl(file_length);
	//m_pySocket->Send(&file_length, 4);

	//byte* file_data = new byte[file_length];
	//word = send_file.Read(file_data, file_length);
	//m_pySocket->Send(file_data, word);

	//delete[] file_data;
	//send_file.Close();
	//file_num++;
	//dlg->m_list1.AddString(_T("파일 송수신 완료"));
	CSocket::OnReceive(nErrorCode);
}

void CClientsock::Create_table()
{
	
}
void CClientsock::insert_qry(CString name, CString occupation, CString emotion)
{
	CString qry;
	qry.Format(_T("INSERT INTO interview_result VALUES('%s', '%s', '%s')"), name, occupation, emotion);

}
