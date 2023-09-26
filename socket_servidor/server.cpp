#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Server {



public:
    /* Inicializar WinSock en la aplicación Servidor */

    WSADATA WSAData;           // Estructura para almacenar información sobre la biblioteca Winsock.
    SOCKET server, client;     // Descriptores de socket para el servidor y el cliente.
    SOCKADDR_IN direccionLocal, clientAddr; // Estructuras para almacenar información de direcciones IP y puertos.
    char buffer[1024];         // Búfer para almacenar mensajes.

    Server() {
        // Inicializa la biblioteca Winsock con la versión 2.0.
        WSAStartup(MAKEWORD(2, 0), &WSAData);

        // Crea un socket para el servidor con IPv4 y protocolo TCP.
        server = socket(AF_INET, SOCK_STREAM, 0);

        // Configura la dirección y el puerto del servidor.
        direccionLocal.sin_addr.s_addr = INADDR_ANY;
        direccionLocal.sin_family = AF_INET;
        int puerto = 5005;
        direccionLocal.sin_port = htons(puerto);  // Puerto 5005.

        /*La función bind() utilizada asocia una dirección local con el socket.
        En este caso estamos especificando que el socket deberá recibir llamadas entrantes en cuyo port destino se especifice 5005.*/
        bind(server, (SOCKADDR *)&direccionLocal, sizeof(direccionLocal));

        // listen(x,x) habilita al servidor para escuchar conexiones entrantes.
        //El último parámetro especifica la cantidad de conexiones que pueden ser encoladas en espera de ser atendidas
        //Si se recibe más llamadas, las mismas serán rechazadas automáticamente.
        listen(server, 1); // 0 no permite conexiones en espera, 1 vamos a decir que permite 1 cliente en espera


        cout << "==================================" << endl;
        cout << "========Inicia Servidor===========" << endl;
        cout << "==================================" << endl;
        cout << "Socket creado. Puerto de escucha: " << endl;

        //Inicia el servidor y se queda siempre a la escucha
        while(true){
            int clientAddrSize = sizeof(clientAddr);

            // La función accept() espera la llegada de conexiones.
            // La llamada a esta función no retornará hasta que se reciba una llamada entrante.
            /* El código verifica si el valor devuelto por accept es diferente de INVALID_SOCKET.
            Si es diferente, significa que la conexión se ha aceptado correctamente,
            y se muestra un mensaje en la consola que indica que el cliente se ha conectado. */
            if ((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET) {

                cout << "---------Cliente conectado---------" << endl;
        }

        cout << "test server" << endl;

        int dato;
        recv(client, (char *)&dato, sizeof(dato), 0);

        //traduccion
        if(dato == 1){
            std::ifstream archivo("traduccion.txt");
            std::string linea;

            string palabraRecibida(buffer);

            int bytesRecibidos = recv (client, buffer, sizeof(buffer) -1 , 0);

            if(bytesRecibidos == -1){
                cout << "error al recibir palabra del cliente" << endl;
            }else{
                string datoRecibido(buffer, bytesRecibidos);

                cout << "datos recibidos: " + datoRecibido <<endl;

                while (std::getline(archivo, linea)){
                size_t pos = linea.find(':');

                if(pos != string::npos){
                    string palabraIng = linea.substr(0, pos);
                    string palabraEsp = linea.substr(pos + 1);

                    if(palabraIng==datoRecibido){
                        send(client, palabraEsp.c_str(), palabraEsp.length(), 0);
                    }

                }
            }
            }


        }
    }
}

};
