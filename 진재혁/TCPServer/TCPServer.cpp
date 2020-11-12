#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERPORT 9000
#define BUFSIZE    512

// ���� �Լ� ���� ��� �� ����
void err_quit(char *msg)
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);
    MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
    LocalFree(lpMsgBuf);
    exit(1);
}

// ���� �Լ� ���� ���
void err_display(char *msg)
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);
    printf("[%s] %s", msg, (char *)lpMsgBuf);
    LocalFree(lpMsgBuf);
}

int main(int argc, char *argv[])
{
    int retval;
    float PlayerX = 0, PlayerY = 0;
    float BombX, BombY;


    // ���� �ʱ�ȭ
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    // socket()
    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == INVALID_SOCKET) err_quit("socket()");

    // bind()
    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVERPORT);
    retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) err_quit("bind()");

    // listen()
    retval = listen(listen_sock, SOMAXCONN);
    if (retval == SOCKET_ERROR) err_quit("listen()");

    // ������ ��ſ� ����� ����
    SOCKET client_sock;
    SOCKADDR_IN clientaddr;
    int addrlen;
    char buf[BUFSIZE + 1];

    

    while (1) {
        // accept()
        addrlen = sizeof(clientaddr);
        client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
        if (client_sock == INVALID_SOCKET) {
            err_display("accept()");
            break;
        }

        char ip_addr[100];
        inet_ntop(AF_INET, &clientaddr.sin_addr, ip_addr, 100);

        // ������ Ŭ���̾�Ʈ ���� ���
        printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
            ip_addr, ntohs(clientaddr.sin_port));

        // Ŭ���̾�Ʈ�� ������ ���
        while (1) {
            // ������ �ޱ�
            retval = recv(client_sock, buf, BUFSIZE, 0);    // char : 1byte
            if (retval == SOCKET_ERROR) {
                err_display("recv()");
                break;
            }
            else if (retval == 0)
                break;


            for (int i = 0; i < retval; ++i)
            {
                switch (buf[i]) {
                case 72:
                    PlayerY = PlayerY + 1.0f;
                    break;

                case 80:
                    PlayerY = PlayerY - 1.0f;
                    break;

                case 75:
                    PlayerX = PlayerX - 1.0f;
                    break;
                case 77:
                    PlayerX = PlayerX + 1.0f;
                    break;
                case ' ':
                    BombX = PlayerX;
                    BombY = PlayerY;
                    
                    printf("Space bar! (%f, %f)\n", BombX, BombY);
                    break;
                }
            }


            // ���� ������ ���
            //buf[retval] = '\0';
            //printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
            //    ntohs(clientaddr.sin_port), buf);


            //// ������ ������
            //retval = send(client_sock, buf, retval, 0);
            //if (retval == SOCKET_ERROR) {
            //    err_display("send()");
            //    break;
            //}

            //retval = send(client_sock, reinterpret_cast<char *>(&ID), 4, 0);   // ���� ID�� ���� ��������� ���� ������ NPC�� �ٸ� �÷��̾���� ������
                                                                                 // ���� ���������� Ŭ���̾�Ʈ���� �� �� �ִ�.

            retval = send(client_sock, reinterpret_cast<char *>(&PlayerX), 4, 0);
            if (retval == SOCKET_ERROR) {
                err_display("X1 send()");
                break;
            }
            if (4 != retval) {
                printf("Data Send Error : x position\n");
            }
            retval = send(client_sock, reinterpret_cast<char *>(&PlayerY), 4, 0);
            if (retval == SOCKET_ERROR) {
                err_display("Y1 send()");
                break;
            }
            if (4 != retval) {
                printf("Data Send Error : y position\n");
            }
        }

        // closesocket()
        closesocket(client_sock);

        printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
            ip_addr, ntohs(clientaddr.sin_port));
    }

    // closesocket()
    closesocket(listen_sock);

    // ���� ����
    WSACleanup();
    return 0;
}
