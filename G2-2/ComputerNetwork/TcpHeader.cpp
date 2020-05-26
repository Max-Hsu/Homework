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

template <class T>
void charToType(T & dest,const char * ptrOfChar,size_t sizeOfBytes){ //only can process more than 8 bits!!
    T Tmp = 0;
    for(uint i = 0 ; i < sizeOfBytes ; i++){
        Tmp += ptrOfChar[i] << (8*(sizeOfBytes-i-1));
    }
    dest = Tmp;
}

template <class T>
void charToBit(T & dest, const char * ptrOfChar,size_t offset){ //count from right
    std::bitset <8> tmp(ptrOfChar[0]);
    dest = tmp[offset];
}

void charToTcp(struct TcpHEADER & header , char * ptrOfChar){ //this will not process the "options"
    charToType  (header.Source_Port         , ptrOfChar     ,2);
    charToType  (header.Destination_Port    , ptrOfChar+2   ,2);
    charToType  (header.Sequence_Number     , ptrOfChar+4   ,4);
    charToType  (header.Ack_Number          , ptrOfChar+8   ,4);
    charToType  (header.Data_Offset         , ptrOfChar+12  ,1);
    header.Data_Offset >>= 4;
    charToBit   (header.NS                  , ptrOfChar+12  ,0);
    charToBit   (header.CWR                 , ptrOfChar+13  ,7);
    charToBit   (header.ECE                 , ptrOfChar+13  ,6);
    charToBit   (header.URG                 , ptrOfChar+13  ,5);
    charToBit   (header.ACK                 , ptrOfChar+13  ,4);
    charToBit   (header.PSH                 , ptrOfChar+13  ,3);
    charToBit   (header.RST                 , ptrOfChar+13  ,2);
    charToBit   (header.SYN                 , ptrOfChar+13  ,1);
    charToBit   (header.FIN                 , ptrOfChar+13  ,0);
    charToType  (header.Window_Size         , ptrOfChar+14  ,2);
    charToType  (header.CheckSum            , ptrOfChar+16  ,2);
    charToType  (header.Urgent_Pointer      , ptrOfChar+18  ,2);
}
int findArgument(const char * finding ,char ** theWholeArgument , const int argc){ // this will return the index after the "-option" 
    for(int i = 0 ; i< argc ; i++){
        if(strcmp(theWholeArgument[i],finding)==0 && i+1<argc){
            return i+1;
        }
    }
    return -1;
}