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

                //bueno en principio logro que segun el rol (nombre es lo mismo porque es un solo admin que se llama admin) funcione (creo) el tema es que solo me deja
                //elegir una opcion del menu si elijko otra se rompe el codigo de servidor y queda en bluce infinito (en especial el cerrar sesion)
                //por eso esto que trabaje hoy 17/10/2023 no lo subi el github
                menuAdmin();
                //menuConexion();
                //menu();


            }
            }
            }


//CREDENCIALES TXT
bool credencial() {
    std::ifstream archivo("credenciales.txt");
    std::string linea;

    string usuario, contrasena;
    string credRecibida(buffer);
    bool credencialesCorrectas = false;

    int bytesRecibidos = recv(client, buffer, sizeof(buffer) - 1, 0);

    if (bytesRecibidos == -1) {
        // Error al recibir usuario
        credencial();
    } else {
        string datoRecibido(buffer, bytesRecibidos);

        // Verificar credenciales
        size_t pos = datoRecibido.find('|');
        if (pos != string::npos) {
            usuario = datoRecibido.substr(0, pos);
            contrasena = datoRecibido.substr(pos + 1);

            while (std::getline(archivo, linea)) {
                size_t pos = linea.find('|');

                if (pos != string::npos) {
                    string userTxt = linea.substr(0, pos);
                    size_t pos2 = linea.find('|', pos + 1);

                    if (pos2 != string::npos) {
                        string contrasenaTxt = linea.substr(pos + 1, pos2 - pos - 1);

                        if (usuario == userTxt && contrasena == contrasenaTxt) {
                            cout << "Datos de usuario correctos" << endl;
                            credencialesCorrectas = true;
                            break;
                        }
                    }
                }
            }

            if (!credencialesCorrectas) {
                cout << "Usuario o contraseña incorrectas" << endl;
                const string user = usuario;
                aumentarIntentosFallidos(user);
            }

            // Verificación de usuario bloqueado NO ME FUNCIONA DE MOMENTO ESTO DEBERIA DECIRME QUE SI UN USER CON MAS O IGUAL A 3 INTENTOS QUE ESTA BLOQUEADO
            const string user = usuario;
            if (usuarioEstaBloqueado(user)) {
                string mensajeBloqueo = "Usuario bloqueado. Tu cuenta ha sido bloqueada.";
                send(client, mensajeBloqueo.c_str(), mensajeBloqueo.length(), 0);
                cout << "Usuario bloqueado: " << usuario << endl;
                // Cierra el flujo aquí sin continuar a menús

            }else{
                send(client, usuario.c_str(), usuario.length(), 0);
            }


        }
    }

    return credencialesCorrectas;
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
            break;

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


}

void menuAdmin(){
    cout << "test menu admin 1" << endl;

    bool validado = credencial();
    bool verificar = true;

    if(validado == true){
        cout << "test menu admin" << endl;

        int option;
        recv(client, (char *)&option, sizeof(option),0);

        while(verificar){
            if(option==2){
                nuevaTraduccion();
                break;
            }

            if(option==3){
                altaYDesbloqueo();
                break;
            }

            if(option==0){
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
            menuAdmin();
        }
    }





 //aqui termina SERVER







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
                cout << "error al recibir la traduccion del cliente" << endl;
            }else{
                string datoRecibido(buffer, bytesRecibidos);

                minusculas(datoRecibido);

                regex formato("^[a-zA-Z]+:[a-zA-Z]+$");

                    if (!regex_match (datoRecibido, formato)){
                        cout << "No fue posible insertar la traduccion. El formato de insercion debe ser palabraEnIngles:traduccionEnEspaniol" << endl;
                        memset(buffer, 0, sizeof(buffer));  // Limpia el búfer para evitar mensajes no deseados
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
               alta();
        }else{
            if(subDato==2){
                desbloquearUsuario();
            }
        }
}

//ALTA
void alta(){
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
                    fprintf(puntero, "%s|CONSULTA|0 \n", datoRecibido.c_str());
                    cout << "Nuevo usuario recibido test: " + datoRecibido << endl;
                }else{
                    cout << "NO se puede ingrear un usuario con la contrasena vacia" << endl;                                }
                } else {
                    cout << "No se pudo guardar el usuario 'admin'" << endl;
                }
                } else {
                    cout << "Dato recibido no valido: " + datoRecibido << endl;
                    }


            fclose(puntero);
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

//manejo usuario

bool manejoUsuario(){
    string user;
    bool flag = false;

    int bytesRecibidos = recv (client, buffer, sizeof(buffer) -1 , 0);

     if(bytesRecibidos == -1){
            cout << "error al recibir usuario" << endl;
        }else{
            string datoRecibido(buffer, bytesRecibidos);

            size_t pos = datoRecibido.find('|');

            if(pos != string::npos){
                user = datoRecibido.substr(0,pos);
                cout << user <<endl;
        }

        if(user=="admin"){
            flag = true;
        }else{
            flag = false;
        }
}

    return flag;
}

//obtener rol usuario
string obtenerRol(){
    //////////////
    string usuario;

    int bytesRecibidos = recv (client, buffer, sizeof(buffer) -1 , 0);

     if(bytesRecibidos == -1){
            cout << "error al recibir usuario test1" << endl;
        }else{
            string datoRecibido(buffer, bytesRecibidos);

            size_t pos = datoRecibido.find('|');

            if(pos != string::npos){
                usuario = datoRecibido.substr(0,pos);
                cout << usuario <<endl;
                send(client, usuario.c_str(), usuario.length(), 0);
        }


}
///////

    return usuario;

}

