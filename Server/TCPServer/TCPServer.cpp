#pragma comment(lib, "ws2_32")
#include "SceneData.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

//SceneData 만들기!
SceneData gameSceneData;
HANDLE Event;
HANDLE PThread, GThread, LThread;
int g_prevTimeInMillisecond = 0;

// 연결된 소켓 저장
std::vector<SOCKET> MatchingQueue;

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

    // 윈속 초기화
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
    retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) err_quit("bind()");

    // listen()
    retval = listen(listen_sock, SOMAXCONN);
    if (retval == SOCKET_ERROR) err_quit("listen()");


    KeyInput Input{ 0 };

    // 데이터 통신에 사용할 변수
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

        MatchingQueue.push_back(client_sock);

        char ip_addr[100];
        inet_ntop(AF_INET, &clientaddr.sin_addr, ip_addr, 100);

        // 접속한 클라이언트 정보 출력
        printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
            ip_addr, ntohs(clientaddr.sin_port));
        //플레이어 연결됐으니 씬데이터에 플레이어 만들어주기
        gameSceneData.setPlayer(client_sock);

        printf("MatchingQueue size : %d \n", MatchingQueue.size());


        if (MatchingQueue.size() == MAX_PLAYER)
        {
            /////////////// 수정해야 함
            //while (1)
            //{
            //    retval = recv(client_sock, (char*)&Input, sizeof(KeyInput), 0);    // char : 1byte
            //    if (retval == SOCKET_ERROR) {
            //        err_display("recv()");
            //        break;
            //    }
            //    else if (retval == 0)
            //        break;
            //}

            //if (gameSceneData.readyPlayer == MAX_PLAYER)
            ///////////////
            {
                for (int i = 0; i < 3; ++i)
                {
                    PThread = CreateThread(NULL, 0, ProcessThread, (LPVOID)MatchingQueue[i], 0, NULL);
                    if (PThread == NULL) { closesocket(client_sock); }
                    else { CloseHandle(PThread); }
                }

                printf("Exit Lobby Thread()\n");

                ExitThread(0);

            }
        }
    }
}

DWORD WINAPI ProcessThread(LPVOID arg)
{
    printf("Running ProcessThread\n");


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
        retval = recv(client_sock, (char*)&Input, sizeof(KeyInput), 0);    // char : 1byte
        if (retval == SOCKET_ERROR) {
            err_display("recv()");
            break;
        }
        else if (retval == 0)
            break;


        //std::cout << Input.key_Down << " " << Input.key_Up << " " << Input.key_Right << " " << Input.key_Left << std::endl;
        gameSceneData.setKeyInput(client_sock, Input);
    

        // 데이터 보내기 (send())
        PlayerStatus ps;
        gameSceneData.getPlayer(client_sock, &ps);
        Pos.X = ps.position.X;
        Pos.Y = ps.position.Y;
         MapData md[MAP_SIZE][MAP_SIZE];
        
        for (int i = 0; i < MAP_SIZE; i++)
            for (int j = 0; j < MAP_SIZE; j++)
               md[i][j] = gameSceneData.getMapData(i, j);
        //std::cout << md[0][0].isBomb << std::endl;
        retval = send(client_sock, (char*)&md, sizeof(md), 0);        if (retval == SOCKET_ERROR) 
        {
            err_display("XY send()");
            break;
        }
        SetEvent(Event);
    }

    printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
        clientaddr.sin_addr, ntohs(clientaddr.sin_port));


    // 윈속 종료
    WSACleanup();


    return 0;

}
void update(int temp)
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int elapsedTime = currentTime - g_prevTimeInMillisecond;
    g_prevTimeInMillisecond = currentTime;
    float elapsedTimeInSec = (float)elapsedTime; // / 1000.0f;

    std::cout << elapsedTimeInSec << std::endl;
    gameSceneData.update();
    glutTimerFunc(60,update, 60);
}

DWORD WINAPI GameThread(LPVOID arg)
{
    while (true) {
        int currentTime = glutGet(GLUT_ELAPSED_TIME);
        int elapsedTime = currentTime - g_prevTimeInMillisecond;
        float elapsedTimeInSec = (float)elapsedTime; // / 1000.0f;
        if (elapsedTimeInSec > 60) {
            g_prevTimeInMillisecond = currentTime;
            std::cout << elapsedTimeInSec << std::endl;
            gameSceneData.update();
        }
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
        Sleep(10000);
    }
}
