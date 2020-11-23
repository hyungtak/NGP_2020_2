#pragma comment(lib, "ws2_32")
#include "SceneData.h"

#define SERVERPORT 9000
#define BUFSIZE    512

//SceneData �����!
SceneData gameSceneData;
HANDLE Event;

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

DWORD WINAPI LobbyThread(LPVOID arg)
{
    return 0;
}

DWORD WINAPI ProcessThread(LPVOID arg)
{
    SOCKET client_sock = (SOCKET)arg;
    SOCKADDR_IN clientaddr;

    int retval;
    Point Pos{ 0 };
    Point Bomb = Pos;
    KeyInput Input{ 0 };
    int addrlen;

    // Ŭ���̾�Ʈ ���� ���
    addrlen = sizeof(clientaddr);
    getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);

    // Ŭ���̾�Ʈ�� ������ ���
    while (1) {

        retval = WaitForSingleObject(Event, INFINITE);
        

        // ������ �ޱ� (recv())
        retval = recv(client_sock, (char*)&Input, sizeof(KeyInput), 0);    // char : 1byte
        if (retval == SOCKET_ERROR) {
            err_display("recv()");
            break;
        }
        else if (retval == 0)
            break;
        std::cout << Input.key_Down << " " << Input.key_Up << " " << Input.key_Right << " " << Input.key_Left << std::endl;
        gameSceneData.setKeyInput(client_sock, Input);
    
        //retval = send(client_sock, reinterpret_cast<char *>(&ID), 4, 0);   // ���� ID�� ���� ��������� ���� ������ NPC�� �ٸ� �÷��̾���� ������
                                                                             // ���� ���������� Ŭ���̾�Ʈ���� �� �� �ִ�.

        // ������ ������ (send())
        PlayerStatus ps;
        gameSceneData.getPlayer(client_sock, &ps);
        Pos.X = ps.position.X;
        Pos.Y = ps.position.Y;
        MapData md[MAP_SIZE][MAP_SIZE];

        for (int i = 0; i < MAP_SIZE; i++)
            for (int j = 0; j < MAP_SIZE; j++)
               md[i][j] = gameSceneData.getMapData(i, j);
       
        std::cout << md[0][0].isBomb << std::endl;
        retval = send(client_sock, (char*)&md, sizeof(md), 0);
        if (retval == SOCKET_ERROR) 
        {
            err_display("XY send()");
            break;
        }
        if (4 != retval) 
        {
            printf("Data Send Error : x position\n");
        }
        
        SetEvent(Event);
    }

    return 0;

}

DWORD WINAPI GameThread(LPVOID arg)
{
    while (true)
    {
        gameSceneData.update();
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int retval;
    
    //LobbyThread = CreateThread(NULL, 0, LobbyThread, (LPVOID)client_sock, 0, NULL)

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

    HANDLE PThread, GThread, LThread;

    //
    Event = CreateEvent(NULL, FALSE, TRUE, NULL);
    if (Event == NULL) return 1;

    //HANDLE PThread;
    GThread = CreateThread(NULL, 0, GameThread, NULL, 0, NULL);
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
        //�÷��̾� ��������� �������Ϳ� �÷��̾� ������ֱ�
        gameSceneData.setPlayer(client_sock);

        PThread= CreateThread(NULL, 0, ProcessThread, (LPVOID)client_sock, 0, NULL);
        if (PThread == NULL) { closesocket(client_sock); }
        else { CloseHandle(PThread); }

        printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
            ip_addr, ntohs(clientaddr.sin_port));
    }

    // closesocket()
    closesocket(listen_sock);

    // ���� ����
    WSACleanup();
    return 0;
}
