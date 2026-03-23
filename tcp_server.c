#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    //Mo file
    FILE *f_greeting, *f_save;
    f_greeting = fopen(argv[1], "r");
    f_save = fopen(argv[2], "w");
    

    //tao socket
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    //thong tin server
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(9000);

    //bind socket toi mang
    int bind_ret = bind(
        server_socket, 
        (struct sockaddr*)&server_addr, 
        sizeof(server_addr));

    //chuyen socket qua tt doi ket noi
    int listen_ret = listen(server_socket, 5);

    //chap nhan ket noi
    int client = accept(server_socket, NULL, NULL);

    //gui cau chao
    char s[100];
    while (fgets(s, 100, f_greeting) != NULL) {
        send(client, s, strlen(s), 0);
    }

    //Nhan du lieu
    char cl_msg[2000];
    int rcv_ret = recv(client, &cl_msg, sizeof(cl_msg), 0);
    fputs(cl_msg, f_save);

    fclose(f_greeting);
    fclose(f_save);
    close(client);
    close(server_socket);

    return 0;
}