#include <stdio.h>
#include <string.h>
#include <unistd.h>


unsigned long long hash(char *str);

//change this number to change the hash to decrypt.
//this program only works on lowercase characters from a-z.
unsigned long long hashNum = 193507093;

int main()
{

char string[] = "aaa";
int i,j,k = 0;
int flag = 0;
unsigned long long num;

while(flag==0){
	for(string[0]='a';string[0]<123;++string[0]){
		for(string[1]='a';string[1]<123;++string[1]){
			for(string[2]='a';string[2]<123;++string[2]){
				//printf("%c", string[0]);
				num = hash(string);
				//printf("%lld\n", num);
				if (num==hashNum){
					flag = 1;
					for(i=0;i<3;++i){
						printf("%c", string[i]);
					}
					printf("\n");
					return 0;
				}
			}
		}
	}
}


return 0;
}