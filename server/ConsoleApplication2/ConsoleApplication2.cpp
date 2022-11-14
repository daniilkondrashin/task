#pragma once
#include <stdio.h>
#include <iostream>
//#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#pragma warning(disable: 4996)

SOCKET Connection;

int main(int argc, char* argv[])
{
	//WSAStartup
	WSAData wsaDATA;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaDATA) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	
	Connection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

	if (Connection == 0) {
		std::cout << "Error #2\n";
	}
	else
	{
		std::cout << "Client Connected!\n";
	}
	char msgl[256];
	while (true)
	{
		std::cin.getline(msgl, sizeof(msgl));
		send(Connection, msgl, sizeof(msgl), NULL);
	}
	system("pause");
	return 0;
}


