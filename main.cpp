

#include <iostream>
#include <cstring>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(){

    //inicializar winsock
    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
        std::cerr << "ERROR EN LA INIZIALIZACION DEL WINSOCK." << std::endl;
        return 1;
    }



    //creacion del socket
    SOCKET servidorSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(servidorSocket == INVALID_SOCKET){
        std::cerr << "ERROR AL CREAR EL SOCKET." << std::endl;
        WSACleanup();
        return 1;
    }

    //configurar la direccion del servidor
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080); //puerto de comunicacion
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); //tuve que ponerla asi porque de otra manera da error


    // vincular el socket a la direccion
    if (bind(servidorSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR){
        std::cerr << "ERROR AL VINCULAR EL SOCKET." << std::endl;
        closesocket(servidorSocket);
        WSACleanup();
        return 1;
    }

    //ESCUCHAR CONEXIONES ENTRANTES
    if(listen(servidorSocket, 5)==SOCKET_ERROR){
        std::cerr << "ERROR AL ESCUCHAR CONEXIONES ENTRANTES." << std::endl;
        closesocket(servidorSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "SERVIDOR ESPERA CONEXIONES..." << std::endl;

    while(true){
        //aceptar conexion entrante
        SOCKET clienteSocket = accept(servidorSocket, NULL, NULL);
        if(clienteSocket == INVALID_SOCKET){
            std::cerr << "ERROR AL ACEPTAR LA CONEXION." << std::endl;
            closesocket(servidorSocket);
            WSACleanup();
            return 1;
        }

        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        //recibir los datos del cliente
        int bytesRead = recv (clienteSocket, buffer, sizeof(buffer), 0);
        if(bytesRead == SOCKET_ERROR){
            std::cerr << "ERROR AL ENVIAR DATOS AL CLIENTE." << std::endl;
        }

        closesocket(clienteSocket);
    }

    closesocket(servidorSocket);
    WSACleanup();

    return 0;

}
