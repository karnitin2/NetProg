#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
using namespace std;
int main()
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
    {
       perror("Socket Creation Has Failed: ");
       exit(-1);
    }
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(32214);
    if (bind(fd, (const struct sockaddr *) &addr, sizeof(addr)) == -1)
    {
       perror("Listening Failed on the Socket: ");
       exit(-1);
    }
    struct sockaddr_in cliaddr;
    socklen_t cliaddr_len = sizeof(cliaddr);
    char buffer[100];
    cout << "Server:\n";
    while(1) {
       string dt = "daytime";
       char dtBuff[sizeof(dt)];
       strcpy(dtBuff, dt.c_str());
       recvfrom(fd, buffer, 100,0,(struct sockaddr *) &cliaddr, &cliaddr_len);
       cout << "Client: " << buffer << endl;
       sendto(fd, dtBuff, sizeof(dtBuff),0,(const struct sockaddr *) &cliaddr,
cliaddr_len);
    }
    return 0;
}
