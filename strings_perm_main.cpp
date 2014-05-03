#include <iostream>

extern int gerAllPosStrings(char *str);

int main(int argc , char *argv[])
{
    if(2 != argc)
    {
        std::cout <<"\nInvalid number of arguments\n" ;
        return -1;
    }  

    gerAllPosStrings(argv[1]);
}
