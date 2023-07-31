#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define PORT 8888
#define MAX_CLIENTS 10
#define PACKET_SIZE 16

int client_sockets[MAX_CLIENTS];
int num_clients = 0;

// Thread function to handle communication with a client
void* client_handler(void* arg) {
    int client_socket = *(int*)arg;
    char packet[PACKET_SIZE];
    memset(packet, 'A', PACKET_SIZE);

    while (1) {
        struct timespec t1, t2;
        clock_gettime(CLOCK_MONOTONIC, &t1);  // Record the starting time

        // Send a packet to the client
        if (send(client_socket, packet, PACKET_SIZE, 0) != PACKET_SIZE) {
            perror("send");
            break;
        }

        clock_gettime(CLOCK_MONOTONIC, &t2);  // Record the ending time
        long elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000000000 + t2.tv_nsec - t1.tv_nsec;
        if (elapsed_time < 100) {
            usleep(100 - elapsed_time);  // Sleep to keep the desired packet rate (100 microseconds)
        }
    }

    close(client_socket);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    pthread_t threads[MAX_CLIENTS];

    // Create a server socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Bind to all available network interfaces
    server_addr.sin_port = htons(PORT);       // Set the port number

    // Bind the server socket to the specified port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections with a maximum queue size of MAX_CLIENTS
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for connections...\n");

    while (1) {
        socklen_t client_size = sizeof(client_addr);
        // Accept a new client connection
        if ((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_size)) == -1) {
            perror("accept");
            continue;
        }

        if (num_clients == MAX_CLIENTS) {
            printf("Maximum number of clients reached. Closing connection...\n");
            close(client_socket);
            continue;
        }

        // Print the information of the newly connected client
        printf("Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        client_sockets[num_clients++] = client_socket;

        // Create a new thread to handle communication with the client
        if (pthread_create(&threads[num_clients - 1], NULL, client_handler, (void*)&client_socket) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    close(server_socket);
    return 0;
}
