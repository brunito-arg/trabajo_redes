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

    //creación de socket (en este caso va a escuchar)
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

    //El servidor, deberá iniciar una lectura en el socket, esperando recibir información
    int Dato;
    recv (SockConexion, (char *)&Dato, sizeof (Dato), 0);

    //y luego deberá enviar la respuesta:
    char Rta = 'K';
    send (SockConexion, (char *)&Rta, sizeof (Rta), 0);

    char palabra[30];
    recv(SockConexion, (char *)&palabra, sizeof (palabra), 0);

    //imprime
    printf ("Dato recibido: %d, Respuesta enviada: %c\n", Dato, Rta);  //no me da lo que quiero !
    closesocket(SockConexion);


    //VALIDAR USUARIO Y CONTRASEÑA

    if(Dato == 4){

        std::ifstream archivo("credenciales.txt");

        std::string linea;

        while(std::getline(archivo, linea)){
            std::istringstream ss(linea);
            std::string usuario, contrasena, rol;
            int intentos;

             if (std::getline(ss, usuario, '|') && std::getline(ss, contrasena, '|') && std::getline(ss, rol, '|') && (ss >> intentos)){

            std::cout << "Usuario: " << usuario << std::endl;
            std::cout << "Contraseña: " << contrasena << std::endl;


            recv(SockConexion, (char *)&Dato, sizeof (Dato), 0);

            send (SockConexion, (char *)&usuario, sizeof(usuario), 0);


            } else {

                std::cerr << "Formato de línea incorrecto en el archivo de credenciales: " << linea << std::endl;
            }
        }



    }

    //TRADUCCION

    if(Dato == 1){

        std::ifstream archivo("traduccion.txt");

        std::string linea;

        recv(SockConexion, (char *)&palabra, sizeof (palabra), 0);

        while(std::getline(archivo, linea)){
            std::istringstream ss(linea);
            std::string palabraIngles, palabraEspanol;

             if (std::getline(ss, palabraIngles, ':') == palabra){ //solucionar esto no puedo hacer el ==

            std::cout << "La traduccion de: " << palabraIngles << std::endl;
            std::cout << "Es la palabra: " << palabraEspanol << std::endl;


            recv(SockConexion, (char *)&Dato, sizeof (Dato), 0);

            send (SockConexion, (char *)&palabraEspanol, sizeof(palabraEspanol), 0);


            } else {

                std::cerr << "Formato de línea incorrecto en el archivo de credenciales: " << linea << std::endl;
            }
        }



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




