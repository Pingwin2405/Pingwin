all:main.c funkcje.c
	gcc main.c funkcje.c -o test

clean:
	rm test
