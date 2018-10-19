CFLAGS = -Wall -Wextra

ventura_seq : 
	gcc $(CFLAGS) -o ventura_seq protomain.c hashfun.o

clean : 
	rm ventura_seq
