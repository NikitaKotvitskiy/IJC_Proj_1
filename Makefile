CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2
PROGS = primes primes-i steg-decode

all: $(PROGS)

primes: primes.c eratosthenes.o
	gcc primes.c eratosthenes.o $(CFLAGS) -o primes

primes-i: primes.c eratosthenes-i.o bitset_funcs.o
	gcc primes.c eratosthenes-i.o bitset_funcs.o $(CFLAGS) -DUSE_INLINE -o primes-i

steg-decode: steg-decode.c error.o ppm.o eratosthenes.o
	gcc steg-decode.c error.o ppm.o eratosthenes.o $(CFLAGS) -o steg-decode

eratosthenes.o: eratosthenes.c
	gcc -c eratosthenes.c $(CFLAGS) -o eratosthenes.o

eratosthenes-i.o: eratosthenes.c
	gcc -c eratosthenes.c $(CFLAGS) -DUSE_INLINE -o eratosthenes-i.o

bitset_funcs.o: bitset_funcs.c
	gcc -c bitset_funcs.c $(CFLAGS) -DUSE_INLINE -o bitset_funcs.o

error.o: error.c
	gcc -c error.c $(CFLAGS) -o error.o

ppm.o: ppm.c
	gcc -c ppm.c $(CFLAGS) -o ppm.o

clean:
	rm -rf *.o

run:
	make && ./primes && ./primes-i