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

                if ((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET) {

                cout << "---------Cliente conectado---------" << endl;

                menuConexion();


            }
            }
            }

         void menuConexion(){

        bool validado = credencial();
        bool verificar = true;

        if(validado == true){
            cout << "test server" << endl;

        int dato;
        recv(client, (char *)&dato, sizeof(dato), 0);

        while(verificar){
        //TRADUCCION
        if(dato == 1){
            traduccion();

        }

        if(dato==0){

            verificar = false;

            int bytesRecibidos = recv (client, buffer, sizeof(buffer) -1 , 0);

            if(bytesRecibidos == -1){
                cout << "error al recibir la salida" << endl;
            }else{
                string datoRecibido(buffer, bytesRecibidos);
            if(datoRecibido == "cerrar"){
                closesocket(client);
                cout << "se cerro la conexion" << endl;
               break;
            }
        }


        }

        }

        }else{
            menuConexion();
        }



        //NUEVA TRADUCCION
        /*
        if(dato == 2){

            nuevaTraduccion();

        }


        //INGRESAR USUARIO ALTA (POR AHORA)
        if(dato == 3){


            altaYDesbloqueo();


        }
        */

        //CERRAR SESION


}

 //aqui termina SERVER






//CREDENCIALES TXT
boolean credencial(){

    std::ifstream archivo("credenciales.txt");
    std::string linea;


        string usuario, contrasena;
        string credRecibida(buffer);
        bool credencialesCorrectas = false;
        // memset(buffer, 0,sizeof(buffer));


        int bytesRecibidos = recv (client, buffer, sizeof(buffer) -1 , 0);

        if(bytesRecibidos == -1){
                cout << "error al recibir usuario" << endl;
                credencial();
            }else{
                string datoRecibido(buffer, bytesRecibidos);

                cout << "usuario recibidos: " + datoRecibido <<endl;

                size_t pos = datoRecibido.find('|');

                if(pos != string::npos){
                    usuario = datoRecibido.substr(0,pos);
                    cout << usuario <<endl;
                    contrasena = datoRecibido.substr(pos + 1);
                    cout << contrasena << endl;

                     //bandera que verifica si se encontro el usuario


                while (std::getline(archivo, linea)){
                  //  trim(linea);
                    size_t pos = linea.find('|');

                     if(pos != string::npos){

                        string userTxt = linea.substr(0, pos);

                        size_t pos2 = linea.find('|', pos + 1);

                        if (pos2 != string::npos){

                            string contrasenaTxt = linea.substr (pos + 1, pos2 - pos - 1);


                            if (usuario==userTxt && contrasena == contrasenaTxt){
                                cout << "datos de usuario incorrectos" << endl;
                                credencialesCorrectas = true;
                                break;

                                }
                        }


                     }
                }

                if(!credencialesCorrectas){
                    cout << "usuario o contrasena incorrectas" << endl;
                }

}
                 send(client, usuario.c_str(), usuario.length(), 0);

}

    return credencialesCorrectas;
}

//TRADUCCION METODO SERVER
void traduccion(){
        std::ifstream archivo("traduccion.txt");
        std::string linea;
        bool traduccionEncontrada = false;

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
                    traduccionEncontrada = true;
                    cout << datoRecibido << endl;
                }

            }
        }
               if(!traduccionEncontrada){
                cout << "No fue posible encontrar la traduccion para: " + datoRecibido << endl;
            }

        }

}

//NUEVA TRADUCCION
void nuevaTraduccion(){

        FILE *puntero;
        puntero = fopen ("traduccion.txt", "a");
        string linea;
        string palabraIngles;

        int bytesRecibidos = recv (client, buffer, sizeof(buffer) -1 , 0);

            if(bytesRecibidos == -1){
                cout << "error al recibir la traduccion del cliente pepo" << endl;
            }else{
                string datoRecibido(buffer, bytesRecibidos);

                minusculas(datoRecibido);

                regex formato("^[a-zA-Z]+:[a-zA-Z]+$");

                    if (!regex_match (datoRecibido, formato)){
                        cout << "No fue posible insertar la traduccion. El formato de insercion debe ser palabraEnIngles:traduccionEnEspaniol" << endl;
                    }else{
                            size_t pos = datoRecibido.find(':');

                            if(pos != string::npos){
                                 palabraIngles = datoRecibido.substr(0,pos);
                            }

                            if(palabraIngles == ingles()){
                                cout << "ya existe una traduccion para la palabra: " + datoRecibido << endl;
                            }

                            cout << "Nueva traduccion recibida: " + datoRecibido <<endl;

                            fprintf(puntero, "%s\n",  datoRecibido.c_str());

                            fclose(puntero);


                    }



            }


}

//ALTA Y DESBLOQUEO
void altaYDesbloqueo(){
        int subDato;
        recv(client, (char *)&subDato, sizeof(subDato), 0);

            if(subDato == 1){
                FILE *puntero;
                puntero = fopen ("credenciales.txt", "a");
                string linea;

                int bytesRecibidos = recv (client, buffer, sizeof(buffer) -1 , 0);

                 if(bytesRecibidos == -1){
                cout << "error al recibir datos del cliente" << endl;
            }else{
                string datoRecibido(buffer, bytesRecibidos);

                cout << "nuevo usario recibido: " + datoRecibido << endl;

                // Divide el dato recibido en usuario y contraseña
                    size_t pos = datoRecibido.find('|');
                    if (pos != string::npos) {

                    string usuario = datoRecibido.substr(0, pos);
                    string contrasena = datoRecibido.substr(pos + 1);

                    // Verifica si el usuario es "admin" y no permite su escritura
                        if (usuario != "admin") {

                                if(!contrasena.empty()){
                                    fprintf(puntero, "%s|CONSULTA|3 \n", datoRecibido.c_str());
                                    cout << "Nuevo usuario recibido: " + datoRecibido << endl;
                                }else{
                                    cout << "NO se puede ingrear un usuario con la contrasena vacia" << endl;                                }
                        } else {
                            cout << "No se pudo guardar el usuario 'admin'" << endl;
                        }
                    } else {
                            cout << "Dato recibido no válido: " + datoRecibido << endl;
                        }


                fclose(puntero);
            }
        }else{
            if(subDato==2){
                cout << "XD" << endl;
            }
        }
}


//CERRAR SESION

/*
void cerrarSesion(bool verificar){
    verificar = false;

    int bytesRecibidos = recv (client, buffer, sizeof(buffer) -1 , 0);

    if(bytesRecibidos == -1){
            cout << "error al recibir la salida" << endl;
        }else{
            string datoRecibido(buffer, bytesRecibidos);
    if(datoRecibido == "cerrar"){
        closesocket(client);
            cout << "se cerro la conexion" << endl;
//                break;
            }
        }



}

*/


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







