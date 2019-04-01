all: compile shared

compile:
	gcc -c -fpic -Wall -Werror src/strlib.c -Iinclude

shared:
	gcc -shared -o libstr.so strlib.o

cp:
	mv -f libstr.so /usr/lib/
	cp include/* /usr/include/

clear:
	rm *.o

install: cp clear
