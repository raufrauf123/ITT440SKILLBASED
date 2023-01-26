#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    int sockfd, clientfd;
    struct sockaddr_in server, client;
    int rand_num;
    socklen_t clientlen;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // Prepare server sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(1234);

    // Bind socket to IP and port
    if (bind(sockfd, (struct sockaddr*) &server, sizeof(server)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    // Listen for incoming connections
    listen(sockfd, 3);

    // Accept incoming connections
    clientlen = sizeof(client);
    clientfd = accept(sockfd, (struct sockaddr*) &client, &clientlen);
    if (clientfd < 0) {
        perror("Error accepting connection");
        exit(1);
    }

    // Generate random number
    srand(time(NULL));
    rand_num = rand() % 900 + 100;

    // Send random number to client
    send(clientfd, &rand_num, sizeof(rand_num), 0);

    // Close socket
    close(sockfd);
    close(clientfd);

    return 0;
}

