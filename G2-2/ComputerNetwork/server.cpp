#include <stdio.h>
#include <iostream>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <vector>
#include "TcpHeader.hpp"
#include "server.hpp"
using namespace std;

int main(int argc , char ** argv){
    srand(time(NULL));
    int index_Port;
    int index_Option;
    int socketFd;
    uint32_t My_Sequence_Number = (rand()%10000)+1;
    index_Port  =   findArgument("-o",argv,argc);
    index_Option=   findArgument("-s",argv,argc);

    char buf[MSS];

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
    char ok[] = "ok\0";
    char receiveIP[20];
    char SendingChar[MSS];
    vector<struct Bind> ListBindDone;
    vector<struct Bind> ListBindPending;

    while(1){
        if ((recvfrom(socketFd, &buf, MSS, 0, (struct sockaddr*)&client, (socklen_t *)&length)) <0) {
            perror ("recv error!");
            continue;
        }
        else{
            //when enter here , the server doesn't know the request(if the connection had already establish or not)
            struct TcpHEADER Packet;
            struct TcpHEADER ReturnPacket;
            charToTcp(Packet,buf);
            displayPacket(Packet);
            if(Packet.SYN == 1){ //a client want to estab a connection
                cout<<"hi SYNC here\n";
                struct Bind DataBind;
                int FindSameBind = 0;
                DataBind.ClientIp   = client.sin_addr.s_addr;
                DataBind.ClientPort = Packet.Source_Port;
                
                for(int i=0 ; i<ListBindDone.size(); i++){
                    if(ListBindDone[i].ClientIp == DataBind.ClientIp && ListBindDone[i].ClientPort == DataBind.ClientPort){
                        FindSameBind = 1;
                        break;
                    }
                }

                if(!FindSameBind){
                    //send back ack for init connection
                    cout<<"first sync\n";
                    ListBindPending.push_back(DataBind);
                    ReturnPacket.Source_Port        =   Packet.Destination_Port;
                    ReturnPacket.Destination_Port   =   Packet.Source_Port;
                    ReturnPacket.Sequence_Number    =   My_Sequence_Number;
                    ReturnPacket.Ack_Number         =   Packet.Sequence_Number+1;
                    ReturnPacket.Data_Offset        =   0;
                    ReturnPacket.ACK                =   1;
                    makePacket(ReturnPacket,SendingChar,sizeof(SendingChar));
                    displayPacket(ReturnPacket);
                    if (sendto(socketFd, (const char *)SendingChar, MSS, 0, (struct sockaddr*)&client, length) < 0) {
                        perror("send error!");
                        continue;
                    }
                }
            }
            else{   //client maybe synced , sync_pending , or just random coming
                struct Bind DataBind;
                int FindSameBindDone = 0;
                int FindSameBindPending = 0;
                int FindSameBindPendingIndex = -1;
                DataBind.ClientIp   = client.sin_addr.s_addr;
                DataBind.ClientPort = Packet.Source_Port;
                
                for(int i=0 ; i<ListBindDone.size(); i++){
                    if(ListBindDone[i].ClientIp == DataBind.ClientIp && ListBindDone[i].ClientPort == DataBind.ClientPort){
                        FindSameBindDone = 1;
                        break;
                    }
                }
                for(int i=0 ; i<ListBindPending.size(); i++){
                    if(ListBindPending[i].ClientIp == DataBind.ClientIp && ListBindPending[i].ClientPort == DataBind.ClientPort){
                        FindSameBindPending = 1;
                        FindSameBindPendingIndex = i;
                        break;
                    }
                }

                if(FindSameBindDone){       //already establish connection , so this is normal operation //should provide some "ls" for user to choose file?
/*                     //send back ack for init connection
                    ReturnPacket.Source_Port        =   Packet.Destination_Port;
                    ReturnPacket.Destination_Port   =   Packet.Source_Port;
                    ReturnPacket.Sequence_Number    =   My_Sequence_Number;
                    ReturnPacket.Ack_Number         =   Packet.Sequence_Number+1;
                    ReturnPacket.Data_Offset        =   0;
                    ReturnPacket.ACK                =   1;
                    makePacket(ReturnPacket,SendingChar,sizeof(SendingChar));
                    if (sendto(socketFd, (const char *)SendingChar, sizeof(ok), 0, (struct sockaddr*)&client, length) < 0) {
                        perror("send error!");
                        continue;
                    } */
                    cout<<"est done.. good job!!\n";
                }
                else if(FindSameBindPending){
                    if(Packet.ACK == 1 && Packet.Ack_Number == (My_Sequence_Number +1)){
                        ListBindDone.push_back(ListBindPending[FindSameBindPendingIndex]);
                        ListBindPending.erase(ListBindPending.begin()+FindSameBindPendingIndex);
                        cout<<"bind ok!!\n";
                    }
                }


            }
            
            /*cout<<inet_ntop(AF_INET,&(client.sin_addr),receiveIP,INET_ADDRSTRLEN)<<"\t";
            cout<<Packet.Source_Port     <<"\t";
            cout<<Packet.Destination_Port<<"\t";
            cout<<Packet.Sequence_Number <<"\t";
            cout<<Packet.Ack_Number      <<"\t";
            cout<<int(Packet.Data_Offset)<<"\t";
            cout<<"\n"; */

        }
    }
}