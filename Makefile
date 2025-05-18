.PHONY: clean connect serve

all: ihttpd

ihttpd: src/main.c src/http.c src/http.h
	cc src/main.c src/http.c -o ihttpd

serve: ihttpd
	./ihttpd

connect:
	curl --ipv4 http://localhost:8666/

clean:
	rm -f ihttpd
