// client.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <stdio.h>
#include <WS2tcpip.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

#define BUF_SIZE 100

int _tmain(int argc, _TCHAR* argv[])
{
	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);

	//绑定套接字
	struct sockaddr_in clnAddr;
	memset(&clnAddr, 0, sizeof(clnAddr));  //每个字节都用0填充
	clnAddr.sin_family = PF_INET;  //使用IPv4地址
	//servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //自动获取IP地址
	InetPton(AF_INET, _T("127.0.0.2"), &clnAddr.sin_addr.s_addr);
	clnAddr.sin_port = htons(59773);  //端口
	bind(sock, (SOCKADDR*)&clnAddr, sizeof(SOCKADDR));

	//服务器地址信息
	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));  //每个字节都用0填充
	servAddr.sin_family = PF_INET;
	//servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	InetPton(AF_INET, _T("127.0.0.3"), &servAddr.sin_addr.s_addr);
	servAddr.sin_port = htons(20971);

	//不断获取用户输入并发送给服务器，然后接受服务器数据
	struct sockaddr fromAddr;
	int addrLen = sizeof(fromAddr);
	while (1){
		char buffer[BUF_SIZE] = { 0 };
		printf("Input a string: ");
		gets(buffer);
		sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
		memset((void *)(&fromAddr), 0, addrLen);
		int strLen = recvfrom(sock, buffer, BUF_SIZE, 0, &fromAddr, &addrLen);
		buffer[strLen] = 0;
		printf("Message form server: %s\n", buffer);
		printf("fromAddr is: ");
		for (int i = 0; i < 14;i++)
		{
			printf("%d ", fromAddr.sa_data[i]);
		}
		printf("\n");
		
	}

	closesocket(sock);
	WSACleanup();
	return 0;
}