#include <iostream>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32")
using namespace std;

int main()
{
	//서버

	WSAData wsaData;
	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (Result != 0)
	{
		cout << "Winsock dll error" << endl;
		exit(-1);
	}

	//소켓 생성
	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		cout << "INVALID_SOCKET : " << GetLastError() << endl;
		exit(-1);
	}
	//tcp용 문지기 소캣 설정
	SOCKADDR_IN ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr)); 
	//ZeroMemory(&ListenSockAddr, sizeof(ListenSockAddr));
	ListenSockAddr.sin_family = AF_INET;
	ListenSockAddr.sin_addr.s_addr = INADDR_ANY;
	ListenSockAddr.sin_port = htons(30211);	// 문지기의 허가를 받으면 다른 port를 임의로 뚫어서 연결시켜줌. 30211은 연결 확인용 port임.
	//ListenSockAddr.sin_zero[8];

	Result =  bind(ListenSocket, (SOCKADDR*)&ListenSocket, sizeof(ListenSockAddr));//바인드를 통해 소켓에 구멍을 뚫고 소캣이 실행될 때마다 bind된 함수를 실행

	if (Result == SOCKET_ERROR)
	{
		cout << "Can't bind : " << GetLastError() << endl;
		exit(-1);
	}

	listen(ListenSocket, 5);	//들어오려고 한다.
	if (Result == SOCKET_ERROR)
	{
		cout << "Can't bind : " << GetLastError() << endl;
		exit(-1);
	}

	//문지기에 의해서 연결되는 실제 소캣
	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
	int ClientSocketAddrLength = sizeof(ClientSockAddr);
	SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSockAddr,&ClientSocketAddrLength);	//실제 통신하는 소켓
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