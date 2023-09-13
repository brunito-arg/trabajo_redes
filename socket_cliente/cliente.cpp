#include <iostream>
#include <windows.h>
#include <winsock.h>
#include <fstream>
#include <sstream>
#include <string>

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
        int op;


        std::cout << "BIENVENIDO INGRESE UNA OPCION: \n";

         std::cout << "1- Traducir(rol CONSULTA)\n";
         std::cout << "2- Nueva Traduccion(rol ADMIN)\n";
         std::cout << "3- Usuarios(rol ADMIN) me flata subopciones aca\n";
         std::cout << "4- Ver registro de actividades (rol ADMIN)\n";
         std::cout << "5- Cerrar sesion(ambos roles)\n";
         std::cin >> op;

         switch(op){
            case 1:
            std::cout << "traduccion\n";
            break;

            case 2:
            std::cout << "nueva traduccion ejecutandose\n";
            break;

            case 3:
            std::cout << "usuarios del sistema\n";
            break;

            case 4:
            std::cout << "registro de actividades\n";
            break;

            case 5:
            std::cout << "se cerro la sesion\n";
            break;

         }


        initWinSock(WsaData);
        initSock(Sock);
        initSockAddr(DireccionServer);
        connectSock(Sock, DireccionServer);


        send(Sock,(char *)& op,sizeof(op),0);

        char rta = 'P';
        recv(Sock,(char *)& rta, sizeof(rta),0);

     //   std::cout << "Opcion elegida es: &s" << rta << "\n\n";
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
