#pragma once

// CClientsock 명령 대상

class CClientsock : public CSocket
{
public:
	CClientsock();
	virtual ~CClientsock();
	CAsyncSocket* m_pclientSocket;
	CAsyncSocket* m_pySocket;
	virtual void OnReceive(int nErrorCode);
	void connect_python(CAsyncSocket* client);
	void setlisten_sock(CAsyncSocket* clinet);
	void Create_table();
	void insert_qry(CString emotion);
};


