#include<iostream>
#include<list>

typedef struct Node
{
    int32_t idx ;
}NODE ;

typedef struct bucket
{
    char c;
    std::list<NODE> l;
} BUCKET ; 

