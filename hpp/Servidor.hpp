#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP 

#include "Sujeto.hpp"

//Librerias basicas 
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

//Libreria para json
#include <nlohmann/json.hpp>

//Libreria para socket
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Cuarto;
class Servidor : public Sujeto{

    private:

     std::vector<std::unique_ptr<Cliente>> listClientes; 
     std::vector<std::unique_ptr<Cuarto>> listCuartos; 
     int socketServidor;


    public: 
     
     /**
     * @brief Servidor; constructor de la clase servidor
     * @param Sin parametros 
     * @return Sin return 
     */
     Servidor() {
          
           //Creamos el socket, A_INET indica que sera IPv4, SOCK_STREAM el flujo, TCP y 0 el protocolo para esa combinación 
           this->socketServidor = socket(AF_INET, SOCK_STREAM, 0); 
           
            // Especificamos la dirección del socket
            sockaddr_in serverAddress;
            serverAddress.sin_family = AF_INET; //Indicamos las dirección a usar  AF_INET es IPv4
            serverAddress.sin_port = htons(8080); //Indicamos el puerto a usar 
            serverAddress.sin_addr.s_addr = INADDR_ANY; //Indicamos las direciones IP a usar, que son del tipo IPv4

            // establecemos conexión con el socket del servidor. 
            bind(socketServidor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
            //Indicamos el socket | La dirección que configuramos(IPv4) | El tamaño de la dirección. 

            //Convertimos este socket a uno de escucha 
            listen(socketServidor, 10);
          
            /*
            while (true) {

              // cuando un cliente hace conect accept es quien lo enlaza con el servidor. 
              int socketCliente = accept(socketServidor, nullptr, nullptr);

            
             }
              */

     }

    

     /**
     * @brief respuesta; es parte del la interface(Sujeto) manda la respuesta a los usuarios 
     * @param Sin parametros. 
     * @return Sin retorno. 
     */
     void respuesta() override;
     
    /**
     * @brief existeElUsuario; permite saber si el usuario esta en la lista del servidor
     * @param el nombre del usuario
     * @return booleano 
     */
     bool existeElUsuario(Cliente usuario);

     /**
     * @brief existeElCuarto; permite saber si la sala esta en la lista del servidor
     * @param el nombre de la sala
     * @return booleano 
     */
     bool existeElCuarto(Cuarto sala);

     

     /**
     * @brief verExisUsuario; Verifica si ya hay un usuario con ese nombre. 
     * @param El nombre del usuario 
     * @return string con formato json 
     */
     bool verExisUsuario(Cliente usuario);

     /**
     * @brief fueInvitado; Verifica si un usuario fue invitado a un cuarto
     * @param El Usuario  
     * @return sUn booleano
     */
     bool fueInvitado(Cliente usuario);
     
     /**
     * @brief nuevoUsuario; avisa a los demas de un nuevo usuario y maneja las conexiones 
     * @param sin parametros 
     * @return string de tipo json 
     */
     std::string nuevoUsuario(std::string nombre); 

     /**
     * @brief nuevoStatus; modifica el status  
     * @param Sin parametros 
     * @return string de tipo json 
     */
     std::string nuevoStatus(std::string nombre, std::string estatus);
     
     /**
     * @brief usuariosList; manda la lista de usuarios conectados al servidor.   
     * @param sin parametros
     * @return  string de tipo json 
     */
     std::string usuariosList(std::vector<std::string> listaUsuarios); 

     /**
     * @brief mandarMensaje; manda un mensaje a cierta persona 
     * @param El cliente a mandar mensaje y para quien es el mensaje
     * @return string de tipo json 
     */
     std::string mandarMensaje(std::string msg, Cliente usuario);

     /**
     * @brief mandarMensajePublico; manda un mensaje a todos los usuarios conectados 
     * @param El mensaje
     * @return string de tipo json 
     */
     std::string mandarMensajePublico(std::string msg, Cliente usuario); 

     /**
     * @brief respuestaNuevoCuarto; responde a la creación de un cuarto nuevo.  
     * @param El nombre del cuarto
     * @return string de tipo json 
     */
     std::string respuestaNuevoCuarto(std::string cuartoNuevo);

     /**
     * @brief invitacion; invita a uno o mas usuarios a un cuarto. 
     * @param El mensaje
     * @return string de tipo json 
     */
     std::string invitacion(Cuarto sala, std::vector<Cliente> listaUsuarios);
     

     /**
     * @brief mandarMensajeCuarto; manda un mensaje al cuarto 
     * @param El mensaje y el cuarto a mandar el mensaje
     * @return string de tipo json 
     */
     std::string mandarMensajeCuarto(std::string msg, Cuarto sala, Cliente usuario);

     /**
     * @brief seUnioCuarto; une un cliente a cierto cuarto  
     * @param El cliente a agregar, nombre del cuarto 
     * @return un string de tipo json 
     */
     std::string seUnioCuarto(Cliente usuario, Cuarto sala); 

     /**
     * @brief listaUsuariosCuarto; retorna la lista de usuarios en el cuarto
     * @param el nombre del cuarto
     * @return un string de tipo json
     */
     std::string listaUsuariosCuarto(Cuarto sala, Cliente usuario); 

     /**
     * @brief abandonarCuarto; saca a una persona del cuarto e informa.  
     * @param El cliente a sacar
     * @return un string de tipo json
     */
     std::string abandonarCuarto(Cliente usuario, Cuarto sala);

     /**
     * @brief eliminarCuarto; elimina el cuarto en caso de tener 0 elementos. 
     * @param El cuarto
     * @return nada
     */
     void eliminarCuarto(Cuarto sala);

     /**
     * @brief desconectado; desconecta al usuario del servidor
     * @param El cliente a desconectar
     * @return un string de tipo json
     */
     std::string desconectado(Cliente usuario);  

};

#endif //SERVIDOR_HPP
