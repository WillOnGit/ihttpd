.PHONY: clean

all: ihttpd

ihttpd: src/main.c
	cc src/main.c -o ihttpd

clean:
	rm -f ihttpd
