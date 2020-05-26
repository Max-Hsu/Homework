#include <stdio.h>
#include <iostream>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc , char ** argv){
    int index_Port;
    int index_Option;
    int socketFd;
    index_Port  =   findArgument("-o",argv,argc);
    index_Option=   findArgument("-s",argv,argc);

    char buf[1024];

    struct sockaddr_in server;
    struct sockaddr_in client;
    memset(&server,'\0',sizeof(server));
    memset(&client,'\0',sizeof(client));

    if(argc<3 || index_Port == -1){
        cerr<<"Usage : ./server -o Port -s option\n";
        exit(1);
    }
    
    socketFd = socket(AF_INET,SOCK_DGRAM,0);
    if(socketFd == -1){
        perror("socket create error!\n");
        exit(1);
    }

    server.sin_family       =   AF_INET;
    server.sin_port         =   htons(atoi(argv[index_Port]));
    server.sin_addr.s_addr  =   htonl(INADDR_ANY);

    if(bind(socketFd,(struct sockaddr *)&server,sizeof(server))<0){
        perror("socket bind error!\n");
        exit(1);
    }
    int length = sizeof(client);
    while(1){
        if ((recvfrom(socketFd, &buf, 1024, 0, (struct sockaddr*)&client, (socklen_t *)&length)) <0) {
            perror ("could not read datagram!!");
            continue;
        }
        else{
            cout<<buf<<"\n";
        }
    }
}