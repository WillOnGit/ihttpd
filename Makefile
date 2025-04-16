.PHONY: clean serve

all: ihttpd

ihttpd: src/main.c
	cc src/main.c -o ihttpd

serve: ihttpd
	./ihttpd

clean:
	rm -f ihttpd
