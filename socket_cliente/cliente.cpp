#include <iostream>
#include <windows.h>
#include <winsock.h>

void initWinSock(WSADATA & WsaData);
void initSock(SOCKET & Sock);
void initSockAddr(SOCKADDR_IN & DireccionServer);
void connectSock(SOCKET & Sock, SOCKADDR_IN & DireccionServer);

int main()
{
    WSADATA WsaData;
    SOCKET Sock;
    SOCKADDR_IN DireccionServer;

    //se va a pedir un numero y mandarselo al sever
    do
    {
        float snd;
        std::cout << "Escribi un numero: ";
        std::cin >> snd;

        initWinSock(WsaData);
        initSock(Sock);
        initSockAddr(DireccionServer);
        connectSock(Sock, DireccionServer);

        send(Sock,(char *)& snd,sizeof(snd),0);

        float rta;
        recv(Sock,(char *)& rta, sizeof(rta),0);

        std::cout << "El doble es: " << rta << "\n\n";
        closesocket (Sock);
    }
    while(1);

    //cierra el socket

    WSACleanup();

    return 0;
}

void initWinSock(WSADATA &WsaData)
{
    /* Inicializar WinSock */
    int iResult = WSAStartup(MAKEWORD(2, 2), &WsaData);
    if (iResult != NO_ERROR)
    {
        std::cout << "WSAStartup failed with error: "<< iResult << "\n";

    }
}
void initSock(SOCKET &Sock)
{
    //creación de socket (en este caso va a escuchar)
    Sock = socket (AF_INET, SOCK_STREAM, 0);
    if (Sock == INVALID_SOCKET)
    {
        std::cout << "socket failed with error: " << WSAGetLastError() << "\n";
        WSACleanup();
        exit(1);
    }
}
void initSockAddr(SOCKADDR_IN &DireccionServer)
{
    //sockadrr permite especificar una direccion en una red de redes
    //127.0.0.1 es el local hots, 5000 el puerto
    memset (&DireccionServer, 0, sizeof (DireccionServer));
    DireccionServer.sin_family = AF_INET;
    DireccionServer.sin_addr.S_un.S_un_b.s_b1 = 127;
    DireccionServer.sin_addr.S_un.S_un_b.s_b2 = 0;
    DireccionServer.sin_addr.S_un.S_un_b.s_b3 = 0;
    DireccionServer.sin_addr.S_un.S_un_b.s_b4 = 1;
    DireccionServer.sin_port = 5000;
}
void connectSock(SOCKET& Sock, SOCKADDR_IN& DireccionServer)
{
    //connect() iniciará un intercambio de paquetes TCP entre ambos equipos, que establecerá la conexión
    int iResult = connect(Sock, (SOCKADDR *) & DireccionServer, sizeof (DireccionServer));

    if (iResult == SOCKET_ERROR)
    {
        std::cout << "socket failed with error: " << WSAGetLastError() << "\n";
        iResult = closesocket(Sock);
        if (iResult == SOCKET_ERROR)
            std::cout << "socket failed with error: " << WSAGetLastError() << "\n";
        WSACleanup();
        exit(1);
    }
}
