#include <iostream>
#include <windows.h>
#include <winsock.h>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <cctype>
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
            /*
            cout << "Conectado al Servidor!" << endl; //si la conexion fue exitosa pasara a confirmar usuario y contrasena

            string usuario, contrasena;

            cout << "ingrese su usuario: ";
            cin >> usuario;

            //limpio el buffer
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "ingrese su contrasena: ";
            cin >> contrasena;

            string credencial = usuario + "|" + contrasena;

            send (server, credencial.c_str(), credencial.length(), 0); //envio el user al server

            memset(buffer, 0, sizeof(buffer)); //limpio el buffer
            */

            //MENU
            do{
                    int op;


                    std::cout << "BIENVENIDO INGRESE UNA OPCION: \n";

                    std::cout << "1- Traducir(rol CONSULTA) test\n";
                    std::cout << "2- Nueva Traduccion(rol ADMIN)\n";
                    std::cout << "3- Usuarios(rol ADMIN) me flata subopciones aca\n";
                    std::cout << "4- Ingresar usuario y contrasena (provisorio)\n";
                    std::cout << "5- Cerrar sesion(ambos roles)\n";
                    std::cin >> op;

                    send(server, (char *)&op, sizeof(op), 0);


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
           // ingresarUsuario();
            break;

            case 5:
            std::cout << "se cerro la sesion\n";
            break;

         }


            } while(1);

        }
    }

    void traduccion(){

        string palabraIngles;

        cout << "ingrese palabra para traducir: ";
        cin >> palabraIngles;

        //minusculas(palabraIngles);

        cout << "test para ver si guardo la palabra: " + palabraIngles << endl;

        send(server, palabraIngles.c_str(), palabraIngles.length(), 0);

        memset(buffer, 0, sizeof(buffer)); // limpio el buffer despues de enviar la palabra

        int bytesRecibidos = recv(server, buffer, sizeof(buffer), 0);

        if (bytesRecibidos == -1){
            cout << "error al recibir traduccion" << endl;
        } else {
          string palabraTraducida(buffer, bytesRecibidos);

            cout << "traduccion: " + palabraTraducida << endl;
        }
    }

    void nuevaTraduccion(){
        string traduccionNueva;

        cout << "ingrese nueva traduccion: ";
        cin >> traduccionNueva;

        send(server, traduccionNueva.c_str(), traduccionNueva.length(), 0);

        memset(buffer, 0, sizeof(buffer)); // limpio el buffer despues de enviar la traduccion
    }



    };
