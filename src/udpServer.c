#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "hashTable.h"

#define PORT 53

int main(int argc, char *argv[]) 
{
	// set working directory
	char path[128];
	int lenPath = 0;
	char *tmp = argv[0], *pos;
	while (1) {
		pos = strchr(tmp, '/');
		if (pos == NULL)
			break;
		lenPath += pos - tmp + 1;
		tmp = pos + 1;
	}
	strcpy(path, argv[0]);
	path[lenPath] = '\0';
	int d = open(path, O_RDONLY);
    fchdir(d);

    // read config.txt
	char str[64];
	FILE *fp;

	if ((fp = fopen("../config/config.txt", "r")) == NULL) {
		printf("Read config error\n");
		return -1;
	}

	// read and bulid hashtable
	initHashTable();
	while (!feof(fp)) {
		fgets(str, 64, fp);
		char name[64], ip[64];
		char *ptr;
		int lenIP = strchr(str, ' ') - str;
		int lenName;
		if (strchr(str, '\n') != NULL)
			lenName = strchr(str, '\n') - strchr(str, ' ') - 1;
		else
			lenName = strlen(str) - lenIP - 1;
		ptr = str;
		for (int i = 0; i < lenIP; i++, ptr++)
			ip[i] = *ptr;
		ip[lenIP] = '\0';
		ptr += 1;
		for (int i = 0; i < lenName; i++, ptr++)
			name[i] = *ptr;
		name[lenName] = '\0';
		// printf ("%s --> %s\n", name, ip);
		add(name, ip);
	}

	fclose(fp);

	dispalyTable();

	// bulid socket
	int sockfd;
	struct sockaddr_in serverAddr, clientAddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&serverAddr, sizeof(struct sockaddr_in));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(PORT);

	if (bind(sockfd, (struct sockaddr *)(&serverAddr), sizeof(serverAddr)) == -1) {
		printf("Bind Fail\n");
		printf("%s\n", strerror(errno));
		return -1;
	}

	printf("***************************************\n");
	printf("Bind Success!\n");
	printf("***************************************\n");
	printf("listening port %d\n", PORT);

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