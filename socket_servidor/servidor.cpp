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
    SOCKET SockTest;
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
    char Rta [256];
    send (SockConexion, (char *)&Rta, sizeof (Rta), 0);




    char palabraEspanol[256];
     recv(SockConexion, (char *)&palabraEspanol, sizeof(palabraEspanol), 0);

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
/*
    if (Dato == 1) {
        std::ifstream archivo("traduccion.txt");

        std::string palabra; // Supongo que palabra es un std::string

        recv(SockConexion, (char *)&palabra, sizeof(palabra), 0);

        std::cout << palabra << std::endl;

        std::string linea;

        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string palabraIngles, palabraEspanol;

            std::getline(ss, palabraIngles, ':'); // Leemos palabraIngles desde la línea

            if (palabra == palabraIngles) { // Comparamos palabra con palabraIngles usando ==
                std::cout << "La traducción de: " << palabraIngles << std::endl;
                std::cout << "Es la palabra: " << palabraEspanol << std::endl;

                recv(SockConexion, (char *)&Dato, sizeof(Dato), 0);

                send(SockConexion, (char *)&palabraEspanol, sizeof(palabraEspanol), 0);
            } else {
                std::cerr << "Esa palabra no se encuentra para traducir." <<std::endl;
            }
        }
    }

*/

    if (Dato == 1){

        std::ifstream archivo ("traduccion.txt");

        std::string linea;

        bool traduccionEncontrada;

        archivo.clear();
        archivo.seekg(0);

         //char palabraIngles[256];
         std::string palabraIngles;
         std::string palabraEspanol;

         recv(SockConexion, (char *)&palabraIngles, sizeof(palabraIngles), 0);

        while(std::getline(archivo, linea)){
            std::size_t pos = linea.find(':');
            if(pos != std::string::npos){
                std::string palabraEsp = linea.substr(0, pos);
                std::string palabraIng = linea.substr(pos + 1);

                if(palabraIng == palabraIngles){
                    palabraEspanol = palabraEsp;
                    traduccionEncontrada = true;

                    break;
                }
            }
        }

         if (!traduccionEncontrada) {
//            strcpy(palabraEspanol, "No se encontró traducción.");
        }

        //enviar traduccion al cliente

       send(SockConexion, palabraEspanol.c_str(), palabraEspanol.size(), 0);

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