//menu para elegir
void menu(){
    string rol = obtenerRol();

    if(rol == "admin"){
        cout << "test menu admin" << endl;
        menuAdmin();
    }else{
        menuConexion();
    }
}


//aumentar intentos fallidos de usuario
void aumentarIntentosFallidos(const string& usuario) {
    fstream archivo("credenciales.txt", ios::in | ios::out);

    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    string nuevoContenido;
    bool usuarioEncontrado = false;
    int intentosFallidos;

    while (getline(archivo, linea)) {
        size_t pos = linea.find('|');
        string usuarioEnArchivo = linea.substr(0, pos);

        if (usuarioEnArchivo == usuario) {
            intentosFallidos = stoi(linea.substr(linea.find_last_of('|') + 1));
            intentosFallidos++;

             if (intentosFallidos >= 3) {
                cout << "Tu usuario esta bloqueado alcanzo los 3 intentos." << endl;
                string mensajeBloqueo = "Tu usuario esta bloqueado.";
                send(client, mensajeBloqueo.c_str(), mensajeBloqueo.length(), 0);
            }


            usuarioEncontrado = true;
            linea = usuario + linea.substr(pos, linea.find_last_of('|') - pos) + "|" + to_string(intentosFallidos);
        }

        nuevoContenido += linea + '\n';
    }

    archivo.close();

    if (!usuarioEncontrado) {
        cout << "Usuario no encontrado." << endl;
        return;
    }

        archivo.open("credenciales.txt", ios::out | ios::trunc);
        archivo << nuevoContenido;
        archivo.close();




}
//usuario bloqueado
bool usuarioEstaBloqueado(const string& usuario) {
    std::ifstream archivo("credenciales.txt");
    string linea;
    bool flag = false;

    while (std::getline(archivo, linea)) {
        cout << "Línea completa: " << linea << endl;
        size_t pos = linea.find('|');
        if (pos != string::npos) {
            string usuarioTxt = linea.substr(0, pos);
            cout << "Usuario: " << usuarioTxt << endl;

            size_t pos2 = linea.find('|', pos + 1);
            if (pos2 != string::npos) {
                string contrasena = linea.substr(pos + 1, pos2 - pos - 1);
                cout << "Contraseña: " << contrasena << endl;

                size_t pos3 = linea.find('|', pos2 + 1);
                if (pos3 != string::npos) {
                    string rol = linea.substr(pos2 + 1, pos3 - pos2 - 1);
                    cout << "Rol: " << rol << endl;

                    string intentosStr = linea.substr(pos3 + 1);
                    cout << "Intentos: " << intentosStr << endl;

                    if (usuarioTxt == usuario && rol != "ADMIN") {
                        // Verificar si intentosStr es un número antes de intentar convertirlo
                        if (std::all_of(intentosStr.begin(), intentosStr.end(), ::isdigit)) {
                            int intentos = std::stoi(intentosStr);
                            if (intentos >= 3) {
                                flag = true; // Si el usuario no es ADMIN y tiene 3 o más intentos, está bloqueado
                            }
                        }
                    }
                }
            }
        }
    }

    return flag; // Si no se encuentra el usuario o no cumple las condiciones, no está bloqueado
}

//desbloquear usuario de almacenamineto
void desbloquearUsuarioEnAlmacenamiento(const string& usuario) {
    fstream archivo("credenciales.txt", ios::in | ios::out);

    if (archivo.is_open()) {
        string linea;
        size_t pos = 0;

        while (getline(archivo, linea)) {
            istringstream iss(linea);
            string user;
            string contrasena;
            string rol;
            int intentos;

            if (getline(iss, user, '|') &&
                getline(iss, contrasena, '|') &&
                getline(iss, rol, '|') &&
                (iss >> intentos)) {

                if (user == usuario && intentos >= 3) {
                    // Usuario encontrado y bloqueado, restablecer los intentos
                    intentos = 0;
                }

                // Reconstruir la línea y escribirla en el archivo
                archivo.seekp(pos);
                archivo << user << '|' << contrasena << '|' << rol << '|' << intentos;
                archivo << endl;
            }

            pos = archivo.tellp(); // Guarda la posición para futuras modificaciones
        }

        archivo.close();
        cout << "Usuario desbloqueado con exito." << endl;
    } else {
        cout << "Error al abrir el archivo de credenciales." << endl;
    }
}

//desbloquear usuario
void desbloquearUsuario(){
    string usuario;

    int bytesRecibidos = recv (client, buffer, sizeof(buffer) -1 , 0);

     if(bytesRecibidos == -1){
            cout << "error al recibir usuario test2" << endl;
    }else{
            string datoRecibido(buffer, bytesRecibidos);
            cout << datoRecibido << endl;
            usuario = datoRecibido;
            cout << usuarioEstaBloqueado(usuario) << endl;
    }


    if(usuarioEstaBloqueado(usuario)){
        desbloquearUsuarioEnAlmacenamiento(usuario);
        string mensaje = "El usuario fue desbloqueado";
        send(client, mensaje.c_str(), mensaje.length(), 0);
    }else{
        string mensaje = "El usuario no fue desbloqueado";
        send(client, mensaje.c_str(), mensaje.length(), 0);
    }
}

};







