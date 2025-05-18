#define	MAX_RESPONSE	1024

#include <unistd.h>
#include <string.h>

#include "http.h"

static char RES_BUF[MAX_RESPONSE] = "HTTP/1.1 ";
static const int RES_BUF_START = 9;
static const char *CRLF = "\r\n";

struct http_status {
	char *code;
	char *msg;
};

static const struct http_status OK = {
	"200",
	"OK",
};

/*
 * Serve an HTTP 200 response with no headers.
 *
 * Response written to file descriptor fd, taking the body from body.
 */
void http_res(int fd, char *body, int body_len)
{
	char c;
	int req_body_len, n;

	/* setup RES_BUF to hold response */
	n = RES_BUF_START;

	/* status line */
	strcpy(RES_BUF + n, OK.code);
	n += strlen(OK.code);
	RES_BUF[n++] = ' ';

	strcpy(RES_BUF + n, OK.msg);
	n += strlen(OK.msg);

	strcpy(RES_BUF + n, CRLF);
	strcpy(RES_BUF + n + 2, CRLF);
	n += 4;

	/* body */
	req_body_len = body_len < (MAX_RESPONSE - n) ? body_len : MAX_RESPONSE - n;
	memcpy(RES_BUF + n, body, req_body_len);
	n += req_body_len;

	/* write RES_BUF to fd. TODO: error handling */
	write(fd, RES_BUF, n);
	return;
}
