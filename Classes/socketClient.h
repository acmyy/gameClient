#include <stdio.h>
#include <tchar.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string.h>
using namespace std;
#define  PORT 8888
#define  IP_ADDRESS "192.168.13.181"
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
    NET_TEST1           = 1,  
};  
  
/// ����1���������ݰ�����  
struct NetPacket_Test1  
{  
    char username[20];  
    char userpwd[20];  
	int nCodeNum;
};  

struct NetPacketResult  
{  
    int result;
};   
class socketClient
{
public:
	bool LoginSendData(string strName, string strPwd, int nCode);
	bool GetData(int clientFd, char* pDataBuffer, const int nDataSize ); 
};