#define	MAX_RESPONSE	1024

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "http.h"

static char RES_BUF[MAX_RESPONSE] = "HTTP/1.1 ";
static const int RES_BUF_START = 9;
static const char *CRLF = "\r\n";
static const char *SERVER_TOKEN = "ihttpd/0.1dev";

struct http_status {
	char *code;
	char *msg;
};

static const struct http_status OK = {
	"200",
	"OK",
};

/*
 * Serve an HTTP 200 response with basic headers.
 *
 * Response written to file descriptor fd, taking the body from body.
 */
void http_res(int fd, char *body, int body_len)
{
	int req_body_len, n;
	time_t req_instant;
	struct tm *req_time;

	/* setup RES_BUF to hold response */
	n = RES_BUF_START;

	/* status line */
	strcpy(RES_BUF + n, OK.code);
	n += strlen(OK.code);

	RES_BUF[n++] = ' ';
	strcpy(RES_BUF + n, OK.msg);
	n += strlen(OK.msg);

	strcpy(RES_BUF + n, CRLF);
	n += 2;

	/* headers */
	req_instant = time(NULL);
	req_time = gmtime(&req_instant);
	n += strftime(RES_BUF + n, 100, "Date: %a, %d %b %Y %H:%M:%S GMT\r\n", req_time);

	n += snprintf(RES_BUF + n, MAX_RESPONSE - n, "Server: %s\r\n", SERVER_TOKEN);
	n += snprintf(RES_BUF + n, MAX_RESPONSE - n, "Content-Type: text/plain\r\n");
	n += snprintf(RES_BUF + n, MAX_RESPONSE - n, "Content-Length: %d\r\n", body_len);
	n += snprintf(RES_BUF + n, MAX_RESPONSE - n, "Cache-Control: no-cache\r\n");
	n += snprintf(RES_BUF + n, MAX_RESPONSE - n, "Connection: close\r\n");

	if (n + 2 >= MAX_RESPONSE) {
		puts("RES_BUF full; aborting");
		return;
	}
	strcpy(RES_BUF + n, CRLF);
	n += 2;

	/* body */
	req_body_len = body_len < (MAX_RESPONSE - n) ? body_len : MAX_RESPONSE - n;
	memcpy(RES_BUF + n, body, req_body_len);
	n += req_body_len;

	/* write RES_BUF to fd. TODO: error handling */
	write(fd, RES_BUF, n);
	return;
}
