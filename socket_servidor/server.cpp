#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <algorithm> // Necesario para trim
#include <cctype>


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


        credencial();

        cout << "test server" << endl;

        int dato;
        recv(client, (char *)&dato, sizeof(dato), 0);

        //TRADUCCION
        if(dato == 1){
            std::ifstream archivo("traduccion.txt");
            std::string linea;

            string palabraRecibida(buffer);

            int bytesRecibidos = recv (client, buffer, sizeof(buffer) -1 , 0);

            if(bytesRecibidos == -1){
                cout << "error al recibir palabra del cliente" << endl;
            }else{
                string datoRecibido(buffer, bytesRecibidos);

                minusculas(datoRecibido);

                cout << "datos recibidos: " + datoRecibido <<endl;

                while (std::getline(archivo, linea)){
                size_t pos = linea.find(':');

                if(pos != string::npos){
                    string palabraIng = linea.substr(0, pos);
                    string palabraEsp = linea.substr(pos + 1);

                    if(palabraIng==datoRecibido){
                        send(client, palabraEsp.c_str(), palabraEsp.length(), 0);
                    }else{
                        cout << "No fue posible encontrar la traduccion para: " + datoRecibido << endl;
                    }

                }
            }
            }


        }

        //NUEVA TRADUCCION
        if(dato == 2){

            FILE *puntero;
            puntero = fopen ("traduccion.txt", "a");
            string linea;
            string palabraIngles;

            int bytesRecibidos = recv (client, buffer, sizeof(buffer) -1 , 0);

             if(bytesRecibidos == -1){
                cout << "error al recibir la traduccion del cliente" << endl;
            }else{
                string datoRecibido(buffer, bytesRecibidos);

                minusculas(datoRecibido);

                regex formato("^[a-zA-Z]+:[a-zA-Z]+$");

                    if (!regex_match (datoRecibido, formato)){
                        cout << "No fue posible insertar la traduccion. El formato de insercion debe ser palabraEnInglos:traduccionEnEspaniol" << endl;
                    }else{
                            size_t pos = datoRecibido.find(':');

                            if(pos != string::npos){
                                 palabraIngles = datoRecibido.substr(0,pos);
                            }

                            if(palabraIngles == ingles()){
                                cout << "ya existe una traduccion para la palabra: " + datoRecibido << endl;
                            }


                    }

                    cout << "traduccion recibida: " + datoRecibido <<endl;

                        fprintf(puntero, "%s\n",  datoRecibido.c_str());

                        fclose(puntero);


            }

        }


        //INGRESAR USUARIO ALTA (POR AHORA)
        if(dato == 3){
            int subDato;
            recv(client, (char *)&subDato, sizeof(subDato), 0);

            if(subDato == 1){
                FILE *puntero;
                puntero = fopen ("credenciales.txt", "a");
                string linea;

                int bytesRecibidos = recv (client, buffer, sizeof(buffer) -1 , 0);

                 if(bytesRecibidos == -1){
                cout << "error al recibir la traduccion del cliente" << endl;
            }else{
                string datoRecibido(buffer, bytesRecibidos);
                cout << "nuevo usario recibido: " + datoRecibido << endl;

                fprintf(puntero, "%s|CONSULTA|3 \n", datoRecibido.c_str());

                fclose(puntero);
            }
        }


        }

    }
}






//CREDENCIALES TXT
void credencial(){

    std::ifstream archivo("credenciales.txt");
    std::string linea;


        string usuario, contrasena;
        string credRecibida(buffer);
        // memset(buffer, 0,sizeof(buffer));


        int bytesRecibidos = recv (client, buffer, sizeof(buffer) -1 , 0);

        if(bytesRecibidos == -1){
                cout << "error al recibir usuario" << endl;
            }else{
                string datoRecibido(buffer, bytesRecibidos);

                cout << "usuario recibidos: " + datoRecibido <<endl;

                size_t pos = datoRecibido.find('|');

                if(pos != string::npos){
                    usuario = datoRecibido.substr(0,pos);
                    cout << usuario <<endl;
                    contrasena = datoRecibido.substr(pos + 1);
                    cout << contrasena << endl;
            }

                while (std::getline(archivo, linea)){
                    trim(linea);
                    size_t pos = linea.find('|');

                     if(pos != string::npos){

                        string userTxt = linea.substr(0, pos);

                        size_t pos2 = linea.find('|', pos + 1);

                        if (pos2 != string::npos){

                            string contrasenaTxt = linea.substr (pos + 1, pos2 - pos - 1);


                            if (usuario==userTxt && contrasena == contrasenaTxt){
                                cout << "usuario y contrasena correctos" << endl;

                                } else{
                                cout << "usuario o contrasena incorrectos" << endl;
                                cout << userTxt << endl;
                                cout << contrasenaTxt << endl;

                        }
                        }


                     }
                }

        }

}

//TRADUCCION METODO SERVER
void traduccion(){
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
                    }else{
                        cout << "No fue posible encontrar la traduccion para: " + datoRecibido << endl;
                    }

                }
            }
            }

}

string ingles(){

    std::ifstream archivo("traduccion.txt");
    std::string linea;
     string palabraIng;

    while (std::getline(archivo, linea)){
    size_t pos = linea.find(':');

    if(pos != string::npos){
        palabraIng = linea.substr(0, pos);

    }
}


    return palabraIng;

}

//PASA A MINUSCULAS
 void minusculas(string &texto) {
    for (char &c : texto) {
        c = tolower(c);
    }
}

void trim(string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
        return !std::isspace(ch);
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}





};



