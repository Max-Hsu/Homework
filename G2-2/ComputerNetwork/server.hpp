#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

struct Bind{
    //uint32_t ServerIp;
    //uint16_t ServerPort;
    uint32_t ClientIp;
    uint16_t ClientPort;
};

struct BindWithPthread{
    uint32_t ClientIP;
    uint16_t ClientPort;
    pthread_t   threadID;
};

struct StructureForPthread{
    struct TcpHEADER Header;
    char * ReceivingBUF_PTH;
};