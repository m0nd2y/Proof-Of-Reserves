#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8888
#define PACKET_SIZE 16

int main(int argc, char* argv[]) {
    int client_socket;
    struct sockaddr_in server_addr;
    char packet[PACKET_SIZE];

    // Create a client socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);  // Server IP address
    server_addr.sin_port = htons(PORT);                 // Server port number

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    while (1) {
        struct timespec t1, t2;
        clock_gettime(CLOCK_MONOTONIC, &t1);  // Record the starting time

        // Receive a packet from the server
        if (recv(client_socket, packet, PACKET_SIZE, 0) != PACKET_SIZE) {
            perror("recv");
            break;
        }

        clock_gettime(CLOCK_MONOTONIC, &t2);  // Record the ending time
        long elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000000000 + t2.tv_nsec - t1.tv_nsec;
        if (elapsed_time < 100) {
            usleep(100 - elapsed_time);  // Sleep to keep the desired packet rate (100 microseconds)
        }
    }

    // Close the client socket
    close(client_socket);
    return 0;
}
