#pragma comment(lib, "ws2_32")
#include "SceneData.h"

#define SERVERPORT 9000
#define BUFSIZE    512

//SceneData 만들기!
SceneData gameSceneData;
HANDLE Event;

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

        //std::cout << Input.key_Down << " " << Input.key_Up << " " << Input.key_Left << " " << Input.key_Right << std::endl;
        
        //값 제대로 들어갔나 보기용 테스트해봐야해..

        
        //std::cout << Input.key_Down << " " << Input.key_Up << " " << Input.key_Left << " " << Input.key_Right << std::endl;

        gameSceneData.setKeyInput(client_sock, Input);
    


        //retval = send(client_sock, reinterpret_cast<char *>(&ID), 4, 0);   // 추후 ID를 같이 보내줘야지 여러 마리의 NPC와 다른 플레이어들이 있을때
                                                                             // 누가 움직였는지 클라이언트에서 알 수 있다.

        // 데이터 보내기 (send())
        PlayerStatus ps;
        gameSceneData.getPlayer(client_sock, &ps);
        Pos.X = ps.position.X;
        Pos.Y = ps.position.Y;
        std::cout << Pos.X << " " << Pos.Y << std::endl;
        retval = send(client_sock, (char*)&Pos, sizeof(Point), 0);
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
    retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) err_quit("bind()");

    // listen()
    retval = listen(listen_sock, SOMAXCONN);
    if (retval == SOCKET_ERROR) err_quit("listen()");

    // 데이터 통신에 사용할 변수
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

        // 접속한 클라이언트 정보 출력
        printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
                ip_addr, ntohs(clientaddr.sin_port));
        //플레이어 연결됐으니 씬데이터에 플레이어 만들어주기
        gameSceneData.setPlayer(client_sock);

        PThread= CreateThread(NULL, 0, ProcessThread, (LPVOID)client_sock, 0, NULL);
        if (PThread == NULL) { closesocket(client_sock); }
        else { CloseHandle(PThread); }


        printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
            ip_addr, ntohs(clientaddr.sin_port));
    }

    // closesocket()
    closesocket(listen_sock);

    // 윈속 종료
    WSACleanup();
    return 0;
}
