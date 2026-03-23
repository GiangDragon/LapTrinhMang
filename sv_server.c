#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include<time.h>

int main(int argc, char* argv[]) {
    //Mo file
    FILE *f;
    f = fopen("sv_log.txt", "a");

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


    //Nhan du lieu
    char cl_msg[2000];
    int rcv_ret = recv(client, &cl_msg, sizeof(cl_msg), 0);
    
    //xu ly
    char* mssv = strtok(cl_msg, "/");
    char* hoten = strtok(NULL, "/");
    char* nsinh = strtok(NULL, "/");
    char* cpa = strtok(NULL, "/");
    
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    getpeername(client, (struct sockaddr*)&client_addr, &addr_len);

    char *ipv4 = inet_ntoa(client_addr.sin_addr);

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char tggui[200];
    sprintf(tggui, "%d-%d-%d %d:%d:%d",
        t->tm_year + 1900,
        t->tm_mon + 1,
        t->tm_mday,
        t->tm_hour,
        t->tm_min,
        t->tm_sec
    );
    char finalstr[500];
    sprintf(finalstr, "%s %s %s %s %s %s",
        ipv4,
        tggui,
        mssv,
        hoten,
        nsinh,
        cpa
    );

    fprintf(f, "%s\n", finalstr);
    printf("%s\n", finalstr);


    fclose(f);
    close(client);
    close(server_socket);

    return 0;
}