#include <iostream>
#include<string.h>
extern int gerAllPosStrings(char *str);

int mp =0;

int main(int argc , char *argv[])
{
    if(3 != argc)
    {
        std::cout <<"\nInvalid number of arguments\n" ;
        return -1;
    }  


    if(0==strcmp("mp",argv[1]))
         mp =1;
        

    gerAllPosStrings(argv[2]);
}
