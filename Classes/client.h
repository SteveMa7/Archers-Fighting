#ifndef __CLIENT_H__
#define __CLIENT_H__
#define BUF_SIZE 64
#include"cocos2d.h"
#include "winsock2.h"
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996) //�������
USING_NS_CC;
class client:public cocos2d::Layer
{
public:
	//const int BUF_SIZE = 64;
	char num = 48;
	const char * num_l = &num;
	WSADATA wsd; //WSADATA����
	SOCKET sHost; //�������׽���
	SOCKADDR_IN servAddr; //��������ַ
	char buf[BUF_SIZE]; //�������ݻ�����
	char bufRecv[BUF_SIZE];
	int retVal; //����ֵ
	//BOOL RecvLine(SOCKET s, char* buf); //��ȡһ������

	int init_sock();//��ʼ���׽��ֶ�̬��
	int create_sock();//�����׽���
	void init_serv();//���÷�������ַ
	int connect_serv();	//���ӷ�����

	char send_infor();//���������������
	char* recv_infor();// ���շ������˵�����

	void close_sock();//�ر�
	CREATE_FUNC(client);
	virtual bool init();

	//int main(int argc, char* argv[]);
};
#endif // !__CLIENT_H__

