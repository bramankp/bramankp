#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sock != -1);

    const int reuseaddr = 1;
    assert(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr)) != -1);

    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_port = htons(6667);
    assert(inet_pton(AF_INET, "127.255.255.255", &address.sin_addr) != -1);
    assert(bind(sock, (struct sockaddr *)&address, sizeof(address)) != -1);

    int value;
    ssize_t len = recv(sock, &value, sizeof(value), 0);
    assert(len == sizeof(value));

    printf("value:%d\n", value);

    (void)close(sock);

    return 0;
}
