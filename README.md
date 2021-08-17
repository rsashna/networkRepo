# networkRepo

This repo includes multiple projects made for the Networks course. This repo has both the unchanged original 'echo' and 'time' files (provided for learning),  and 3 network application projects that were coded in C.
-Original files: oges.exe ogec.exe echo_client.c echo_server.c time_client.c time_server.c

## Project 1: Establish TCP connection
tcp_hello.c
tcp_hello_server.c

These files run at the same time in separate isolated environments connected via bridge.

The project implements a simple socket program to connect the two environments with a TCP link. When the link is established, the server sends an outbound 'Hello' message and closes the connection. When the message is received by the client, the message is printed in the client's the terminal and the connection is closed.

## File Download Applications

## Project 2: TCP File Download Application
tcp_fd_clent.c
tcp_fd_server.c

These files run at the same time in separate isolated environments connected via bridge.

This project allows the client to download files from the server using a TCP socket connection.
When the application is run and the TCP connection is successfully established, the Client is shown a menu where they can request a file to be downloaded. If the file exists in the Server, the Server sends packets of the file data. This data is then stored as a new file on the Client's side. When the entire file has been downloaded on the client's side, the client is shown the menu again, if they want to download another file.

## Project 3: UDP File Download Application
udp_fd_clent.c
udp_fd_server.c

These files run at the same time in separate isolated environments connected via bridge.

This project allows the client to download files from the server using a UDP socket connection.
The Client is shown a menu where they can request a file to be downloaded. If the file exists in the Server, the Server sends packets of the file data, otherwise an error code is sent back. This data is then stored as a new file on the Client's side. When the entire file has been sent, the server sends the completed status code and the client is shown the menu again, if they want to download another file.
