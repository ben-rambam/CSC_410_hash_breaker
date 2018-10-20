to compile brown_seq:

g++ -o brown_seq hashfun.o brown_seq.c

to compile hashbrowns:

gcc -o hashbrown hashfun.o hashbrowns.c

to execute:

./brown_seq $(./hashbrown zab) zab



