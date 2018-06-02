all:main.c funkcje.c
	gcc main.c funkcje.c -o test
main.o:main.c
	gcc main.c -c -o main.o

funkcje.o:funkcje.c 
	gcc funkcje.c -c -o funkcje.o

clean:
	rm test
