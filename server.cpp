#include <fstream>
#include <string>

#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8000
#define MAX 1024

int main()
{
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(listenfd, (struct sockaddr *)&addr, sizeof(addr));
    listen(listenfd, 20);

    struct sockaddr_in client;
    socklen_t  client_size = sizeof(client);
    int sock = accept(listenfd, (struct sockaddr *)&client, &client_size);

    char buf[MAX];
    bzero(buf, MAX);
    recv(sock, buf, MAX, 0);
    std::ifstream istrm(buf, std::ios::binary);
    bzero(buf, MAX);
    istrm.read(buf, MAX);
    int n = istrm.gcount();
    send(sock, buf, n, 0);

    istrm.close();
    close(sock);
    close(listenfd);

    return 0;
}
