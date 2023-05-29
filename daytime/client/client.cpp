#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
int main() {
struct sockaddr_in {
    short sin_family;
    unsigned short sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};
struct in_addr {
    unsigned long s_addr;
};

int s = socket(AF_INET, SOCK_DGRAM, 0);
if(s == -1) {
    cout << "Socket error\n";
    return 1;
}
//Локальный адрес
sockaddr_in * self_addr = new (sockaddr_in);
self_addr->sin_family = AF_INET;
self_addr->sin_port = htons(44214);
self_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
//Адрес сервера
sockaddr_in * srv_addr = new (sockaddr_in);
srv_addr->sin_family = AF_INET;
srv_addr->sin_port = htons(44214);
srv_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
//Фиктивное соединение
int rc = connect(s,(const sockaddr*)srv_addr, sizeof(sockaddr_in));
if (rc == -1) {
    close(s);
    cout << "Error: failed connect to server.\n";
    return 1;
}
//Информационный обмен
else {
    cout << "Successful connection to the server\n";
    char connection_msg[100] = "Hello, it's client!";
    send(s, connection_msg, sizeof(connection_msg), 0);
    char daytime[100];
    recv(s, daytime, sizeof(daytime), 0);
    cout << "Daytime from server: " << daytime << endl;
    cout << "Session close!" << endl;
    close(s);
    return 0;
}
}
