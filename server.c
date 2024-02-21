#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_socket, new_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);
    char buffer[BUFFER_SIZE] = {0};

    // 创建套接字
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 将套接字绑定到指定地址和端口
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听客户端连接
    if (listen(server_socket, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // 接受客户端连接
    if ((new_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // 从客户端接收数据
    ssize_t recv_size = recv(new_socket, buffer, BUFFER_SIZE, 0);
    printf("Received message from client: %s\n", buffer);

    // 发送响应给客户端
    const char *response = "Hello from server!";
    send(new_socket, response, strlen(response), 0);

    // 关闭套接字
    close(new_socket);
    close(server_socket);

    return 0;
}