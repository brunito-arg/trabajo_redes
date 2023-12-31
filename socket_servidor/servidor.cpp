#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <sstream>
#include <string>
#include "server.cpp"

int main()
{
    Server server;



    /*

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

    //El servidor, deber� iniciar una lectura en el socket, esperando recibir informaci�n
    int Dato;
    recv (SockConexion, (char *)&Dato, sizeof (Dato), 0);

    //y luego deber� enviar la respuesta:
    char Rta [256];
    send (SockConexion, (char *)&Rta, sizeof (Rta), 0);




    char palabraEspanol[256];
     recv(SockConexion, (char *)&palabraEspanol, sizeof(palabraEspanol), 0);

    char palabra[30];
    recv(SockConexion, (char *)&palabra, sizeof (palabra), 0);

    //imprime
    printf ("Dato recibido: %d, Respuesta enviada: %c\n", Dato, Rta);  //no me da lo que quiero !
    closesocket(SockConexion);


    //VALIDAR USUARIO Y CONTRASE�A

    if(Dato == 4){

        std::string usuario;
        std::string contrasena;

        char buffer[50];

        std::string credencialRecibida(buffer);

        memset(buffer, 0, sizeof(buffer));

        int bytesRecibidos = recv(SockConexion, buffer, sizeof(buffer), 0);

        if (bytesRecibidos == -1) {
            // Manejo de error si recv falla
            std::cerr << "Error al recibir datos del cliente(servidor)" << std::endl;
        } else {

            std::cout << credencialRecibida << std::endl;

            size_t pos = credencialRecibida.find('|');
            if (pos != std::string::npos){
            usuario = credencialRecibida.substr(0,pos);
            contrasena = credencialRecibida.substr(pos + 1);
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

            std::getline(ss, palabraIngles, ':'); // Leemos palabraIngles desde la l�nea

            if (palabra == palabraIngles) { // Comparamos palabra con palabraIngles usando ==
                std::cout << "La traducci�n de: " << palabraIngles << std::endl;
                std::cout << "Es la palabra: " << palabraEspanol << std::endl;

                recv(SockConexion, (char *)&Dato, sizeof(Dato), 0);

                send(SockConexion, (char *)&palabraEspanol, sizeof(palabraEspanol), 0);
            } else {
                std::cerr << "Esa palabra no se encuentra para traducir." <<std::endl;
            }
        }
    }




    if (Dato == 1) {
    printf("OwO\n");

    std::ifstream archivo("traduccion.txt");
    std::string linea;

    bool traduccionEncontrada = false;
    char palabraIngles[50];
    char palabraEspanol[50];

    int bytesRecibidos = recv(SockConexion, palabraIngles, sizeof(palabraIngles), 0);
    palabraIngles[bytesRecibidos] = '\0';


    std::cerr << " test palabra ingles: " << palabraIngles << std::endl;

    while (std::getline(archivo, linea)) {
        printf("uwu\n");
        std::size_t pos = linea.find(':');

        if (pos != std::string::npos) {
            char palabraIng[50];
            strncpy(palabraIng, linea.c_str(), pos); // Copiar la parte anterior al ':' en palabraIng
            palabraIng[pos] = '\0'; // A�adir terminador nulo

            char palabraEsp[50];
            strncpy(palabraEsp, linea.c_str() + pos + 1, sizeof(palabraEsp)); // Copiar la parte de la traducci�n a palabraEsp

            printf("U_U\n");
            std::cerr << " test palabra ing: " << palabraIng << std::endl;
            std::cerr << " comparacion palabra ing: " << palabraIngles << std::endl;
            std::cerr << " test palabra esp: " << palabraEsp << std::endl;

            if (strncmp(palabraIng, palabraIngles, sizeof(palabraIngles)) == 0) {
                strncpy(palabraEspanol, palabraEsp, sizeof(palabraEspanol));
                palabraEspanol[sizeof(palabraEspanol) - 1] = '\0'; // A�adir terminador nulo
                traduccionEncontrada = true;

                printf("XD");
                std::cerr << " test palabra esp: " << palabraEspanol << std::endl;

                // send(SockConexion, palabraEspanol, strlen(palabraEspanol), 0);

                break;
            }
        }
    }

    if (!traduccionEncontrada) {
        // strcpy(palabraEspanol, "No se encontr� traducci�n.");
    }

    // Convertir palabraEspanol a std::string
    std::string palabraEspanolStr(palabraEspanol);

    // Enviar traducci�n al cliente
    std::cout << "Palabra en espa�ol a enviar al cliente: " << palabraEspanol << std::endl;
    send(SockConexion, palabraEspanolStr.c_str(), palabraEspanolStr.size(), 0);
}


/*
    if (Dato == 1){

        char buffer[50];

         std::string palabraRecibida;
       // memset(buffer, 0, sizeof(buffer)); //limpia el buffer

       std::cout << palabraRecibida << std::endl;


       std::cout << recv(SockConexion, buffer, sizeof(buffer)-1, 0) << std::endl;

        int bytesRecibidos = recv(SockConexion, buffer, sizeof(buffer)-1, 0);


        if (bytesRecibidos <= 0) {
                std::cerr << "Error al recibir datos o conexi�n perdida (servidor)." << std::endl;
        } else {
                // Copiamos los datos recibidos en la variable std::string
                palabraRecibida.assign(buffer, bytesRecibidos);

                // Ahora 'palabraRecibida' contiene los datos recibidos del cliente
                std::cout << "Datos recibidos del cliente: " << palabraRecibida << std::endl;
}



        std::ifstream archivo("traduccion.txt");
        std::string linea;




        std::cout << palabraRecibida << std::endl;

        while (std::getline(archivo, linea)) {

        std::size_t pos = linea.find(':');

            if (pos != std::string::npos){

               std::string palabraIng(linea.c_str(), pos); //copia la parte de la traduccion de la palabra en ingles

               std::string palabraEsp(linea, pos + 1); // Copiar la parte de la traducci�n a palabraEsp

                if (palabraIng == palabraRecibida){

                    send(SockConexion, palabraEsp.c_str(), palabraEsp.length(), 0);
                }


            }

        }

    }



    //NUEVA TRADUCCION
    if(Dato==2){
        FILE *puntero;
        puntero = fopen ("traducciones.txt", "w");

        char palabraTraduccion[50];

        char aux[50];
        int bytesRecibidos = recv(SockConexion, aux, sizeof(aux), 0);

        if (bytesRecibidos <= 0) {
            std::cout << "ERROR" << std::endl; //me da este error revisar!
            } else {
            aux[bytesRecibidos] = '\0'; // A�adir terminador nulo para convertirlo en una cadena de C v�lida
            // Ahora 'aux' contiene los datos recibidos desde el socket
            }

            std::cout << aux << std::endl;

            //escribe
            fprintf(puntero, aux);

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

    */
    return 0;
};




