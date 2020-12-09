#pragma comment(lib, "ws2_32")
#include "SceneData.h"

//SceneData 만들기!
SceneData gameSceneData;
HANDLE Event;
HANDLE PThread, GThread, LThread;

DWORD WINAPI ProcessThread(LPVOID arg);


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

DWORD WINAPI LobbyThread(LPVOID arg)
{
    printf("Running LobbyThread\n");
    int retval;

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == INVALID_SOCKET) err_quit("socket()");

    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVERPORT);
    retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) err_quit("bind()");

    retval = listen(listen_sock, SOMAXCONN);
    if (retval == SOCKET_ERROR) err_quit("listen()");

    KeyInput Input{ 0 };

    SOCKET client_sock;
    SOCKADDR_IN clientaddr;
    int addrlen;


    while (1) {
        // accept()
        addrlen = sizeof(clientaddr);
        client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
        if (client_sock == INVALID_SOCKET) {
            err_display("accept()");
            break;
        }

        gameSceneData.MatchingQueue.push_back(client_sock);

        char ip_addr[100];
        inet_ntop(AF_INET, &clientaddr.sin_addr, ip_addr, 100);

        // 접속한 클라이언트 정보 출력
        printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
            ip_addr, ntohs(clientaddr.sin_port));


        int playerNum = gameSceneData.MatchingQueue.size();
        printf("MatchingQueue size : %d \n", gameSceneData.MatchingQueue.size());

        if (gameSceneData.MatchingQueue.size() == MAX_PLAYER)
        {
            for (int i = 0; i < MAX_PLAYER; ++i)
            {
                gameSceneData.SetPlayer(gameSceneData.MatchingQueue[i]);
           
                retval = send(gameSceneData.MatchingQueue[i], (char*)&playerNum, sizeof(playerNum), 0);

                PThread = CreateThread(NULL, 0, ProcessThread, (LPVOID)gameSceneData.MatchingQueue[i], 0, NULL);
                if (PThread == NULL) { closesocket(client_sock); }
            }

            printf("Exit Lobby Thread()\n");

            ExitThread(0);
        }
        else
        {
            for (int i = 0; i < gameSceneData.MatchingQueue.size(); ++i)
            {
                retval = send(gameSceneData.MatchingQueue[i], (char*)&playerNum, sizeof(playerNum), 0);
            }
        }
    }
}

DWORD WINAPI ProcessThread(LPVOID arg)
{
    printf("Running ProcessThread\n");
    gameSceneData.StartGame();

    SOCKET client_sock = (SOCKET)arg;
    SOCKADDR_IN clientaddr;

    int retval;
    Point Pos{ 0 };
    Point Bomb = Pos;
    KeyInput Input{ 0 };
    int addrlen;

    // 클라이언트 정보 얻기
    addrlen = sizeof(clientaddr);
    getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);

    // 클라이언트와 데이터 통신
    while (1) {

        retval = WaitForSingleObject(Event, INFINITE);

        // 데이터 받기 (recv())
        retval = recv(client_sock, (char*)&Input, sizeof(KeyInput), 0);  
        if (retval == SOCKET_ERROR) {
            err_display("recv()");
            break;
        }
        else if (retval == 0)
            break;

        gameSceneData.SetKeyInput(client_sock, Input);

        // 데이터 보내기 (send())

        MapData gameMapData[MAP_SIZE][MAP_SIZE];
        FinishGame finishFlag = gameSceneData.GetGameFinish();

        for (int i = 0; i < MAP_SIZE; i++)
            for (int j = 0; j < MAP_SIZE; j++)
               gameMapData[i][j] = gameSceneData.GetMapData(i, j);

        retval = send(client_sock, (char*)&gameMapData, sizeof(gameMapData), 0);
        if (retval == SOCKET_ERROR)
        {
            err_display("Map send()");
            break;
        }

        retval = send(client_sock, (char*)&finishFlag, sizeof(FinishGame), 0);
        if (retval == SOCKET_ERROR) 
        {
            err_display("Finish send()");
            break;
        }
        SetEvent(Event);
    }


    // 윈속 종료
    WSACleanup();

    return 0;
}

DWORD WINAPI GameThread(LPVOID arg)
{
    while (true)
    {
        gameSceneData.Update();
    }
    return 0;
}

int main(int argc, char *argv[])
{
    Event = CreateEvent(NULL, FALSE, TRUE, NULL);
    if (Event == NULL) return 1;


    GThread = CreateThread(NULL, 0, GameThread, NULL, 0, NULL);
    if (GThread == NULL)
        printf("Create GThread Error\n");

    LThread = CreateThread(NULL, 0, LobbyThread, NULL, 0, NULL);
    if(LThread == NULL)
        printf("Create LThread Error\n");

    while (1)
    {
        printf("Running main \n");
        printf("startgame: %d\n", gameSceneData.MatchingQueue.size());
        Sleep(10000);
    }
}
