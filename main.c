// Machine port enumeration affecting https://www.programiz.com
// No real way to escalate this as you can't get the applications IP to do any exploitation of extra diggingg because they prevent it (I've tried many different methods). So this is safe to just upload as it is..
// Found this on accident and with no malicious intent.
// Twitter bountyoverload
// Discord bountyoverload

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

int main() {
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    char error_message[] = "Error on binding: Address already in use\n";

    printf("lulz: Enumerating active ports on the machine:\n");

    for (portno = 1; portno <= 65535; portno++) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("Error opening socket");
            exit(1);
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);

        if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            if (strcmp(strerror(errno), "Address already in use") == 0) {
                printf("Port %d is active.\n", portno);
            }
        }

        close(sockfd);
    }

    printf("lulz: Port enumeration completed.\n");
    return 0;
}
