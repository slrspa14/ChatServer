#pragma once
#include <afxsock.h>            // ���� Ŭ���� ��� ���� include
#include "SocServer.h"            // ������ ����
#include "SocCom.h"                // ��ſ� ����

#define UM_ACCEPT WM_USER+1        // ���� �����쿡 �޽����� ������ ���� ������. ��, ���� ������(���⼭�� m_hWnd)�� SendMessage�� �̿��� UM_ACCEPT��� ����� ���� �޽����� ��.
#define UM_RECEIVE WM_USER+2    // UM_ACCEPT�� ����� ����