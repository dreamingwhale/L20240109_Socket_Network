#include <iostream>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32")
using namespace std;

int main()
{
	//����

	WSAData wsaData;
	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (Result != 0)
	{
		cout << "Winsock dll error" << endl;
		exit(-1);
	}

	//���� ����
	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		cout << "INVALID_SOCKET : " << GetLastError() << endl;
		exit(-1);
	}
	//tcp�� ������ ��Ĺ ����
	SOCKADDR_IN ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr)); 
	//ZeroMemory(&ListenSockAddr, sizeof(ListenSockAddr));
	ListenSockAddr.sin_family = AF_INET;
	ListenSockAddr.sin_addr.s_addr = INADDR_ANY;
	ListenSockAddr.sin_port = htons(30211);	// �������� �㰡�� ������ �ٸ� port�� ���Ƿ� �վ ���������. 30211�� ���� Ȯ�ο� port��.
	//ListenSockAddr.sin_zero[8];

	Result =  bind(ListenSocket, (SOCKADDR*)&ListenSocket, sizeof(ListenSockAddr));//���ε带 ���� ���Ͽ� ������ �հ� ��Ĺ�� ����� ������ bind�� �Լ��� ����

	if (Result == SOCKET_ERROR)
	{
		cout << "Can't bind : " << GetLastError() << endl;
		exit(-1);
	}

	listen(ListenSocket, 5);	//�������� �Ѵ�.
	if (Result == SOCKET_ERROR)
	{
		cout << "Can't bind : " << GetLastError() << endl;
		exit(-1);
	}

	//�����⿡ ���ؼ� ����Ǵ� ���� ��Ĺ
	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
	int ClientSocketAddrLength = sizeof(ClientSockAddr);
	SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSockAddr,&ClientSocketAddrLength);	//���� ����ϴ� ����
	if (ClientSocket == INVALID_SOCKET)
	{
		cout << "accept fail :" << GetLastError() << endl;
		exit(-1);
	}

	const char Buffer[] = { "Hello World" };

	int SentByte = send(ClientSocket, Buffer, strlen(Buffer),0);
	if (SentByte < 0)
	{
		cout << "Error :" << GetLastError() << endl;
		exit(-1);
	}
	else if (SentByte == 0)
	{
		cout << "Disconnect :" << GetLastError() << endl;
		exit(-1);
	}
	else
	{
		cout << "Sent byte :" << ", "<< Buffer << endl;
		exit(-1);
	}

	char RecvBuffer[1024] = { 0, };
	int RecvByte = recv(ClientSocket, RecvBuffer, sizeof(RecvBuffer), 0);
	if (RecvByte < 0)
	{
		cout << "Error :" << GetLastError() << endl;
		exit(-1);
	}
	else if (RecvByte == 0)
	{
		cout << "Disconnect :" << GetLastError() << endl;
		exit(-1);
	}
	else
	{
		cout << "Sent byte :" << ", " << RecvBuffer << endl;
		exit(-1);
	}


	closesocket(ClientSocket);
	closesocket(ListenSocket);

	WSACleanup();

	return 0;
}