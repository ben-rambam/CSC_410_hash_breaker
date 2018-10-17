#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

unsigned long long hash(char *str);

void makeStr( char* str, unsigned numChars, unsigned index)
{
    unsigned numUseable = 26;
    char useable[] = "abcdefghijklmnopqrstuvwxyz";

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

        printf("Assigning %c to location %d\n", useable[subIndex], numChars-i);
        str[numChars-i] = useable[subIndex];
    }
    
}

int main( int argc, char* argv[])
{
    unsigned numChars = atof(argv[1]);
    unsigned index = atof(argv[2]);
    char str[16];

    makeStr(str, numChars, index);

    printf("String: %s  Hash: %d\n", str, hash(str));

	return 0;
}
