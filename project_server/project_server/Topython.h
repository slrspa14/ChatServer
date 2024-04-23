#pragma once

// Topython 명령 대상

class Topython : public CSocket
{
public:
	Topython();
	virtual ~Topython();

	virtual void OnReceive(int nErrorCode);
	CAsyncSocket* m_python_Client;
	CAsyncSocket* m_WPFClient;
	void connect_wpf(CAsyncSocket* client);
	void set_wpfsocket(CAsyncSocket* client);
};


