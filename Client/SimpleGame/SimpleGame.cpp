#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <conio.h>

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "GSEGame.h"
#include "GSEGlobal.h"

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    512

GSEGame* g_game = NULL;
KeyInput g_inputs;

void SendToServer();
void RecvFromServer();

WSADATA wsa;
SOCKET sock;
SOCKADDR_IN serveraddr;
int retval;

int g_prevTimeInMillisecond = 0;

void RenderScene(int temp)
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int elapsedTime = currentTime - g_prevTimeInMillisecond;
    g_prevTimeInMillisecond = currentTime;
    float elapsedTimeInSec = (float)elapsedTime / 1000.0f;

    SendToServer();
    RecvFromServer();

    g_game->RendererScene();

    glutSwapBuffers();		//double buffering

    glutTimerFunc(16, RenderScene, 16);
}

void KeyDownInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        g_inputs.key_Space = true;
        break;
    }
}

void KeyUpInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        g_inputs.key_Space = false;
        break;
    }
}

void SpecialKeyDownInput(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        g_inputs.key_UP = true;
        break;
    case GLUT_KEY_DOWN:
        g_inputs.key_Down = true;
        break;
    case GLUT_KEY_LEFT:
        g_inputs.key_Left = true;
        break;
    case GLUT_KEY_RIGHT:
        g_inputs.key_Right = true;
        break;
    }

}

void SpecialKeyUpInput(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        g_inputs.key_UP = false;
        break;
    case GLUT_KEY_DOWN:
        g_inputs.key_Down = false;
        break;
    case GLUT_KEY_LEFT:
        g_inputs.key_Left = false;
        break;
    case GLUT_KEY_RIGHT:
        g_inputs.key_Right = false;
        break;
    }
}

void Idle(void)
{
}

void MouseInput(int button, int state, int x, int y)
{
}

// ���� �Լ� ���� ��� �� ����
void err_quit(char* msg)
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
void err_display(char* msg)
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);
    printf("[%s] %s", msg, (char*)lpMsgBuf);
    LocalFree(lpMsgBuf);
}

// ����� ���� ������ ���� �Լ�
int recvn(SOCKET s, char* buf, int len, int flags)
{
    int received;
    char* ptr = buf;
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

void SendToServer()
{
    // ������ ������ ���
    // ������ ������
    retval = send(sock, (const char*)(&g_inputs), sizeof(KeyInput), 0);
    if (retval == SOCKET_ERROR) {
        err_display("send()");
    }
    system("cls");
}

void RecvFromServer()
{
    MapData mapData[MAP_SIZE][MAP_SIZE];

   do{
        retval = recvn(sock, reinterpret_cast<char*>(&mapData), sizeof(MapData), 0);
        if (retval == SOCKET_ERROR) {
            err_display("MapData recv()");
            break;
        }
   } while (retval != 0);

   g_game->SetMapData(mapData);
}

int connectSocket()
{
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) err_quit("socket()");

    // connect()
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVERIP, &(serveraddr.sin_addr.s_addr));
    serveraddr.sin_port = htons(SERVERPORT);
    retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) err_quit("connect()");
}

int main(int argc, char* argv[])
{
    // Initialize GL things
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(GSE_WINDOW_WIDTH, GSE_WINDOW_HEIGHT);
    glutCreateWindow("Network Game Programing KPU");
    connectSocket();

    glewInit();
    if (glewIsSupported("GL_VERSION_3_0"))
    {
        std::cout << " GLEW Version is 3.0\n ";
    }
    else
    {
        std::cout << "GLEW 3.0 not supported\n ";
    }

    g_game = new GSEGame();
    memset(&g_inputs, 0, sizeof(KeyInput));

    glutDisplayFunc(Idle);
    glutIdleFunc(Idle);
    glutMouseFunc(MouseInput);
    glutKeyboardFunc(KeyDownInput);
    glutKeyboardUpFunc(KeyUpInput);
    glutSpecialFunc(SpecialKeyDownInput);
    glutSpecialUpFunc(SpecialKeyUpInput);

    g_prevTimeInMillisecond = glutGet(GLUT_ELAPSED_TIME);

    glutTimerFunc(16, RenderScene, 16);

    glutMainLoop();

    delete g_game;

    // closesocket()
    closesocket(sock);

    // ���� ����
    WSACleanup();

    return 0;
}
