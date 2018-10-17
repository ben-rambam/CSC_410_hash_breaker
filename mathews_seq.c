#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

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
    unsigned long long tempHash = 0;
    const unsigned maxSize = 16;
    char str[maxSize];

    for( unsigned numChars = 1; numChars <= maxSize; numChars++)
    {
        unsigned maxIndex = pow(numUseable, numChars);
        for( unsigned i = 0; i < maxIndex; i++ )
        {
            makeStr(str, numChars, i);
            tempHash = hash(str);
            if( tempHash == inputHash)
                break;
        }
        if( tempHash == inputHash)
            break;
    }

    printf("String: %s  Hash: %lld\n", str, hash(str));

	return 0;
}
