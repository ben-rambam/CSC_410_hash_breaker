


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//alphabet to use
const char a[] = "abcdefghijklmnopqrstuvwxyz";
unsigned long long hash(char *str);

void swap(char *x, char *y)
{

    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

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

void permutateIterative(char perm[],int pos, const char *str,FILE *fp,unsigned long long code,int range )
{
    //There is a bug somewhere in this function that is increasing running time.
    //can't figure it out.
    int slen = strlen(str);
    //printf("\nrange:%d\tpos:%d\t",range,pos);
    char k[range+1];    //account for '\0'

    if (pos ==range)
    {
        for(int i=0;i<range;i++)
        {
            //printf("i:%d\n",i);
            k[i] = perm[i];
            
        }

        fprintf(fp,"\ncalling hash on: %s\t::Result of hash:%llu\t\n",k,hash(k));
        //printf("\ncalling hash on: %s\t::Result of hash:%llu\t",k,hash(k));

        if(code==hash(k))
        {
            printf("\nfound matching string:%s\n",k);
            fprintf(fp,"\nfound matching string: %s\n",k);
           
            //need to find a way to exit early if found...recursion likely not the way to go.
            //return;
            //exit(-1);
        }
    }


    else 
    {
        for (int i = 0 ; i < slen ; i++)
        {
            //create substring
            perm[pos] = *(str+i);
            //swap();
            permutateIterative(perm, pos+1, str,fp,code,range);
            //swap();
        }
    }
}

/*
    Test case:
    pick a string: 3 lowercase chars a-g???
    baf -> find hash??

    run program: with found hash
    find that baf was the string.
    
    iterate through all possible 3 tuple values a-g and 
    feed the permutations to the hash function. 
    if the value returned matches the code: 193514003
    we have found the hash.

*/

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
    //save all hashes to a file.
    FILE *ifp=NULL;
    char *ifile = "iterative_results.txt";
 
    ifp=fopen(ifile,"w");
    if(ifp==NULL)
        printf("Error opening file: %s\n",ifile);
    else
        printf("file %s opened\n",ifile);
    printf("arg leng: %d\n",argc);

    //unsigned long long code =193514003;
   
    //determine size of alphabet set
    int len = (sizeof(a)/sizeof(a[0]))-1;
    //create a subarray
    char subarray[range];
    
    //this is not really needed.
    printf("###############HASHCRACKE STARTING UP####################");
    printf("\n[*]calling permutation on string:\"%s\" of length: %d\n",a,len);
    printf("[*]Provided hash: %llu, range of characters to be used:%d\n",code,range);
    fprintf(ifp,"[*]Provided hash: %llu, range of characters used for hash::%d\n",code,range);

    printf("\n[*]Calling function permutateIterative\n");
    fprintf(ifp,"\n[*]Calling function permutateIterative\n");
    //this is not really needed.

    //attempts to time just the permutation function.
    clock_t t;          
    t=clock();
    permutateIterative(subarray,0,a,ifp,code,range);
    t=clock()-t;

    printf("\n[*]Exiting function permutateIterative\n");
    double cpu_time_used = ((double)t)/CLOCKS_PER_SEC;
    
    //this is not really needed.
    printf("[*]time taken to crack the hash: %f\n",cpu_time_used);
    fprintf(ifp,"[*]time taken to crack the hash: %f\n",cpu_time_used);
    
    printf("############HASHCRACKE SHUTTING DOWN################\n");
    //this is not really needed.
    
    if(fclose(ifp)==0)
        printf("file %s closed\n",ifile);


    return 0;
}
