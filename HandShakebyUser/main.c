#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct {
    char* host;         // Host address of the node (here, using "127.0.0.1")
    int port;           // Port number of the node
    int parent_port;    // Port number of the parent node
    int child_ports[2]; // Array of port numbers of child nodes (maximum of 2 children)
    int child_count;    // Number of child nodes
} Node;

// Function to send a message to the given node
void send_message(Node* node, char* buffer) {
    int try_count = 0;
    while (try_count < 3) {  // Retry up to 3 times
        int neighbor_port;
        if (node->child_count == 0) {
            neighbor_port = node->parent_port;  // If there are no child nodes, send to the parent node
        } else if (node->child_count == 1) {
            neighbor_port = node->child_ports[0];  // If there is one child node, send to that child node
        } else {
            int neighbor_idx = rand() % node->child_count;
            neighbor_port = node->child_ports[neighbor_idx];  // Randomly select one of the child nodes to send the message
        }

        struct sockaddr_in neighbor_addr;
        int sock = socket(AF_INET, SOCK_STREAM, 0);  // Create a TCP socket
        neighbor_addr.sin_family = AF_INET;
        neighbor_addr.sin_addr.s_addr = inet_addr(node->host);  // Set the host address
        neighbor_addr.sin_port = htons(neighbor_port);         // Set the port number

        if (connect(sock, (struct sockaddr*)&neighbor_addr, sizeof(neighbor_addr)) == 0) {
            // If the connection to the selected node is successful, send the message and close the socket
            int send_result = send(sock, buffer, strlen(buffer), 0);
            if (send_result != -1) {
                close(sock);
                return;
            }
        }
        try_count++;
        close(sock);
    }

    // If the connection fails even after 3 attempts, try sending the message to the parent node
    if (node->parent_port != node->port) {
        printf("Failed to send message to neighbors after 3 attempts. Trying parent node...\n");

        struct sockaddr_in parent_addr;
        int parent_sock = socket(AF_INET, SOCK_STREAM, 0);
        parent_addr.sin_family = AF_INET;
        parent_addr.sin_addr.s_addr = inet_addr(node->host);   // Set the host address of the parent node
        parent_addr.sin_port = htons(node->parent_port);       // Set the port number of the parent node

        try_count = 0;
        while (try_count < 3) {
            if (connect(parent_sock, (struct sockaddr*)&parent_addr, sizeof(parent_addr)) == 0) {
                // If the connection to the parent node is successful, send the message and close the socket
                int send_result = send(parent_sock, buffer, strlen(buffer), 0);
                if (send_result != -1) {
                    close(parent_sock);
                    return;
                }
            }
            try_count++;
            close(parent_sock);
        }

        printf("Failed to send message to parent node after 3 attempts.\n");
    } else {
        printf("Failed to send message to neighbors after 3 attempts.\n");
    }
}

// Thread function to run each node
void *run_node(void *arg) {
    Node *node = (Node *)arg;
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(node->host);  // Set the host address of the node
    address.sin_port = htons(node->port);            // Set the port number of the node

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);  // Receive message from the socket
        printf("Received: %s\n", buffer);

        send_message(node, buffer);  // Send the received message to neighboring nodes

        close(new_socket);
    }

    return NULL;
}

int main() {
    Node nodes[10000];

    nodes[0] = (Node){"127.0.0.1", 8001, {8002, 8003}, 2, -1};
    nodes[1] = (Node){"127.0.0.1", 8002, {8004, 8005}, 2, 8001};
    nodes[2] = (Node){"127.0.0.1", 8003, {8006, 8007}, 2, 8001};
    
    /*
        Set More nodes
    */

    // Set up the rest of the nodes and establish parent-child relationships between nodes
    for (int i = 3; i < 10000; i++) {
        int parent_idx = (i - 1) / 2;
        int port = 8000 + i;
        nodes[i] = (Node){"127.0.0.1", port, {8001}, 0, nodes[parent_idx].port};
        nodes[parent_idx].child_ports[nodes[parent_idx].child_count++] = port;
    }

    int node_count = sizeof(nodes) / sizeof(Node);
    pthread_t threads[node_count];

    // Create threads to run each node
    for (int i = 0; i < node_count; i++) {
        if (pthread_create(&threads[i], NULL, run_node, (void *)&nodes[i]) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < node_count; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
