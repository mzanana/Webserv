# Webserv
Webserv is a non-blocking HTTP/1.1 web server built from scratch in C++98. It uses I/O multiplexing (poll/select) to handle hundreds of concurrent clients on a single thread. Modeled after NGINX, it parses custom config files, routes requests (GET/POST/DELETE), manages static assets, and executes dynamic scripts via CGI.
