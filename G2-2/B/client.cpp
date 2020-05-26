#include <stdio.h>
#include <iostream>
#include <bitset>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "TcpHeader.hpp"
using namespace std;

int main(int argc , char ** argv){
    int index_IP;
    int index_Port;
    int index_Option;
    int socketFd;
    index_IP    =   findArgument("-i",argv,argc);
    index_Port  =   findArgument("-o",argv,argc);
    index_Option=   findArgument("-s",argv,argc);

    struct sockaddr_in client;
    memset(&client,'\0',sizeof(client));

    if(argc<5 || index_IP == -1 || index_Port == -1){
        cerr<<"Usage : ./client -i IP_Connect_to -o Port -s option\n";
        exit(1);
    }
    socketFd = socket(AF_INET,SOCK_DGRAM,0);
    if(socketFd == -1){
        perror("socket create error!\n");
        exit(1);
    }


    client.sin_family       =   AF_INET;
    client.sin_port         =   htons(atoi(argv[index_Port]));
    client.sin_addr.s_addr  =   inet_addr(argv[index_IP]);

    char hello[] = "hello\0";
    sendto(socketFd, (const char *)hello, strlen(hello), 0, (const struct sockaddr *) &client, sizeof(client)); 

    /*     char ooo[50];
    
    int fd = open("./hello",O_RDONLY);
    read(fd , ooo ,20); */
    /*
    //so if we receive a packet , read it with char
    //concat it and use bitset to separate?
    for(int i = 0 ; i <20 ;i++){
        //cout<<ooo[i];
        bitset<8> aaa(ooo[i]);
        cout<<aaa.to_string();
    }
    */

   //uint16_t sss = (ooo[0]<<8 )+ ooo[1];
    /*    uint32_t sss;
    charToType(sss,ooo,4);
    char ssa = 15;
    bool as;
    charToBit(as,&ssa,4);
    cout<<ooo[0]<<"\n";
    cout<<ooo[1]<<"\n";
    cout<<as<<"\n"; */


}