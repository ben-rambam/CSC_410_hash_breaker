#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//alphabet to use
const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";
unsigned long long hash(char *str);
const int STRING_LENGTH = strlen(ALPHABET);

/*
************************************************************************
*   Permutate: generates permutations for a given alphabet.
*   Implemented with recursion but it contains a few bugs and running time
*       is not efficient.
*
*   Arguments:
*       Char subarray[]: Range of substring of permutations for the hash.
*       const char *str: "Alphabet" or character set to be used to generate permutations.
*       unsigned long long code: The hash to find. 
*       int range: Range of characters used for the hash.
*    
*   Returns: N/A
************************************************************************
*/

//void permutateIterative(char perm[],int pos, const char *str,unsigned long long code,int range )
void permutate(char perm[],int pos,unsigned long long code,int range )
{
    if (pos ==range)
    {
        perm[pos]='\0';
        //printf("perm:%s\n",perm);
        if(code==hash(perm))
        {
            printf("\nfound matching string:%s\n",perm);
            //need to find a way to exit early if found...recursion likely not the way to go.
            //exit(1); //not a clean to exit but obv works.
        }
    }

    else 
    {
        for (int i = 0 ; i < STRING_LENGTH ; i++)
        {
            //create substring
            perm[pos] = *(ALPHABET+i);
            permutate(perm, pos+1,code,range);
        }
    }
}


/*
************************************************************************
*   Usage: 
*        Pass a string or set of characters to get a hash. 
*        Pass a hash and a number indicating number of characters to use
*        to find the desired hash.
*       
*   
*
************************************************************************
*/
int main(int argc, char *argv[])
{

    if(argc<2 || argc >3)
    {
        printf("Usage: %s <string to generate hash for>\n",argv[0]);
        printf("Usage: %s<hash to find> <number of characters>\n", argv[0]);
        return(-1);
    }

    if(argc==2)
    {
        printf("[*]Hash for string: %s: %llu\n",argv[1],hash(argv[1]));
        return 0;       
    }
    
    
    unsigned long long code;    //hash to find
    int range;                  //number of characters used for string used to create hash.

    if(argc==3)
    {
        code = atoi(argv[1]);
        range =atoi(argv[2]);      
    } 

    char subarray[range];                     //create a subarray
    
    //this is not really needed.
    printf("###############HASHCRACKE STARTING UP####################");
    printf("\n[*]calling permutation on string:\"%s\" of length: %d\n",ALPHABET,STRING_LENGTH);
    printf("[*]Provided hash: %llu, range of characters to be used:%d\n",code,range);

    //attempts to time just the permutation function.
    clock_t t;          
    t=clock();
    permutate(subarray,0,code,range);
    t=clock()-t;

    printf("\n[*]Exiting function permutateIterative\n");
    double cpu_time_used = ((double)t)/CLOCKS_PER_SEC;
    
    //this is not really needed.
    printf("[*]time taken to crack the hash: %f\n",cpu_time_used);
    printf("############HASHCRACKE SHUTTING DOWN################\n");

    return 0;
}
