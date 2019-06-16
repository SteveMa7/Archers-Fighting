#include "winsock2.h"
#include <iostream>
#include"client.h"
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996) //必须加上
using namespace std;
//BOOL RecvLine(SOCKET s, char* buf); //读取一行数据
//char num = 48;
//初始化套结字动态库
int client::init_sock()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		//cout << "WSAStartup failed!" << endl;
		return -1;
	}
	return 0;
}
//创建套接字
int client::create_sock()
{
	
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		//cout << "socket failed!" << endl;
		WSACleanup();//释放套接字资源
		return  -1;
	}
	return 0;
}
//设置服务器地址
void client::init_serv()
{
	//设置服务器地址
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons((short)4999);
	int nServAddlen = sizeof(servAddr);
}
//连接服务器
int client::connect_serv()
{
	//连接服务器
	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
	if (SOCKET_ERROR == retVal)
	{
		//cout << "connect failed!" << endl;
		closesocket(sHost); //关闭套接字
		WSACleanup(); //释放套接字资源
		return -1;
	}
	return 0;
}
//向服务器发送数据
char client::send_infor()
{

	ZeroMemory(buf, BUF_SIZE);
	retVal = send(sHost, num_l, strlen(num_l), 0);
	if (SOCKET_ERROR == retVal)
	{
		//cout << "send failed!" << endl;
		closesocket(sHost); //关闭套接字
		WSACleanup(); //释放套接字资源
		return -1;
	}
	return 0;
}
// 接收服务器端的数据
char* client::recv_infor() 
{
	ZeroMemory(bufRecv, BUF_SIZE);
	recv(sHost, bufRecv, BUF_SIZE, 0); // 接收服务器端的数据， 只接收5个字符
	
	//cout << endl << "从服务器接收数据：" << bufRecv;
	//cout << "\n";
	return bufRecv;
}
//关闭
void client::close_sock()
{
	closesocket(sHost); //关闭套接字
	WSACleanup(); //释放套接字资源
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
//	//WSADATA wsd; //WSADATA变量
//	//SOCKET sHost; //服务器套接字
//	//SOCKADDR_IN servAddr; //服务器地址
//	//char buf[BUF_SIZE]; //接收数据缓冲区
//	//char bufRecv[BUF_SIZE];
//	//int retVal; //返回值
//				//初始化套结字动态库
//
//	while (true)
//	{
//
//		
//		//RecvLine(sHost, bufRecv);
//		ZeroMemory(bufRecv, BUF_SIZE);
//		recv(sHost, bufRecv, BUF_SIZE, 0); // 接收服务器端的数据， 只接收5个字符
//		cout << endl << "从服务器接收数据：" << bufRecv;
//		cout << "\n";
//	}
//	//退出
//	closesocket(sHost); //关闭套接字
//	WSACleanup(); //释放套接字资源
//	return 0;
//}