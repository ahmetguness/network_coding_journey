#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <arpa/inet.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);
    char buffer[BUFFER_SIZE];

    // Initialize socket for Windows
    #ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        perror("WSAStartup failed");
        exit(EXIT_FAILURE);
    }
    #endif

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Start listening mode
    if (listen(server_socket, 5) == SOCKET_ERROR) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Waiting for connection
    if ((client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_len)) == INVALID_SOCKET) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected: %s\n", inet_ntoa(client_address.sin_addr));

    // Read data from the client
    int bytesRead;
    while ((bytesRead = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytesRead] = '\0';
        printf("Received from client: %s", buffer);
        send(client_socket, buffer, bytesRead, 0);  // Send back to the client
    }

    // Close the sockets
    #ifdef _WIN32
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
    #else
    close(client_socket);
    close(server_socket);
    #endif

    return 0;
}
