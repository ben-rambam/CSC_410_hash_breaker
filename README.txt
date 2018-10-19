#CSC-410_hash_breaker


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



