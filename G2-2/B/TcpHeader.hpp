#ifndef TCP_HEADER
#define TCP_HEADER

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

#endif