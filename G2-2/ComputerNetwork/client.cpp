#include <iostream>
#include <bitset>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/ip.h>
#include "TcpHeader.hpp"
using namespace std;
template <class T>
void charToType(T & dest,const char * ptrOfChar,size_t sizeOfBytes){ //only can process more than 8 bits!!
    T Tmp = 0;
    for(int i = 0 ; i < sizeOfBytes ; i++){
        Tmp += ptrOfChar[i] << (8*(sizeOfBytes-i-1));
    }
    dest = Tmp;
}
template <class T>
void charToBit(T & dest, const char * ptrOfChar,size_t offset){ //count from right
    bitset <8> tmp(ptrOfChar[0]);
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
int main(){
    char ooo[50];
    
    int fd = open("./hello",O_RDONLY);
    read(fd , ooo ,20);
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