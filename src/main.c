#define	LISTEN_PORT	8666
#define	OUTPUT_LIMIT	1024

#include <stdio.h>
#include <unistd.h>

#include <netinet/in.h>
#include <sys/socket.h>

char outbuf[OUTPUT_LIMIT];

int mksock()
{
	int sock, bind_r, listen_r;
	struct sockaddr_in addr;

	/* create a socket */
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		puts("Could not create socket.");
		return -1;
	}

	/* bind the address */
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	addr.sin_port = htons(LISTEN_PORT);

	bind_r = bind(sock, (struct sockaddr *) &addr, sizeof addr);
	if (bind_r == -1) {
		puts("Could not bind to local port.");
		return -1;
	}

	/* listen for connections */
	listen_r = listen(sock, 1);
	if (listen_r == -1) {
		puts("Could not listen for connections.");
		return -1;
	}

	return sock;
}

int mkoutput()
{
	int c, len;

	len = 0;

	puts("Input required! Send EOF when done...");
	while ((c = getchar()) != EOF && len < OUTPUT_LIMIT) {
		outbuf[len++] = c;
	}

	clearerr(stdin); /* required to read past first EOF */
	return len;
}

void serve(int sock)
{
	while (1) {
		int conn, outlen;

		/* accept a connection */
		conn = accept(sock, NULL, NULL);
		if (conn == -1) {
			puts("Could not accept a connection.");
			return;
		}

		/* set output */
		outlen = mkoutput();

		/* send output data and close socket */
		write(conn, outbuf, outlen);
		printf("Served a request with %d bytes!\n", outlen);
		close(conn);
	}
}

int main()
{
	int sock;

	/* setup */
	puts("Starting server...");
	if ((sock = mksock()) == -1)
		return 1;

	/* keep serving requests */
	puts("Server started!");
	serve(sock);

	return 0;
}
