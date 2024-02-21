#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};

    // 创建套接字
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // 将IP地址从字符串转换为网络地址
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // 连接到服务器
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // 发送消息给服务器
    //const char *message = "Hello from client!";
    const char *message = argv[1];
    send(client_socket, message, strlen(message), 0);
    printf("Message sent to server: %s\n", message);

    // 接收服务器的响应
    ssize_t recv_size = recv(client_socket, buffer, BUFFER_SIZE, 0);
    printf("Received response from server: %s\n", buffer);

    // 关闭套接字
    close(client_socket);

    return 0;
}