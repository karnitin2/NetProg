#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
using namespace std;
int main()
{
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1) {
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    }
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(33333);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    bind(listening, (sockaddr*)&hint, sizeof(hint));
    listen(listening, SOMAXCONN);
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    if (clientSocket != 4) {
       cerr << "Can't connect! Quitting" << endl;
       return -1;
       close(clientSocket);
    }
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service,
NI_MAXSERV, 0) == 0) {
       cout << host << " connected on port " << service << endl;
    } else {
       inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
       cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }
    close(listening);
    char buf[4096];
    awhile (true) {
       memset(buf, 0, 4096);
       int bytesReceived = recv(clientSocket, buf, 4096, 0);
       if (bytesReceived == -1) {
          cerr << "Error in recv(). Quitting" << endl;
          break;
       }
       if (bytesReceived == 0) {
          cout << "Client disconnected " << endl;
          break;
       }
       cout << string(buf, 0, bytesReceived) << endl;
       send(clientSocket, buf, bytesReceived + 1, 0);
       }
    }  
 close(clientSocket);
 return 0;
 }
