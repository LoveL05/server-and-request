#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
   
int main(int argc, char const *argv[])
{
    int client_fd, valread;
    struct sockaddr_in serv_addr;
    
    int buffer[1024];

    std::string message = "get_link";
    
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 0;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons( PORT );

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) < 0) {
        perror("inet_pton");
        return 0;
    }

    if (connect(client_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        return 0;
    }

    std::cout << "There is 1 working command (get_link): ";
    std::cin >> message;

    send(client_fd, message.c_str(), strlen(message.c_str()), 0);

    std::cout << "Request sent." << std::endl;

    valread = read(client_fd, buffer, 1024);
    printf("Message: %s\n", buffer);

    return 0;

}