#include <fstream>

#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <libgen.h>

#define PORT 8000
#define MAX 1024

int main(int argc, char *argv[1])
{
    const char *path = argv[1];
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    send(sock, path, strlen(path),0);
    char *file_name = basename((char *)path);
    char buf[MAX];
    bzero(buf, MAX);
    int n = recv(sock, buf, MAX, 0);
    std::ofstream ostrm(file_name, std::ios::binary);
    ostrm.write(buf, n);

    ostrm.close();
    close(sock);

    return 0;
}
