# CSC_410_hash_breaker

The makefile is set up to make two programs:
* hash
* mathews_seq

hash returns the hash for a string given as a command line argument

usage: ./hash cba

mathews_seq does an exhaustive search to find the string that produced
a specific hash

usage: ./mathews_seq <hash>

The two can be used in conjunction by calling:

./mathews_seq $(./hash cba)

This will create the hash for "cba" and pass that as the argument to 
mathews_seq which will then try to determine the corresponding string
