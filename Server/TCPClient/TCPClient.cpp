#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

using namespace std;

#define SERVERIP   "192.168.43.189"
#define SERVERPORT 9000
#define BUFSIZE    512

// 소켓 함수 오류 출력 후 종료
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

// 소켓 함수 오류 출력
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

// 사용자 정의 데이터 수신 함수
int recvn(SOCKET s, char *buf, int len, int flags)
{
    int received;
    char *ptr = buf;
    int left = len;

    while (left > 0) {
        received = recv(s, ptr, left, flags);
        if (received == SOCKET_ERROR)
            return SOCKET_ERROR;
        else if (received == 0)
            break;
        left -= received;
        ptr += received;
    }

    return (len - left);
}

struct KeyInput //키 입력 on off
{
    bool key_Up;
    bool key_Down;
    bool key_Left;
    bool key_Right;
    bool key_Space;
};

struct Point
{
    short X;
    short Y;
};


int main(int argc, char *argv[])
{
    int retval;

    Point Pos {0, 0};


    // 윈속 초기화
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    // socket()
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) err_quit("socket()");

    // connect()
    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
    serveraddr.sin_port = htons(SERVERPORT);
    retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) err_quit("connect()");

    // 데이터 통신에 사용할 변수
    //char buf[BUFSIZE + 1];
    //int len;

    // 서버와 데이터 통신
    while (1) {
        // 데이터 입력
        KeyInput Input{ 0 };
        
        if (GetAsyncKeyState(VK_UP) & 0x8000)
            Input.key_Up = TRUE;
        if (GetAsyncKeyState(VK_DOWN) & 0x8000)
            Input.key_Down = TRUE;
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
            Input.key_Left = TRUE;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
            Input.key_Right = TRUE;
        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
            Input.key_Space = TRUE;

        // 데이터 보내기
        retval = send(sock, (char*)&Input, sizeof(KeyInput), 0);
        if (retval == SOCKET_ERROR) {
            err_display("send()");
            break;
        }

        system("cls");

        //printf("[TCP 클라이언트] %d바이트를 보냈습니다.\n", retval - 1);

        // 데이터 받기
        retval = recvn(sock, (char*)&Pos, sizeof(Point), 0);
        if (retval == SOCKET_ERROR) {
            err_display("recv()");
            break;
        }
        

        // 좌표 출력
        printf("location (%d, %d)\n", Pos.X, Pos.Y);

        //// 받은 데이터 출력
        //buf[retval] = '\0';
        //printf("[TCP 클라이언트] %d바이트를 받았습니다.\n", retval - 1);
        //printf("[받은 데이터] %s\n", buf);
    }

    // closesocket()
    closesocket(sock);

    // 윈속 종료
    WSACleanup();
    return 0;
}
