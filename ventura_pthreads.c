/************************************************************************
 * A pthreads implementation of Hash Breaker using recursion.
 ***********************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

/************************************************************************
 * Pthreads functionality,  constants, function headers, data structure.
 ***********************************************************************/

pthread_barrier_t barr;
pthread_mutex_t lock;

//number of threads
#define NUMT 20

////////
//alphabet/string to use for hash
const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";
const int STRING_LENGTH = strlen(ALPHABET);

unsigned long long hash(char *str);
void *startThread();
void startHashBreaker(unsigned long long hash, int hashLength);

/*
    Structure that contains:
    A threadID,hash to break, Range of characters,index into string.
*/


typedef struct
{
    unsigned long id;       //determines index into string and keeps track of itself/
    int index;                  //what index it's permutating
    int range;                  //Lenght of string used for hash
    unsigned long long code;    //which hash to break
} HashBreaker;

/************************************************************************
 * Function defintions.
 ***********************************************************************/


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

void permutate(char perm[],int pos,unsigned long long code,int range,HashBreaker *s)//unsigned long id)
{
    
    //Base case: if we have a string of length range.
    if (pos ==range)
    {   
        //this should be a critical or private section???
        //multiple threads accessing it at the same time will lead to race conditions.

        //printf("perm:%s by TID:%lu\n",perm,s->id);
        pthread_mutex_lock(&lock);
        perm[pos]='\0';
        pthread_mutex_unlock(&lock);

        if(code==hash(perm))
        {
            printf("\nfound matching string:%s by TID:%lu\n",perm,s->id);
            exit(1);    //Instead of running all permutations exit when hash found
                        //to save CPU cycles/cutdown on running time.
        }
    }

    //Recursive case
    else 
    {
         /*
            s->index will permutate ALPHABET[INDEX]
            This divides different character set between threads
            in a static manner. Also instead of one thread performing
            all permutations each thread will pick one block to permutate.
        */

        for (int i = s->index ; i < STRING_LENGTH ; i++)
        {
            #ifdef DEBUG
                printf("TID: %lu is permuting character: %c\n",s->id,ALPHABET[s->index]);
            #endif
            //create substring
            //Don't want multiple threads accesing this at once.
            pthread_mutex_lock(&lock);
            perm[pos] = *(ALPHABET+i);
            pthread_mutex_unlock(&lock);
            permutate(perm, pos+1,code,range,s);    
           
        }
    }
    
}

/*
    Fun startThread: Starts the threads and calls permutate function
        to crack hashes, terminates thread once work is done.

        Creates a pointer to HashBreaker struct and calls required function
        to crack hashes.

    Args: N/A.
    Returns: N/A.
*/

void *startThread(void* param)
{
    #ifdef DEBUG
        printf("in startThread\n");
    #endif

    HashBreaker *breaker = (HashBreaker *) param;
    char subarray[breaker->range];      //create a subarray
                                        //controls lenght of character for hash.

    //int pos =0;           //always starts at 0 but maybe some test case 
                            //calls for it to be something else?
    #ifdef DEBUG
    {
        printf("Starting thread %ld\tcode:%llu...\t",breaker->id,breaker->code);
        printf("Index %d\trange:%d...\n",breaker->index,breaker->range);
    }
    #endif
    permutate(subarray,0,breaker->code,breaker->range,breaker);
    pthread_exit(NULL);
}

/*

    Func startHashBreaker: sets ups the structure for a hashBreaker thread and 
    calls routing to start thread.
    
    Args:
        unsigned long long hashCode: The hash to crack.
        int hashLength: indicates length of characters used to create hash.
    
    Returns: N/A.

*/

void startHashBreaker(unsigned long long hashCode, int hashLength)
{
    pthread_t tid[NUMT];
    pthread_mutex_init(&lock,NULL);
    pthread_barrier_init(&barr,NULL,NUMT);
    int thread=-1;

     /*
        Dispatches permutation to the ID:
        each ID will compute a different section of the string.
        by using modulo N we might be able to accomplish this.

        tid %len(alphabet)
        tid%26 = congruence class.
    */

    //create a struct of type hash breaker
    HashBreaker hStruct[NUMT];

    for(long i=0;i<NUMT;i++)
    {
        #ifdef DEBUG
            printf("spining up thread:%ld\n",i);
        #endif
       
        hStruct[i].id = i;                  //initialize struct with ThreadID
        hStruct[i].range=hashLength;        //length of characters to break: range
        hStruct[i].code = hashCode;         //hash to crack
        
        thread =(i%NUMT);                   //Gets which index into string this thread will crack.
                                            //ALPHABET[index] -> string="ABD" -> if index=0;ALPHABET[A]
        hStruct[i].index = thread;  
        pthread_create(&tid[i],NULL,startThread,(void*)&(hStruct[i]));
       
    }

    for(int i = 0; i < NUMT; i++)
    {
        pthread_join(tid[i],NULL);
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
    char *ullptr=NULL;
    if(argc==3)
    {
        //this properly converts hash tu unsigned long long. prev code was causing int overflows.
        code = strtoul(argv[1],&ullptr,10); 
        range =atoi(argv[2]);      
    } 

    //this is not really needed.
    printf("###############HASH-CRACKER STARTING UP####################");
    printf("\n[*]calling permutation on string:\"%s\" of length: %d\n",ALPHABET,STRING_LENGTH);
    printf("[*]Provided hash: %llu, range of characters to be used:%d\n",code,range);
    printf("Using: %d threads\n",NUMT);
    startHashBreaker(code,range);

    printf("############HASH-CRACKER SHUTTING DOWN################\n");

    return 0;
}