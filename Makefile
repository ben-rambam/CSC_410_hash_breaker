CFLAGS = -Wall -Wextra

all: mathews_seq brown_seq hashbrowns ventura_seq mathews_parallel ventura_parallel landon_seq landon_parallel

debug: CFLAGS += -DDEBUG -g
debug: all

mathews_seq : mathews_seq.c
	gcc $(CFLAGS) -o mathews_seq hashfun.o mathews_seq.c -lm

mathews_parallel : mathews_parallel.c
	gcc $(CFLAGS) -o mathews_parallel hashfun.o mathews_parallel.c -lm -fopenmp

brown_seq: brown_seq.cpp
	g++ $(CFLAGS) -o brown_seq hashfun.o brown_seq.cpp -lm

ventura_seq : 
	gcc $(CFLAGS) -o ventura_seq ventura_seq.c hashfun.o

ventura_parallel: 
	gcc $(CFLAGS) -o ventura_parallel ventura_pthreads.c hashfun.o -lpthread

landon_seq :
	gcc $(CFLAGS) -o landon_seq landonf_seq.c hashfun.o

landon_parallel :
	gcc $(CFLAGS) -o landon_parallel landonf_3char_par.c hashfun.o -lpthread

hashbrowns: hashbrowns.c
	gcc $(CFLAGS) -o hashbrowns hashfun.o hashbrowns.c

clean:
	rm mathews_seq brown_seq hashbrowns ventura_seq mathews_parallel ventura_parallel landon_seq landon_parallel
