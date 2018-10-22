#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

const unsigned numUseable = 26;
const char useable[] = "abcdefghijklmnopqrstuvwxyz";
unsigned long long hash(char *str);

void makeStr( char* str, unsigned numChars, unsigned index)
{
    if( index >= pow(numUseable, numChars) )
    {
        printf("Error: Index too big\n");
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
        printf("Error: incorrect usage\nUsage: ./mathews_seq hash\n");
        return 1;
    }
    unsigned long long inputHash = atoll(argv[1]);
    const unsigned maxSize = 16;
    char solutionStr[maxSize];
    unsigned long long solutionHash = 0;

    for( unsigned numChars = 1; numChars <= maxSize; numChars++)
    {
        unsigned maxIndex = pow(numUseable, numChars);
        long long globIndex = -1;
        #pragma omp parallel
        {
            unsigned long long tempHash = 0;
            char tempStr[maxSize];
            long long myIndex = 0;
            #pragma omp critical
            {
                myIndex = ++globIndex;
            }
            while( solutionHash == 0 && myIndex < maxIndex)
            {
                makeStr(tempStr, numChars, myIndex);
                tempHash = hash(tempStr);
                if( tempHash == inputHash )
                {
                    solutionHash = tempHash;
                    strcpy(solutionStr, tempStr);
                }
                #pragma omp critical
                {
                    myIndex = ++globIndex;
                }
            }
        }
        if( solutionHash == inputHash )
            break;
    }

    printf("String: %s  Hash: %lld\n", solutionStr, hash(solutionStr));

	return 0;
}
