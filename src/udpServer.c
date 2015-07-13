#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 10234

int main() 
{
	int sockfd;
	struct sockaddr_in serverAddr, clientAddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&serverAddr, sizeof(struct sockaddr_in));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(PORT);

	if (bind(sockfd, (struct sockaddr *)(&serverAddr), sizeof(serverAddr)) == -1) {
		printf("Bind Fail\n");
		return -1;
	}

	printf("Bind Success!\n");

	char message[1024];

	while (1) {
		socklen_t len;
		len = sizeof(clientAddr);
		recvfrom(sockfd, message, sizeof(message), 0, (struct sockaddr *)(&clientAddr), &len);
		for (int i = 0; i < 100; i++)
			printf("%c", message[i]);
		printf("\n");
	}

	return 0;
}