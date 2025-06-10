# `ihttpd`

An interactive HTTP server, responding to requests from live input.

## Quickstart

* Run `make serve` to build and start the server.
* In a separate window, make any HTTP request to local port 8666, with e.g. `make connect`.
* Back in the first session, enter whatever you like followed by `CTRL-D`.
Your input will be returned as an HTTP/1.1 response.

## Planned features

* setting or detecting Content-Type
