# CSC_410_hash_breaker

The makefile is set up to make four programs:
* hashbrowns
* mathews_seq
* brown_seq

/***********************************************************************
                                mathews_seq 
***********************************************************************/

does an exhaustive search to find the string that produced
a specific hash

usage: ./mathews_seq <hash>

to compile: 
	gcc $(CFLAGS) -o mathews_seq hashfun.o mathews_seq.c -lm



/***********************************************************************
                                brown_seq
***********************************************************************/

usage:
    ./brown_seq $(./hashbrown zab) zab

to compile:
	g++ $(CFLAGS) -o brown_seq hashfun.o brown_seq.cpp -lm



/***********************************************************************
                                hashbrowns
***********************************************************************/

returns the hash for a string given as a command line argument

usage: ./hashbrowns <string>

to compile:
	gcc $(CFLAGS) -o hashbrowns hashfun.o hashbrowns.c
    


/***********************************************************************
                                combinations
***********************************************************************/
Use hashbrowns with the sequential solvers as follows

./mathews_seq $(./hashbrowns cba)
./brown_seq $(./hashbrowns cba) cba

This will create the hash for "cba" and pass that as the argument to 
the solver which will then try to determine the corresponding string

