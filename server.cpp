#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080

std::string request(std::string r) {
    if (r == "get_link") {return "https://www.youtube.com/watch?v=Sz89hp_OBVw";}
    return "ERROR";
}

int main() {

    int server_socket, new_socket;
    char valread;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    int opt = 1;

    int buffer[1024] = {0};

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket");
        return 0;
    }

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        return 0;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    if (bind(server_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind");
        return 0;
    }

    if (listen(server_socket, 1) < 0) {
        perror("listen");
        return 0;
    }

    if ((new_socket = accept(server_socket, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
        perror("accept");
        return 0;
    }

    valread = read( new_socket, buffer, 1024);
    
    printf("Request received: %s\n", (char *) buffer);

    std::string data = request((char *) buffer);

    printf("Returned: %s\n", data.c_str());

    send(new_socket, data.c_str(), strlen(data.c_str()), 0);

    return 1;

}
