#include <iostream>
#include <windows.h>
#include <winsock.h>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#pragma comment(lib, "ws2_32")

using namespace std;

class Client {
public:
    /* Inicializar WinSock en la aplicación Cliente */

    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN direccionServer;
    char buffer[1024];

    Client() {
        cout << "Conectando al servidor..." << endl << endl;

        // Inicializa la biblioteca Winsock con la versión 2.0.
        WSAStartup(MAKEWORD(2, 0), &WSAData);

        // Crea un socket para el cliente con IPv4 y protocolo TCP.
        server = socket(AF_INET, SOCK_STREAM, 0);

        // Configura la dirección IP y el puerto del servidor al que se conectará el cliente.
        direccionServer.sin_addr.s_addr = inet_addr("192.168.0.135"); // dirección IP del servidor, corresponde a la de misma ip de la maquina si el servidor y cliente estan en la misma.
        direccionServer.sin_family = AF_INET;

        int puerto;
        cout << "\nIngrese puerto: " << endl;
        cin >> puerto;
        direccionServer.sin_port = htons(puerto); // Puerto 5005 (debe coincidir con el del servidor).

        // Establece la conexión con el servidor. Si es 0 la conexion se realizo con exito, sino informa error
        if(connect(server, (SOCKADDR *)&direccionServer, sizeof(direccionServer)) != 0){
            cout << "Error al conectar al servidor" << endl;
            WSACleanup();
            return;
        }else {
            cout << "Conectado al Servidor!" << endl; //si la conexion fue exitosa pasara a confirmar usuario y contrasena

        }
    }



    };
