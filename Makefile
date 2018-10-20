CFLAGS = -Wall -Wextra

all: mathews_seq brown_seq hashbrowns ventura_seq

debug: CFLAGS += -DDEBUG -g
debug: all

mathews_seq : mathews_seq.c
	gcc $(CFLAGS) -o mathews_seq hashfun.o mathews_seq.c -lm

brown_seq: brown_seq.cpp
	g++ $(CFLAGS) -o brown_seq hashfun.o brown_seq.cpp -lm

ventura_seq : 
	gcc $(CFLAGS) -o ventura_seq ventura_seq.c hashfun.o
	
hashbrowns: hashbrowns.c
	gcc $(CFLAGS) -o hashbrowns hashfun.o hashbrowns.c

clean:
	rm mathews_seq brown_seq hashbrowns ventura_seq
