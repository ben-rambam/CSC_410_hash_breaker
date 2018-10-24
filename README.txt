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
                                mathews_parallel
***********************************************************************/

usage: ./mathews_parallel <hash>

to compile: 
        gcc $(CFLAGS) -o mathews_parallel hashfun.o mathews_parallel.c -lm -fopenmp



/***********************************************************************
                                brown_seq
***********************************************************************/

usage:
    ./brown_seq $(./hashbrown zab) zab

to compile:
	g++ $(CFLAGS) -o brown_seq hashfun.o brown_seq.cpp -lm


/***********************************************************************
                                ventura_seq
***********************************************************************/

Implements a "recursive" algorithm to create all permutations of a 
set of characters, determines if the hash is in the given permutation,
and returns the original string. Saves all hashes to a file if debug is turned on.

The make file will compile ventura_seq. 
Can be run as shown below.


To Generate a hash.
Usage:
./ventura_seq <string to generate hash for> (returns the hash for a given string (a-z)).

ex:
./ventura_seq abc
[*]Hash for string: abc: 193485963


To crack a hash.
Usage: ./ventura_seq <hash to find> <number of characters used to create hash

./ventura_seq 193485963 3
[*]calling permutation on string:"abcdefghijklmnopqrstuvwxyz" of length: 26
[*]Provided hash: 193485963, range of characters to be used:3

To compile:
	gcc $(CFLAGS) -o ventura_seq ventura_seq.c hashfun.o


/***********************************************************************
                                ventura_parallel
***********************************************************************/
Usage: Same as sequential.

To compile:
	gcc $(CFLAGS) -o ventura_pthreads ventura_pthreads.c hashfun.o -lpthread


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
