
#ifndef TESTCLENT_SOCKETCLIENT_H
#define TESTCLENT_SOCKETCLIENT_H
#include <stdio.h>
#include <tchar.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
#define  PORT 8888
#define  IP_ADDRESS "192.168.13.5"
#define NET_PACKET_DATA_SIZE 1024   
#define NET_PACKET_SIZE (sizeof(NetPacketHeader) + NET_PACKET_DATA_SIZE) * 10  

/// �������ݰ���ͷ  
struct NetPacketHeader  
{  
    unsigned short      wDataSize;  ///< ���ݰ���С���������ͷ�ͷ�����ݴ�С  
    unsigned short      wOpcode;    ///< ������  
};  
//////////////////////////////////////////////////////////////////////////  
  
  
/// ���������  
enum eNetOpcode  
{  
    REGISTER_CODE         = 1,  
    LOGIN_CODE          = 2,
    GET_SCORE_CODE          = 3,
	SCORE_CODE      = 4,
    RESULT_CODE         = 5
};  
  
  
/// ����1���������ݰ�����  
struct NetPacket_Register  
{  
    char strUserName[30];  
    char strUserPwd[30];
};  

struct NetPacket_Score
{
    char strUserName[30];  
    int nScore;
    NetPacket_Score(){}
    NetPacket_Score(char* strtemp, int score)
    {
        strcpy(strUserName, strtemp);
        nScore = score;
    }
};


struct NetPacketResult  
{  
    int result;
};   

class socketClient
{
public:
	socketClient(void);
	~socketClient(void);
public:
	bool LoginSendData(string strName, string strPwd, int nCode, int nScore = 0);
	bool GetData(int clientFd, char* pDataBuffer, const int nDataSize ); 
	bool GetScoreRankList(std::vector<NetPacket_Score*>& scoreVec);
	bool ServerConnection();
private:
	SOCKET m_clientSocket;
};
#endif
