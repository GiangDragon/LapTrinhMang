#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    //tao socket
    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //thong tin server
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    //ketnoi toi sv
    int connect_ret = connect(
        client_socket, 
        (struct sockaddr*) &server_addr, 
        sizeof(server_addr)
    );
    if(connect_ret < 0) exit(1);
    else printf("Connected to server : %s:%s\n", argv[1], argv[2]);
    //nhan loi chao tu server
    char sv_msg[200];
    int len = recv(client_socket, sv_msg, sizeof(sv_msg), 0);
    sv_msg[len] = 0;
    printf("Data received : %s\n", sv_msg);

    //nhap xau tu ban phim
    char message[2000];
    fgets(message, 2000, stdin);


    //gui xau toi sever
    send(client_socket, message, strlen(message), 0);

    close(client_socket);
    return 0;
}