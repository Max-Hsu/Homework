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
    srand(time(NULL));
    int index_IP;
    int index_Port;
    int index_Option;
    int index_File;
    int socketFd;
    uint16_t My_Source_Port = rand()%65536;
    uint32_t My_Sequence_Number = (rand()%10000)+1;
    char RecevingBUF[UDP_MAX];
    index_IP    =   findArgument("-i",argv,argc);
    index_Port  =   findArgument("-o",argv,argc);
    index_Option=   findArgument("-s",argv,argc);
    index_File  =   findArgument("-f",argv,argc);

    struct sockaddr_in client;
    struct sockaddr_in server;
    memset(&client,'\0',sizeof(client));
    memset(&server,'\0',sizeof(server));

    if(argc<5 || index_IP == -1 || index_Port == -1 || index_File ==-1 || argc<atoi(argv[index_File])+7){
        cerr<<"Usage : ./client -i IP_Connect_to -o Port -s option -f filecount file1 file2 ...\n";
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

    server.sin_family       =   AF_INET;
    server.sin_port         =   htons(atoi(argv[index_Port]));
    server.sin_addr.s_addr  =   htonl(INADDR_ANY);

    int length = sizeof(client);
    char hello[] = "hello\0";

    char conversion[40];
    memset(conversion,'\0',40);
    /*
    for(int i=0 ;i<40;i++){
        printf("%d",int(conversion[i]));
    }
    printf("\n");
    */
    struct TcpHEADER SendindPacket;
    struct TcpHEADER RecvingPacket;
    //let's do three way handshake

    SendindPacket.Source_Port          =   My_Source_Port;
    SendindPacket.Destination_Port     =   atoi(argv[index_Port]);
    SendindPacket.Sequence_Number      =   My_Sequence_Number;
    SendindPacket.Ack_Number           =   0;
    SendindPacket.Data_Offset          =   0;
    SendindPacket.SYN                  =   1;
    makePacket(SendindPacket,conversion,40);
    //sending sync
    if(sendto(socketFd, conversion, sizeof(conversion), 0, (const struct sockaddr *) &client, sizeof(client))<0){
        perror("send error!");
    }
    if(recvfrom(socketFd, &RecevingBUF, UDP_MAX, 0, (struct sockaddr*)&server, (socklen_t *)&length)<0){
            perror("recv error!");
    }
    else{
        charToTcp(RecvingPacket,RecevingBUF);
        displayPacket(RecvingPacket);
    }
    SendindPacket.Source_Port          =   My_Source_Port;
    SendindPacket.Destination_Port     =   atoi(argv[index_Port]);
    SendindPacket.Sequence_Number      =   ++My_Sequence_Number;
    SendindPacket.Ack_Number           =   RecvingPacket.Sequence_Number+1;
    SendindPacket.Data_Offset          =   0;
    SendindPacket.SYN                  =   0;
    SendindPacket.ACK                  =   1;
    displayPacket(SendindPacket);
    makePacket(SendindPacket,conversion,40);
    if(sendto(socketFd, conversion, sizeof(conversion), 0, (const struct sockaddr *) &client, sizeof(client))<0){
        perror("send error!");
    }


    SendindPacket.Source_Port          =   My_Source_Port;
    SendindPacket.Destination_Port     =   atoi(argv[index_Port]);
    SendindPacket.Sequence_Number      =   ++My_Sequence_Number;
    SendindPacket.Ack_Number           =   RecvingPacket.Sequence_Number+1;
    SendindPacket.Data_Offset          =   0;
    SendindPacket.SYN                  =   0;
    SendindPacket.ACK                  =   1;
    displayPacket(SendindPacket);
    makePacket(SendindPacket,conversion,40);
    if(sendto(socketFd, conversion, sizeof(conversion), 0, (const struct sockaddr *) &client, sizeof(client))<0){
        perror("send error!");
    }
    //requesting file !!
    for(int i = 0 ;i <atoi(argv[index_File]);i++){
        cout<<"requesting\t"<<argv[index_File+i+1]<<"\n";
        SendindPacket.Source_Port          =   My_Source_Port;
        SendindPacket.Destination_Port     =   atoi(argv[index_Port]);
        SendindPacket.Sequence_Number      =   ++My_Sequence_Number;
        SendindPacket.Data_Offset          =   0;
        SendindPacket.SYN                  =   0;
        
    }


}