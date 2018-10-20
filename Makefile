CFLAGS = -Wall -Wextra

all: mathews_seq hash

debug: CFLAGS += -DDEBUG -g
debug: all

mathews_seq : mathews_seq.c
	gcc $(CFLAGS) -o mathews_seq hashfun.o mathews_seq.c -lm

hash : hash.c
	gcc $(CFLAGS) -o hash hashfun.o hash.c

clean:
	rm mathews_seq hash
