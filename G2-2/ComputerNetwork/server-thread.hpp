#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include "TcpHeader.hpp"
#include "server.hpp"
#include <string.h>
#include <vector>
void *server_thread(void * args);
struct PassingToThread{
    struct Bind         Bind_data;
    pthread_t           tid;
    pthread_cond_t      cond_signal;
    pthread_mutex_t     lock;
    char *              ReceivingBUF_PTH;
    struct TcpHEADER    Header;
    volatile int        readOK;
    bool                SackOption;
};

struct unpackOption{
    uint8_t options;
    uint8_t parameters;
};