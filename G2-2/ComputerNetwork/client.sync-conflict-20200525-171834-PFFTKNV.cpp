#include <iostream>
#include <bitset>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

int main(){
    char ooo[50];
    int fd = open("./hello",O_RDONLY);
    read(fd , ooo ,20);

    //so if we receive a packet , read it with char
    //concat it and use bitset to seperate?
    for(int i = 0 ; i <20 ;i++){
        //cout<<ooo[i];
        bitset<8> aaa(ooo[i]);
        cout<<aaa.to_string();
		sdsds
    }
}