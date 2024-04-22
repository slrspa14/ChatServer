#pragma once

#include "Topython.h"
#include "CClientsock.h"

// CListen 명령 대상

class CListen : public CAsyncSocket
{
public:
	CListen();
	virtual ~CListen();

	virtual void OnAccept(int nErrorCode);
	CClientsock* m_pWPFClient;
	Topython* m_pyClient;
};


