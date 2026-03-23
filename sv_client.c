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
    
    //Nhap thong tin
    char mssv[10], hoten[20], nsinh[20]; float cpa;
    printf("Nhap MSSV : ");
    fgets(mssv, 10, stdin);
    printf("\nNhap ho va ten : ");
    fgets(hoten, 20, stdin);
    printf("\nNhap ngay sinh : ");
    fgets(nsinh, 20, stdin);
    printf("\nNhap cpa: ");
    scanf("%f", &cpa);

    //dong goi
    char buf[200];
    mssv[strcspn(mssv, "\n")] = '\0';
    hoten[strcspn(hoten, "\n")] = '\0';
    nsinh[strcspn(nsinh, "\n")] = '\0';
    sprintf(buf, "%s/%s/%s/%.2f", mssv, hoten, nsinh, cpa);
    
    //gui toi sv
    send(client_socket, buf, strlen(buf), 0);

    close(client_socket);
    return 0;
}