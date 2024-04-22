// CClientsock.cpp: 구현 파일
//

#include "pch.h"
#include "project_server.h"
#include "CClientsock.h"
#include "afxdialogex.h"

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
	int file_length;
	int file_num = 1;
	CString file_save_path, voice_save_path;
	file_save_path = "C:/Users/aiot/Desktop/file_test/" + file_num++;
	voice_save_path = "C:/Users/aiot/Desktop/file_test/voice" + file_num++;
	CFile recv_file;
	Receive(&file_length, 4);
	AfxMessageBox(_T("%d"), file_length);
	if (file_length < 4 || file_length > 4)
	{
		//텍스트
		m_pySocket->Send("받은내용", sizeof("받은내용"));
	}
	else
	{
		int bytesread = 0;
		byte* file = new byte[file_length];

		recv_file.Open(file_save_path, recv_file.modeCreate | recv_file.modeWrite | recv_file.typeBinary);
		DWORD word;//CPU가 한번에 처리할 수 있는 데이터의 크기 단위를 WORD 라고 한다.DWORD는 나중에 나온거 더블
		word = Receive(file, file_length);
		recv_file.Write(file, file_length);
		recv_file.Close();
		delete file;

		CFile send_file;
		send_file.Open(file_save_path, send_file.modeRead | send_file.typeBinary);
		file_length = ntohl(file_length);
		m_pySocket->Send(&file_length, 4);

		byte* file_data = new byte[file_length];
		word = send_file.Read(file_data, file_length);
		m_pySocket->Send(file_data, word);

		delete file_data;
		send_file.Close();
	}
	
	CSocket::OnReceive(nErrorCode);
}