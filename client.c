#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    int sockfd;
    struct sockaddr_in server;
    int rand_num;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // Prepare server sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(1234);

    // Connect to server
    if (connect(sockfd, (struct sockaddr*) &server, sizeof(server)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }

    // Receive random number from server
    recv(sockfd, &rand_num, sizeof(rand_num), 0);

    // Print random number
    // Print random number
printf("Random number: %d\n", rand_num);
// Close socket
close(sockfd);

return 0;
}
