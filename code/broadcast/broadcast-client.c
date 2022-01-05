#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sock != -1);

    const int broadcast = 1;
    assert(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) != -1);

    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(6667);
    assert(inet_pton(AF_INET, "127.255.255.255", &address.sin_addr) != -1);

    int value = 42;
    assert(sendto(sock, &value, sizeof(value), 0, (struct sockaddr *)&address, sizeof(address)) == (ssize_t)sizeof(value));

    (void)close(sock);

    return 0;
}
