#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];

    // 1. 建立 socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(1);
    }

    // 2. 設定伺服器位址
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 3. 綁定 IP 和 Port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(1);
    }

    // 4. 開始監聽
    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(1);
    }

    printf("Server is running on http://localhost:%d\n", PORT);

    while (1) {
        socklen_t addrlen = sizeof(address);

        // 5. 接受 client 連線
        client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }

        // 6. 讀取 client 傳來的 HTTP Request
        memset(buffer, 0, BUFFER_SIZE);
        read(client_fd, buffer, BUFFER_SIZE - 1);

        printf("Client Request:\n%s\n", buffer);

        // 7. 回傳 HTTP Response
        char *response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "\r\n"
            "<html>"
            "<head><title>Simple Server</title></head>"
            "<body>"
            "<h1>簡易伺服器成功啟動！</h1>"
            "<p>這是使用 C 語言與系統呼叫建立的 HTTP Server。</p>"
            "</body>"
            "</html>";

        write(client_fd, response, strlen(response));

        // 8. 關閉 client 連線
        close(client_fd);
    }

    close(server_fd);
    return 0;
}