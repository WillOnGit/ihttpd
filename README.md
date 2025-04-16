# `ihttpd`

An interactive HTTP server, responding to requests from live input.

## Quickstart

* Run `make serve` to build and start the server.
* In a separate terminal/program, connect to local port 8666, with e.g. `make connect`.
* Back in the first session, enter whatever you like followed by `CTRL-D`.
Your input will be sent to whatever program you used to connect.

## Planned features

* basic HTTP/1.1 on requests and responses
* setting or detecting Content-Type
