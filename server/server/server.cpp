// server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <WS2tcpip.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

#define BUF_SIZE 100

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

	//绑定套接字
	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));  //每个字节都用0填充
	servAddr.sin_family = PF_INET;  //使用IPv4地址
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //自动获取IP地址
	//InetPton(AF_INET, _T("127.0.0.3"), &servAddr.sin_addr.s_addr);
	servAddr.sin_port = htons(20971);  //端口
	bind(sock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));

	//接收客户端请求
	SOCKADDR clntAddr;  //客户端地址信息
	int nSize = sizeof(SOCKADDR);
	char buffer[BUF_SIZE];  //缓冲区
	while (1){
		#if 1
		int strLen = recvfrom(sock, buffer, BUF_SIZE, 0, &clntAddr, &nSize);
		printf("clntAddr is: ");
		for (int i = 0; i < 14; i++)
		{
			printf("%d ", clntAddr.sa_data[i]);
		}
		printf("\n");
		if (strLen > 0)
		{
			buffer[strLen] = 0x21;
			Sleep(2000);
			sendto(sock, buffer, strLen+1, 0, &clntAddr, nSize);
		}
		#endif
		
		#if 0
		int strLen = 5;
		char *buffer_str = "abcdef";
		//Sleep(2000);
		sendto(sock, buffer_str, strLen + 1, 0, &clntAddr, nSize);
		#endif
	}

	closesocket(sock);
	WSACleanup();
	return 0;
}