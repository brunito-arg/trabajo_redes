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

            ingresarUsuario();

            int bytesRecibidos = recv(server, buffer, sizeof(buffer), 0);

            if (bytesRecibidos == -1){
                cout << "error al recibir rol" << endl;
            } else {
                string rol(buffer, bytesRecibidos);

            cout << "ROL: " + rol << endl;

            if(rol == "admin"){
                menuAdmin();
            }else{
                menu();
            }
        }






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

void subMenu(){
    do{
        int op;
        string salida;
            cout << "INGRESE UNA OPCION: \n";
            cout << "1) ALTA \n";
            cout << "2) DESBLOQUEO \n";
            cout << "3) SALIR AL MENU ANTERIOR \n";
            cin >> op;
            send(server, (char *)&op, sizeof(op), 0);

            switch(op){
            case 1:
                cout << "Alta: \n";
                ingresarUsuario();
                break;
            case 2:
                cout << "Desbloqueo: \n";
                break;
            case 3:
                cout << "escriba /salir para ir al menu anterior: ";
                cin >> salida;

                if(salida == "/salir"){
                    menu();
                }
            }


    }while(1);
}

void ingresarUsuario(){

            string usuario, contrasena;

            cout << "ingrese su usuario: ";
            cin >> usuario;

            //limpio el buffer
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "ingrese su contrasena: ";
            getline(cin, contrasena);
            cin.ignore(); //ignora el salto de linea mmm bueno soluciono error de que me comia una letra pero debo ingresar dos veces enter

            cout << contrasena << endl;

            string credencial = usuario + "|" + contrasena;

            send (server, credencial.c_str(), credencial.length(), 0); //envio el user al server

            memset(buffer, 0, sizeof(buffer)); //limpio el buffer

}

//CERRAR SESION
void cerrarSesion(){
     string salida;

     cout << "ingrese 'cerrar' para salir: ";
     cin >> salida;

    send (server, salida.c_str(), salida.length(), 0);
    memset(buffer, 0, sizeof(buffer)); //limpio el buffer


    //FALTA PONER UN MENSAJE QUE RECIBA DEL SERVER QUE SE CERRO LA CONEXION



}

void menuAdmin(){
    do{
        int option;

        cout << "MENU DEL ADMINISTRADOR \n";

        cout << "2- Nueva Traduccion(rol ADMIN)\n";
        cout << "3- Usuarios(rol ADMIN) me flata subopciones aca\n";
        cout << "4- Ver registro de actividades(rol ADMIN)\n";
        cout << "5- Cerrar sesion(ambos roles)\n";
        std::cin >> option;

        send(server, (char *)&option, sizeof(option), 0);

        switch(option){

            case 2:
            std::cout << "Nueva traduccion\n";
            nuevaTraduccion();
            break;

            case 3:
            std::cout << "Usuarios del sistema\n";
            subMenu();
            break;

            case 4:
            cout << "Ver registro de actividades\n";
           // ingresarUsuario();
            break;

            case 5:
            cerrarSesion();
            break;

         }


    }while(1);
}

void menu(){
    //MENU
    do{
        int op;


        std::cout << "BIENVENIDO INGRESE UNA OPCION: \n";

        std::cout << "1- Traducir(rol CONSULTA) test\n";
       // std::cout << "2- Nueva Traduccion(rol ADMIN)\n";
       // std::cout << "3- Usuarios(rol ADMIN) me flata subopciones aca\n";
       // std::cout << "4- Ingresar usuario y contrasena (provisorio)\n";
        std::cout << "5- Cerrar sesion(ambos roles)\n";
        //std::cout << "6- Cerrar sesion(ambos roles)\n";
        std::cin >> op;

        send(server, (char *)&op, sizeof(op), 0);


         switch(op){
            case 1:
            std::cout << "traduccion\n";
           traduccion();
            break;

           // case 2:
            //std::cout << "nueva traduccion ejecutandose\n";
            //nuevaTraduccion();
            //break;

            //case 3:
            //std::cout << "usuarios del sistema\n";
            //subMenu();
            //break;

            //case 4:
           // ingresarUsuario();
            //break;

            case 5:
            cerrarSesion();
            break;

         }


            } while(true);
}





    };
