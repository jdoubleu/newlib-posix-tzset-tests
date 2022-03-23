# helper Makefile to compile and run the small test suite

test: glibc.out
	./glibc.out

glibc.out: main.c ../timezones.h
	gcc -lc -I../ -o $@ $^

clean:
	rm -f glibc.out