#ifndef __CLIENT_H__
#define __CLIENT_H__
#define BUF_SIZE 64
#include"cocos2d.h"
#include "winsock2.h"
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996) //必须加上
USING_NS_CC;
class client:public cocos2d::Layer
{
public:
	//const int BUF_SIZE = 64;
	char num = 48;
	const char * num_l = &num;
	WSADATA wsd; //WSADATA变量
	SOCKET sHost; //服务器套接字
	SOCKADDR_IN servAddr; //服务器地址
	char buf[BUF_SIZE]; //接收数据缓冲区
	char bufRecv[BUF_SIZE];
	int retVal; //返回值
	//BOOL RecvLine(SOCKET s, char* buf); //读取一行数据

	int init_sock();//初始化套结字动态库
	int create_sock();//创建套接字
	void init_serv();//设置服务器地址
	int connect_serv();	//连接服务器

	char send_infor();//向服务器发送数据
	char* recv_infor();// 接收服务器端的数据

	void close_sock();//关闭
	CREATE_FUNC(client);
	virtual bool init();

	//int main(int argc, char* argv[]);
};
#endif // !__CLIENT_H__

