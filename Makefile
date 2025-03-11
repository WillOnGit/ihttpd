.PHONY: clean

all: main

main: src/main.c
	cc src/main.c -o main

clean:
	rm -f main
