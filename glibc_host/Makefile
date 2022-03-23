# helper Makefile to compile and run the small test suite

BIN=a.out

test: ${BIN}
	./${BIN}

${BIN}: main.c ../timezones.h
	gcc -lc -I../ $<

clean:
	rm ${BIN}