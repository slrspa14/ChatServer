// Topython.cpp: 구현 파일
//

#include "pch.h"
#include "project_server.h"
#include "Topython.h"
#include "project_serverDlg.h"

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
	m_python_Client = client;
}
void Topython::connect_wpf(CAsyncSocket* client)
{
	m_WPFClient = client;
}
void Topython::OnReceive(int nErrorCode)
{
	CprojectserverDlg* dlg = (CprojectserverDlg*)::AfxGetMainWnd();//메인 dlg 호출하려고
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	int file_length;
	int file_num = 1;
	CString file_save_path, voice_save_path, Name, occupation, msg;
	char recv_msg[1024];
	memset(recv_msg, '\0', 1024);
	Receive(recv_msg, sizeof(recv_msg));
	recv_msg[strlen(recv_msg)] = 0;
	msg = recv_msg;
	//담은거 db insert
	AfxExtractSubString(Name, msg, 0, '/');
	AfxExtractSubString(occupation, msg, 1, '/');

	file_save_path.Format(_T("C:/Users/aiot/Desktop/file_test/%d.mp4"), file_num);
	CFile recv_file;//wpf는 byte 배열로 보내고 mfc는 char*로 받아서 값이 다르면
	Receive(&file_length, 4);//3851836 -> 825571379
	file_length = htonl(file_length);//859321649//
	dlg->m_list2.AddString((LPCTSTR)file_length);
	byte* file = new byte[file_length];

	recv_file.Open(file_save_path, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	DWORD word;//CPU가 한번에 처리할 수 있는 데이터의 크기 단위를 WORD 라고 한다.DWORD는 나중에 나온거 더블
	word = Receive(file, file_length);
	recv_file.Write(file, word);//file_length x
	delete[] file;
	recv_file.Close();
	//file = nullptr;

	CFile send_file;
	send_file.Open(file_save_path, CFile::modeRead | CFile::typeBinary);
	file_length = ntohl(file_length);
	m_WPFClient->Send(&file_length, 4);

	byte* file_data = new byte[file_length];
	word = send_file.Read(file_data, file_length);
	m_WPFClient->Send(file_data, word);

	delete[] file_data;
	send_file.Close();
	file_num++;
	dlg->m_list1.AddString(_T("파일 송수신 완료"));
	CSocket::OnReceive(nErrorCode);
}
