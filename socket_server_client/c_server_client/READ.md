# C Socket Server-Client Example

This is a simple C socket programming example with a server and a client.

## Server (server.c)

The `server.c` file contains the server-side code. It creates a socket, binds it to a specific port, and listens for incoming connections. Once a client connects, it receives messages from the client and sends them back.

### Compilation and Execution

To compile and run the server, use the following commands:

```bash
gcc server.c -o server
./server
