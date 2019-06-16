#include "winsock2.h"
#include <iostream>
#include"client.h"
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996) //�������
using namespace std;
//BOOL RecvLine(SOCKET s, char* buf); //��ȡһ������
//char num = 48;
//��ʼ���׽��ֶ�̬��
int client::init_sock()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		//cout << "WSAStartup failed!" << endl;
		return -1;
	}
	return 0;
}
//�����׽���
int client::create_sock()
{
	
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		//cout << "socket failed!" << endl;
		WSACleanup();//�ͷ��׽�����Դ
		return  -1;
	}
	return 0;
}
//���÷�������ַ
void client::init_serv()
{
	//���÷�������ַ
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons((short)4999);
	int nServAddlen = sizeof(servAddr);
}
//���ӷ�����
int client::connect_serv()
{
	//���ӷ�����
	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
	if (SOCKET_ERROR == retVal)
	{
		//cout << "connect failed!" << endl;
		closesocket(sHost); //�ر��׽���
		WSACleanup(); //�ͷ��׽�����Դ
		return -1;
	}
	return 0;
}
//���������������
char client::send_infor()
{

	ZeroMemory(buf, BUF_SIZE);
	retVal = send(sHost, num_l, strlen(num_l), 0);
	if (SOCKET_ERROR == retVal)
	{
		//cout << "send failed!" << endl;
		closesocket(sHost); //�ر��׽���
		WSACleanup(); //�ͷ��׽�����Դ
		return -1;
	}
	return 0;
}
// ���շ������˵�����
char* client::recv_infor() 
{
	ZeroMemory(bufRecv, BUF_SIZE);
	recv(sHost, bufRecv, BUF_SIZE, 0); // ���շ������˵����ݣ� ֻ����5���ַ�
	
	//cout << endl << "�ӷ������������ݣ�" << bufRecv;
	//cout << "\n";
	return bufRecv;
}
//�ر�
void client::close_sock()
{
	closesocket(sHost); //�ر��׽���
	WSACleanup(); //�ͷ��׽�����Դ
}

bool client::init()
{
	init_sock();
	create_sock();
	init_serv();
	connect_serv();
	//while (true)
	//{
	//	send_infor();
	//	recv_infor();
	//}
	return true;
}


//int client::main(int argc, char* argv[])        
//{
//	//const int BUF_SIZE = 64;  
//	//const char * num_l = &num;
//	//WSADATA wsd; //WSADATA����
//	//SOCKET sHost; //�������׽���
//	//SOCKADDR_IN servAddr; //��������ַ
//	//char buf[BUF_SIZE]; //�������ݻ�����
//	//char bufRecv[BUF_SIZE];
//	//int retVal; //����ֵ
//				//��ʼ���׽��ֶ�̬��
//
//	while (true)
//	{
//
//		
//		//RecvLine(sHost, bufRecv);
//		ZeroMemory(bufRecv, BUF_SIZE);
//		recv(sHost, bufRecv, BUF_SIZE, 0); // ���շ������˵����ݣ� ֻ����5���ַ�
//		cout << endl << "�ӷ������������ݣ�" << bufRecv;
//		cout << "\n";
//	}
//	//�˳�
//	closesocket(sHost); //�ر��׽���
//	WSACleanup(); //�ͷ��׽�����Դ
//	return 0;
//}