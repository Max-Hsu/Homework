#ifndef TCP_HEADER
#define TCP_HEADER

#define RTT 15
#define MSS 1           *1000
#define Threshold 64    *1000
#define UDP_MAX 64000
#define Buffer_Size 512 *1000

struct TcpHEADER{
    uint16_t        Source_Port;
    uint16_t        Destination_Port;
    uint32_t        Sequence_Number;
    uint32_t        Ack_Number;
    unsigned char   Data_Offset;
    bool            NS;
    bool            CWR;
    bool            ECE;
    bool            URG;
    bool            ACK;
    bool            PSH;
    bool            RST;
    bool            SYN;
    bool            FIN;
    uint16_t        Window_Size;
    uint16_t        CheckSum;
    uint16_t        Urgent_Pointer;
};

template <class T>
void charToType(T & dest,const char * ptrOfChar,size_t sizeOfBytes);
template <class T>
void charToBit(T & dest, const char * ptrOfChar,size_t offset);
void charToTcp(struct TcpHEADER & header , char * ptrOfChar);
int findArgument(const char * finding ,char ** theWholeArgument , const int argc);
template <class T>
void typeToChar(const T & data, char * destptrOfChar);
template <class T>
void bitToChar(const T & data, char * ptrOfChar,size_t offset);
void makePacket(const struct TcpHEADER Header , char * packetChar , size_t size);
void displayPacket(const struct TcpHEADER Header);
#endif