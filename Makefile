.PHONY: clean connect serve

all: ihttpd

ihttpd: src/main.c
	cc src/main.c -o ihttpd

serve: ihttpd
	./ihttpd

connect:
	@nc localhost 8666

clean:
	rm -f ihttpd
