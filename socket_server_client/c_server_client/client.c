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
    SOCKET client_socket;
    struct sockaddr_in server_address;
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
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server's IP address
    server_address.sin_port = htons(PORT);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server\n");

    // Receive input from the user and send it to the server
    printf("Enter a message for the server: ");
    fgets(buffer, sizeof(buffer), stdin);
    send(client_socket, buffer, strlen(buffer), 0);

    // Receive the response from the server
    int bytesRead = recv(client_socket, buffer, sizeof(buffer), 0);
    buffer[bytesRead] = '\0';
    printf("Received from the server: %s", buffer);

    // Close the socket
    #ifdef _WIN32
    closesocket(client_socket);
    WSACleanup();
    #else
    close(client_socket);
    #endif

    return 0;
}
