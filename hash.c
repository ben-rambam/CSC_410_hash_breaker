#include <stdio.h>
#include <string.h>
#include <unistd.h>

unsigned long long hash(char *str);


int main(int argc, char* argv[])
{
    if( argc != 2)
        return 1;
    printf("%lld\n", hash(argv[1]));

	return 0;
}
