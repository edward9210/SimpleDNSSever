#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include "dns.h"

#define PORT 53

int main()
{
	int sockfd;
	struct sockaddr_in serverAddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&serverAddr, sizeof(struct sockaddr_in));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(PORT);

	char buf[1024]= {0};
    char tmp[100];

    printf("Input name : \n");
    while (1) {
        scanf("%s", tmp);
        createDNSQuery(tmp, buf);
        int len = sizeof(DnsHead) + sizeof(DnsQuery) + strlen(tmp) + 2;
        for (int i = 0; i < len; i++)
            printf("%x ", buf[i]);
        printf("\n");
        sendto(sockfd, buf, len, 0, (struct sockaddr *)&serverAddr,sizeof(serverAddr));
    }  
	return 0;
}