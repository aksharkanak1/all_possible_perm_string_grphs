/*This file contains all the functions required for the generation of 
all possible combination of the strings 
*/

/*Header file */

#include<iostream>
#include<stdint.h>
#include<string.h>
#include"strings_perm_graphs.h"
#include "../common/bitSet.h"

using namespace std;

int createBucket(uint32_t num , char *str , BUCKET**pB)
{
     BUCKET *temp = NULL ;
     uint32_t i =0;

     try
     {
          temp = new BUCKET [num];
     }
     catch(std::bad_alloc& ba)
     {
       return -1; 
     } 

     *pB = temp ;
     
     for(i=0;i<num;i++)
     {
         temp[i].c = str[i];
     }

     return 0;
}


int updateGraph(BUCKET *b, char *str, int size)
{
     uint32_t temp =0;
     uint32_t i =0;
     NODE tempNode ={0,};

     if(NULL == b || NULL == str || size <=0)
         return -1;

     while (temp <size)
     {
         for (i=0;i<size;i++)
         {
             if(temp ==i)
                 continue;

            tempNode.idx = i;
            b[temp].l.push_back(tempNode);
         }
         temp++;
     }    

     return 0;
}

int generateLL(int i , char *buff, uint32_t *l, bitSet *bSet, BUCKET *b,uint32_t num )
{
    if(NULL == buff || NULL ==l||NULL == bSet || NULL ==b)
        return -1;

    //cout<<"\n"<<buff;
    std::list<NODE>::iterator p ;
    NODE temp ={0,};
   
    p=b[i].l.begin();
    
    while(p !=b[i].l.end())
    {
         temp = *p;
        
         if(0 == bSet->CheckIfBitSet(temp.idx))
         {
            buff[*l]=b[temp.idx].c;
            (*l)++;
            bSet->setBit(temp.idx);
            generateLL(temp.idx,buff,l,bSet,b,num);
         }     
         p++;
    }
   
    if(bSet->totalOnes()==num)
    {
       cout <<"\n"<<buff;
       buff[*l]='\0';
       (*l)--;
       bSet->resetBit(i);
    } 
    else 
    {
       buff[*l]='\0';
       (*l)--;
       bSet->resetBit(i);
    } 
    
    return 0; 
}


int generateHL(BUCKET *b, uint32_t num)
{
    bitSet *bSet= NULL ;
    uint32_t i =0;
    uint32_t l =0;
    char *buff= NULL ;
    
    if(NULL == b || num <0)
      return -1;


    try 
    {
       bSet = new bitSet(num);
       buff = new char[num+1];
    }
    catch (std::bad_alloc &ba)
    {
         if(NULL !=bSet)
         {
             delete bSet; 
         }
         return -1;
    }

    for(i=0;i<num;i++)
    {
       l=0;
       memset(buff, 0, num);
       buff[0]=b[i].c ;
       l++;
       bSet->setBit(i);
       generateLL(i,buff,&l,bSet,b, num);
  
    }

    return 0; 
        
}

void freeBUCKET(BUCKET **b)
{
     if(NULL == b || NULL == *b)
        return ;
 
     delete [] (*b);
     *b= NULL ;
}


int gerAllPosStrings(char * str)
{
     BUCKET *b= NULL ;
     int retVal =0;
 
     if(NULL == str)
        return -1;

    retVal = createBucket(strlen(str) , str ,&b);
    if(0!=retVal)
    {
        return -1;
    }
    
    retVal = updateGraph(b, str, strlen(str));
    if(0!=retVal)
    {
       freeBUCKET(&b); 
       return -1;
    }
   
    retVal = generateHL(b, strlen(str));
    if(0 != retVal)
    {
       freeBUCKET(&b);
       return -1; 
    }

    freeBUCKET(&b);
    return 0;
    
}
