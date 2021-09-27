// client.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <stdio.h>
#include <WS2tcpip.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll

#define BUF_SIZE 100

int _tmain(int argc, _TCHAR* argv[])
{
	//��ʼ��DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���
	SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);

	//���׽���
	struct sockaddr_in clnAddr;
	memset(&clnAddr, 0, sizeof(clnAddr));  //ÿ���ֽڶ���0���
	clnAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	//servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //�Զ���ȡIP��ַ
	InetPton(AF_INET, _T("127.0.0.2"), &clnAddr.sin_addr.s_addr);
	clnAddr.sin_port = htons(59773);  //�˿�
	bind(sock, (SOCKADDR*)&clnAddr, sizeof(SOCKADDR));

	//��������ַ��Ϣ
	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));  //ÿ���ֽڶ���0���
	servAddr.sin_family = PF_INET;
	//servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	InetPton(AF_INET, _T("127.0.0.3"), &servAddr.sin_addr.s_addr);
	servAddr.sin_port = htons(20971);

	//���ϻ�ȡ�û����벢���͸���������Ȼ����ܷ���������
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