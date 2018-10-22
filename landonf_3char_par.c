#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


//vars to count function run time
struct timeval t0;
struct timeval t1;
float elapsed;

//timecount function
float timedifference_msec(struct timeval t0, struct timeval t1)
{
return (t1.tv_sec - t0.tv_sec)*1000.0f + (t1.tv_usec) / 1000.0f;
}


//this implimentation only works on strings of 3 characters lowercase a-z
//change this to change the hash to decode.
unsigned long long hashNum = 193507093;

int match = 0;
int stringLength = 3;
int globX;
char string[] = "aaa";
int numThreads = 26;

unsigned long long hash(char *str);

void *thread(void *threadParam)
{
   unsigned long long num;
   char stringCopy[stringLength];

   for(int i=0;i<stringLength;++i){
      stringCopy[i] = string[i];
   }

   char character[] = "a";
   int threadID;
   threadID = (long) threadParam;
   character[0] = character[0]+threadID;


   for(stringCopy[0]=character[0];stringCopy[0]!=stringCopy[0]+1;++stringCopy[0]){
                for(stringCopy[1]='a';stringCopy[1]<123;++stringCopy[1]){
                        for(stringCopy[2]='a';stringCopy[2]<123;++stringCopy[2]){
                                if(match==1){
	 				pthread_exit(NULL);
				}
                                num = hash(stringCopy);
                                //printf("%lld\n", num);
                                if (num==hashNum){
                                        match = 1;
					printf("ATTENTION!!! Found the hash string: ");
                                        for(int i=0;i<stringLength;++i){
                                                printf("%c", stringCopy[i]);
                                        }
					printf("\n");
                                        return 0;
                                }
                        }
                }
   }

   pthread_exit(NULL);
}


int main()
{

void *status;
int i,j,k = 0;
int flag = 0;
pthread_t threadNum[26];

//start clock
gettimeofday(&t0, 0);

  for ( i = 0; i < 26; ++i){
//     printf("Creating thread %d\n", i);
     pthread_create( &threadNum[i], NULL, thread, (void *)(long) i );
  }

  for ( i = 0; i < 5; ++i)
  {
     pthread_join( threadNum[i], &status );
  }
//stopclock
gettimeofday(&t1, 0);
elapsed = elapsed + timedifference_msec(t0,t1);
elapsed = elapsed/1000;
printf("%f seconds\n", elapsed);

return 0;
}