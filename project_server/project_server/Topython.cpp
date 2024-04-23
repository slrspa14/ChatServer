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
	CprojectserverDlg* dlg = (CprojectserverDlg*)::AfxGetMainWnd;//메인 dlg 호출하려고
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	int file_length = 0;
	int file_num = 1;
	CString file_save_path, voice_save_path;
	file_save_path = "C:/Users/aiot/Desktop/file_test/" + file_num;
	//voice_save_path = "C:/Users/aiot/Desktop/file_test/voice/" + file_num;
	CFile recv_file;
	Receive(&file_length, 4);
	AfxMessageBox(_T("%d"), file_length);
	int bytesread = 0;
	byte* file = new byte[file_length];

	recv_file.Open(file_save_path, recv_file.modeCreate | recv_file.modeWrite | recv_file.typeBinary);
	DWORD word;//CPU가 한번에 처리할 수 있는 데이터의 크기 단위를 WORD 라고 한다.DWORD는 나중에 나온거 더블
	word = Receive(file, file_length);
	recv_file.Write(file, file_length);//
	delete[] file;// debug assertion///////3718984,,,,942749491 파일크기 이상
	file = nullptr;

	CFile send_file;
	send_file.Open(file_save_path, send_file.modeRead | send_file.typeBinary);
	file_length = ntohl(file_length);
	m_WPFClient->Send(&file_length, 4);

	byte* file_data = new byte[file_length];
	word = send_file.Read(file_data, file_length);
	m_WPFClient->Send(file_data, word);

	delete[] file_data;
	recv_file.Close();
	send_file.Close();
	file_num++;
	dlg->m_list1.AddString(_T("파일 송수신 완료"));
	CSocket::OnReceive(nErrorCode);
}
