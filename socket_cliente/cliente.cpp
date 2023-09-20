#include <iostream>
#include <windows.h>
#include <winsock.h>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

void initWinSock(WSADATA & WsaData);
void initSock(SOCKET & Sock);
void initSockAddr(SOCKADDR_IN & DireccionServer);
void connectSock(SOCKET & Sock, SOCKADDR_IN & DireccionServer);
void ingresarUsuario();
void traduccion();
void nuevaTraduccion();

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
         std::cout << "4- Ingresar usuario y contraseña (provisorio)\n";
         std::cout << "5- Cerrar sesion(ambos roles)\n";
         std::cin >> op;

         switch(op){
            case 1:
            std::cout << "traduccion\n";
            traduccion();
            break;

            case 2:
            std::cout << "nueva traduccion ejecutandose\n";
            nuevaTraduccion();
            break;

            case 3:
            std::cout << "usuarios del sistema\n";
            break;

            case 4:
            ingresarUsuario();
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

//TRADUCCION
void traduccion(){
    WSADATA WsaData;
    SOCKET Sock;
    SOCKADDR_IN DireccionServer;

    initWinSock(WsaData);
        initSock(Sock);
        initSockAddr(DireccionServer);
        connectSock(Sock, DireccionServer);


    char palabraIngles[50];
    char palabraEspanol[50];

    //char palabraIngles[250];

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();


    std::cout << "Ingresa una palabra en inglés para traducir: ";
    memset(palabraIngles, 0, sizeof(palabraIngles)); // Limpia el buffer
    std::cin >> palabraIngles; // Ingresa la palabra por teclado

    std::cout << "test para ver si guarda la palabra que ingreso: " << palabraIngles <<std::endl;


    int bytesEnviados = send(Sock, palabraIngles, strlen(palabraIngles), 0);
        if (bytesEnviados == -1) {
            std::cerr << "Error al enviar datos al servidor." << std::endl;
        } else {
            std::cout << "Se enviaron " << bytesEnviados << " bytes al servidor." << std::endl;
}


     char buffer[256];
     int bytesRecibidos = recv(Sock, buffer, sizeof(buffer), 0);

        if (bytesRecibidos <= 0) {
        std::cerr << "Error al recibir la traduccion o conexion perdida." << std::endl;
    } else {
        buffer[bytesRecibidos] = '\0';

        strncpy(palabraEspanol, buffer, sizeof(palabraEspanol));
        palabraEspanol[sizeof(palabraEspanol) - 1] = '\0'; // Añadir terminador nulo

        std::cout << "Traduccion recibida del servidor: " << palabraEspanol << std::endl;
    }

           WSACleanup();
    }


void nuevaTraduccion(){
    WSADATA WsaData;
    SOCKET Sock;
    SOCKADDR_IN DireccionServer;

    initWinSock(WsaData);
    initSock(Sock);
    initSockAddr(DireccionServer);
    connectSock(Sock, DireccionServer);

    char palabraTraduccion[50];

    std::cout << "Ingresa una nueva traduccion: ";
    memset(palabraTraduccion, 0, sizeof(palabraTraduccion)); // Limpia el buffer
    std::cin >> palabraTraduccion; // Ingresa la palabra por teclado

    std::cout << "verificacion de ingreso de traduccion: " << palabraTraduccion << std::endl;

    send(Sock, (char *) &palabraTraduccion, strlen(palabraTraduccion), 0);


    WSACleanup();

}



     //send(Sock,(char *)& contrasena,sizeof(contrasena),0);









void ingresarUsuario(){
    WSADATA WsaData;
    SOCKET Sock;
    SOCKADDR_IN DireccionServer;

    std::string usuario;
    std::string contrasena;

    printf ("ingrese el usuario: ");
    std::cin >> usuario;

    printf ("ingrese la contrasena: ");
    std::cin >> contrasena;

    initWinSock(WsaData);
        initSock(Sock);
        initSockAddr(DireccionServer);
        connectSock(Sock, DireccionServer);


     send(Sock,(char *)& usuario,sizeof(usuario),0);

     send(Sock,(char *)& contrasena,sizeof(contrasena),0);

      WSACleanup();

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
