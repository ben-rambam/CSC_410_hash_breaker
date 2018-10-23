#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

const unsigned numUseable = 26;
const char useable[] = "abcdefghijklmnopqrstuvwxyz";
unsigned long long hash(char *str);

void makeStr( char* str, unsigned long long index)
{
    unsigned numChars = 0;
    for( numChars = 1; numChars < 16; numChars++)
    {
        unsigned long long temp = pow(numUseable, numChars);
        if( index >= temp)
        {
            index -= temp;
        }
        else
            break;
    }

    if( index >= pow(numUseable, numChars) )
    {
        
        printf("Error: Index too big\n");
        printf("index: %lld numChars: %d", index, numChars);
        str = "";
        return;
    }
    str[numChars] = '\0';
    for( unsigned i = 1; i <= numChars; i++)
    {
        unsigned subIndex = index % numUseable;
        index = index / numUseable;

        #ifdef DEBUG
            printf("Assigning %c to location %d\n", useable[subIndex], numChars-i);
        #endif
        str[numChars-i] = useable[subIndex];
    }
    
}

int main( int argc, char* argv[])
{
    if( argc !=2 )
    {
        printf("Error: incorrect usage\nUsage: ./mathews_seq <hash>\n");
        return 1;
    }
    unsigned long long inputHash = atoll(argv[1]);
    const unsigned maxSize = 11;
    unsigned size = maxSize;
    //if( size > 11 )
    //{
    //    printf("Error: index will overflow unsigned long long\n");
    //    return 1;
    //}
    char solutionStr[maxSize+1];
    unsigned long long solutionHash = 0;

    //unsigned long long maxIndex = pow(numUseable, maxSize);
    unsigned long long globIndex = 0;
    unsigned long long upperBound = 0;
    for( unsigned i = 1; i < size+1; i++)
    {
        upperBound += pow(numUseable, i);
    }
    #ifdef DEBUG
    printf("upperBound: %lld \n", upperBound);
    #endif
    makeStr(solutionStr, upperBound-1);
    #ifdef DEBUG
    printf("upperStr: %s \n", solutionStr);
    #endif
    unsigned long long upperHash = hash(solutionStr);
    #ifdef DEBUG
    printf("upperHash: %lld \n", upperHash);
    #endif
    unsigned long long lowerBound = 0;
    #ifdef DEBUG
    printf("lowerBound: %lld \n", lowerBound);
    #endif
    makeStr(solutionStr, lowerBound);
    #ifdef DEBUG
    printf("lowerStr: %s \n", solutionStr);
    #endif
    unsigned long long lowerHash = hash(solutionStr);
    #ifdef DEBUG
    printf("lowerHash: %lld \n", lowerHash);
    #endif
    unsigned long long interval;

    #pragma omp parallel
    {
        unsigned long long tempHash = 0;
        char tempStr[maxSize+1];
        unsigned long long myIndex = 0;
        unsigned long long numThreads = omp_get_num_threads();
        interval = (upperBound - lowerBound)/(numThreads-1) + 1;
        #pragma omp critical
        {
            myIndex = lowerBound + (globIndex++*interval);
            #ifdef DEBUG
            printf("myIndex: %lld \n", myIndex);
            #endif
        }
        while( solutionHash == 0 && lowerBound < upperBound)
        {
            makeStr(tempStr, myIndex);
            tempHash = hash(tempStr);
            if( tempHash == inputHash )
            {
                solutionHash = tempHash;
                strcpy(solutionStr, tempStr);
            }
            #pragma omp critical (lower)
            if( tempHash > lowerHash && tempHash < inputHash )
            {
                lowerBound = myIndex;
                lowerHash = tempHash;
            }
            #pragma omp critical (upper)
            if( tempHash < upperHash && tempHash > inputHash )
            {
                upperBound = myIndex;
                upperHash = tempHash;
            }
            #pragma omp barrier
            #pragma omp single 
            {
                interval = (upperBound - lowerBound)/(numThreads+1) + 1;
                globIndex = 1;
            }
            #pragma omp critical (index)
            {
                myIndex = lowerBound + (globIndex++*interval);
            }
        }
    }
    
    if( solutionHash == 0 )
    {
        printf("Couldn't find string in range\n");
        return 1;
    }
    printf("String: %s  Hash: %lld\n", solutionStr, hash(solutionStr));

	return 0;
}
