#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <sstream>
#include <string>

int main()
{
    /* Inicializar WinSock */
    WSADATA WsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &WsaData);
    if (iResult != NO_ERROR) {
        std::cout << "WSAStartup failed with error: "<< iResult << "\n";
        return 1;
    }

    //creaci�n de socket (en este caso va a escuchar)
    SOCKET SockEscucha;
    SockEscucha = socket (AF_INET, SOCK_STREAM, 0);
    if (SockEscucha == INVALID_SOCKET) {
        std::cout << "socket failed with error: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    //sockadrr permite especificar una direccion en una red de redes
    SOCKADDR_IN DireccionLocal;
    memset (&DireccionLocal, 0, sizeof (DireccionLocal));
    DireccionLocal.sin_family = AF_INET;
    DireccionLocal.sin_port = 5000;

    //bind asocia una direccion local al socket
     if (bind(SockEscucha,
             (SOCKADDR *) &DireccionLocal, sizeof (DireccionLocal)) == SOCKET_ERROR) {
        std::cout << "bind failed with error: " << WSAGetLastError() << "\n";
        closesocket(SockEscucha);
        WSACleanup();
        return 1;
    }

    //listen inicia la esoera de coneixones, especifica la cantidad maxima de conexiones encoladas
    if (listen(SockEscucha, 1) == SOCKET_ERROR) {
        std::cout << "listen failed with error: " <<  WSAGetLastError() << "\n";
        closesocket(SockEscucha);
        WSACleanup();
        return 1;
    }

    SOCKET SockConexion;
    do{
    //accept espera la llegada de conexiones y duplica el socket en el nuevo
    SockConexion = accept (SockEscucha, NULL, NULL);
    if (SockConexion == INVALID_SOCKET) {
        std::cout << "listen failed with error: " <<  WSAGetLastError() << "\n";
        closesocket(SockEscucha);
        WSACleanup();
        return 1;
    }

    //El servidor, deber� iniciar una lectura en el socket, esperando recibir informaci�n
    int Dato;
    recv (SockConexion, (char *)&Dato, sizeof (Dato), 0);

    //y luego deber� enviar la respuesta:
    char Rta = 'K';
    send (SockConexion, (char *)&Rta, sizeof (Rta), 0);

    //imprime
    printf ("Dato recibido: %d, Respuesta enviada: %c\n", Dato, Rta);  //no me da lo que quiero !
    closesocket(SockConexion);


    //VALIDAR USUARIO Y CONTRASE�A

    if(Dato == 4){
        FILE *puntero;
        puntero = fopen ("credenciales.txt", "r");//lee el archivo;

     char linea[30];
     char *p;
     int i = 0;
     char aux[30];

     fgets(linea, 30, puntero);
     while(!feof(puntero)){
        i++;
        if(p==strstr(linea,"bruno|pepitos123|ADMIN|3")){
            sscanf(p, "%s", aux);
        }
            if(!strcmp(aux,"bruno|pepitos123|ADMIN|3"))
                break;
            fgets(linea, 30, puntero);
     }

    recv(SockConexion, (char *)&Dato, sizeof (Dato), 0);

    send (SockConexion, (char *)&aux, sizeof(aux), 0);

     printf("\nline: %d\n", i);

      fclose(puntero);

}





    //ARCHIVO DE USUARIOS
    if(Dato==3){
         FILE *puntero;
    puntero = fopen ("credenciales.txt", "r"); //lee el archivo

    char aux[40] = " ";
    fgets(aux,40,puntero);


    recv(SockConexion, (char *)&Dato, sizeof (Dato), 0);

    send (SockConexion, (char *)&aux, sizeof(aux), 0);

    //imprime
    printf("USUARIO: %s", aux);

    fclose(puntero);
    }

        }while(1);

     // No longer need server socket
    closesocket(SockEscucha);


    WSACleanup();
    return 0;
}
