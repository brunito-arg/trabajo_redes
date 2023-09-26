#include <iostream>
#include <windows.h>
#include <winsock.h>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#pragma comment(lib, "ws2_32")
#include "client.cpp"

void ingresarUsuario();
void traduccion();
void nuevaTraduccion();

int main()
{

    Client client;

    /*


    //se va a pedir un numero y mandarselo al sever
    do
    {
        int op;


        std::cout << "BIENVENIDO INGRESE UNA OPCION: \n";

         std::cout << "1- Traducir(rol CONSULTA) test\n";
         std::cout << "2- Nueva Traduccion(rol ADMIN)\n";
         std::cout << "3- Usuarios(rol ADMIN) me flata subopciones aca\n";
         std::cout << "4- Ingresar usuario y contrasena (provisorio)\n";
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



        char rta = 'P';

     //   std::cout << "Opcion elegida es: &s" << rta << "\n\n";
    }
    while(1);

    //cierra el socket

    WSACleanup();
*/
    return 0;
}

//TRADUCCION

/*
void traduccion(){


    char palabraIngles[50];
    char palabraEspanol[50];

    //char palabraIngles[250];

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();


    std::cout << "Ingresa una palabra en ingl�s para traducir: ";
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
        palabraEspanol[sizeof(palabraEspanol) - 1] = '\0'; // A�adir terminador nulo

        std::cout << "Traduccion recibida del servidor: " << palabraEspanol << std::endl;
    }

           WSACleanup();
    }


/*

//TRADUCCION
void traduccion(){
    WSADATA WsaData;
    SOCKET Sock;
    SOCKADDR_IN DireccionServer;

    initWinSock(WsaData);
    initSock(Sock);
    initSockAddr(DireccionServer);
    connectSock(Sock, DireccionServer);



    std::string palabraIngles;

    std::cout << "ingrese palabra para buscar la traduccion: ";
    std::cin >> palabraIngles;

    std::cout << palabraIngles << std::endl;

    send(Sock, palabraIngles.c_str(), palabraIngles.length(), 0);

    std::cout << send(Sock, palabraIngles.c_str(), palabraIngles.length(), 0) << std::endl;


    std::string traduccionRecibida;

    char buffer[50];

    int bytesRecibidos = recv(Sock, buffer, sizeof(buffer)-1, 0);

    if (bytesRecibidos <= 0) {
    std::cerr << "Error al recibir datos o conexi�n perdida (cliente)" << std::endl;

        } else {
            // Copiamos los datos recibidos en la variable std::string
            //traduccionRecibida.assign(buffer, bytesRecibidos);
             buffer[bytesRecibidos] = '\0';
            std::string palabraRecibida(buffer);

            // Ahora 'traduccionRecibida' contiene los datos recibidos del servidor
            std::cout << "Datos recibidos del servidor: " << traduccionRecibida << std::endl;
}

    WSACleanup();
}



void nuevaTraduccion(){

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

    std::string usuario;
    std::string contrasena;

    printf ("ingrese el usuario: ");
    std::cin >> usuario;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    printf ("ingrese la contrasena: ");
    std::cin >> contrasena;

    std::string credencial = usuario + "|" + contrasena;

    send(Sock, credencial.c_str(), credencial.length(), 0);

 //   memset(buffer, 0, sizeof(buffer))


   //  send(Sock,(char *)& usuario,sizeof(usuario),0);

   //  send(Sock,(char *)& contrasena,sizeof(contrasena),0);

        WSACleanup();

}
*/





