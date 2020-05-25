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
}

#endif