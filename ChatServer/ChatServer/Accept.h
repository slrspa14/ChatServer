#pragma once

#include <list>
#include "SocCom.h"
#define UM_ACCEPT WM_USER+1
// Accept 명령 대상

class Accept : public CAsyncSocket
{
public:
	Accept();
	virtual ~Accept();
	
    CSocCom m_socCom[MAX_CLIENT_COUNT];// 연결 요청을 한 클라이언트 서버와 실제 연결이 되는 소켓
    CSocCom* GetAcceptSocCom();                // 통신 소켓 리턴

    std::list<int> m_index;

    HWND m_hWnd;                            // 메인 윈도우 핸들
    void Accept::Init(HWND hWnd);        // 소켓 클래스와 메인 윈도우를 연결시킴    
    virtual void OnAccept(int nErrorCode);    // 클라이언트 접속 요청 처리
};


