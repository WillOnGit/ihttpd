#define	LISTEN_PORT	8666

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <sys/socket.h>

int main()
{
	int sock, conn, bind_r, listen_r;
	struct sockaddr_in addr;
	char *hello;

	/* create a socket */
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		puts("Could not create socket.");
		return 1;
	}

	/* bind the address */
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	addr.sin_port = htons(LISTEN_PORT);

	bind_r = bind(sock, (struct sockaddr *) &addr, sizeof addr);
	if (bind_r == -1) {
		puts("Could not bind to local port.");
		return 1;
	}

	/* listen for connections */
	listen_r = listen(sock, 1);
	if (listen_r == -1) {
		puts("Could not listen for connections.");
		return 1;
	}

	/* accept a connection */
	conn = accept(sock, NULL, NULL);
	if (conn == -1) {
		puts("Could not accept a connection.");
		return 1;
	}

	/* send some data and shutdown */
	hello = "Greetings!\n";

	write(conn, hello, strlen(hello));

	close(conn);
	close(sock);

	return 0;
}
