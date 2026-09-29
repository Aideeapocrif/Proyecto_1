#ifndef CLIENTE_HPP
#define CLIENTE_HPP 

//Librerias del programa. 
#include "Observador.hpp"
#include "tipoEstatus.hpp"

//Librerias basicas 
#include <string>
#include <vector>
#include <iostream>

//Libreria para json
#include <nlohmann/json.hpp>

//Libreria para socket
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using json = nlohmann::json;

class Cliente : public Observador{


    private: 

     std::string nombre; 
     tipoEstatus estatus;
     int socketCliente; 
     class Servidor* elServidor; 

    public:

     /**
     * @brief Constructor de Cliente
     *        Verifica que nombre no este siendo usado ya. 
     * @param El nombre, el estatus, el servidor 
     */

     Cliente(std::string nombre, Servidor* elServidor) {

        if(verificarNombre(nombre)){
           this->nombre = nombre; 
           this->elServidor = elServidor;
           this->estatus = tipoEstatus::ACTIVE;

           //Creamos el socket, A_INET indica que sera IPv4, SOCK_STREAM el flujo, TCP y 0 el protocolo para esa combinación 
           this->socketCliente = socket(AF_INET, SOCK_STREAM, 0);


            // Especificamos la dirección del socket
            sockaddr_in serverAddress;
            serverAddress.sin_family = AF_INET;
            serverAddress.sin_port = htons(8080);
            serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

            // establecemos conexión con el socket del servidor. 
            connect(this->socketCliente, (struct sockaddr*)&serverAddress,sizeof(serverAddress)); 

            //Identificamos con el servidor. 
            std::string identify = "{ \"type\": \"IDENTIFY\", \"username\": \"" + this->nombre + "\" }\n";

        }else{ 
            std::cout << "La longitud de tu nombre debe ser menor o igual a  8 caractares.  " << std::endl;
        }

     }

     /**
     * @brief ==; operador para permitir la comparación usando ==
     * @param La referencia a un cliente
     * @return booleano, si es el mismo o no lo es. 
     */
     bool operator==(const Cliente& otro) const;

     /**
     * @brief getNombre; para obtener el nombre de la instancía 
     * @param Sin parametros
     * @return el nombre, string
     */
     std::string getNombre();

     /**
     * @brief getInstanciaNombre; para obtener la instancia a partir del nombre. 
     * @param El nombre del usuario
     * @return un puntero a la instancía. 
     */
     Cliente* getInstanciaNombre(std::string nombre);

     /**
     * @brief getEstatus; para obtener en estatus de la isntancía
     * @param Sin parametros
     * @return la instancia, tipoEstatus
     */
     tipoEstatus getEstatus();

     /**
     * @brief getPersonaEstatus; obtiene un string de tipo json con el nombre y el estatus. 
     * @param Sin parametros
     * @return string de tipo json. 
     */
     std::string getPersonaEstatus();
     
     /**
     * @brief actualizar; permite actualizar el el estado de la instacia
     * @param Sin parametros
     * @return 
     */
     void actualizar() override; 

     /**
     * @brief verificarNombre; verifica que el número de caracteres del usuario sea menor a 8. 
     * @param  El nombre, string
     * @return un booleano, true or false. 
     */
     bool verificarNombre(std::string nombre);

     
     /**
     * @brief mensaje; manda un str par para el servidor, el mensaje a mandar. 
     * @param El mensaje a mandar y el nombre de quien 
     * @return Un string con formato json.  
     */
     std::string mensaje(std::string nombre, std::string msg); 


     /**
     * @brief listaUusarios; es para indicar que se quiere la lista de usuarios en el servidor 
     * @param Sin parametros 
     * @return Un string con formato json.
    */
     std::string listaUsuarios();

     /**
     * @brief mensajeTodos; manda un str par para el servidor, el mensaje a mandara todos. 
     * @param El mensaje a mandar
     * @return Un string con formato json.  
     */
     std::string mensajeTodos(std::string msg); 

      /**
     * @brief nuevoEstatus; modifica el estatus 
     * @param El estatus como string
     * @return el string en formato json con el estatus
     */
     std::string nuevoEstatus(std::string estatus);

     /**
     * @brief crearCuarto; manda un str con formato json indicando que se quiere crear un cuarto
     * @param El nombre de la sala/cuarto.
     * @return Un string con formato json.  
     */
     std::string crearCuarto(std::string nombreSala);

     /**
     * @brief invitarCuartoUno; invitamos al cuarto a un usuario 
     * @param El nombre del usuario, el nombre de la sala. 
     * @return Un string con formato json.  
     */
     std::string invitarCuartoUno(std::string nombre, std::string nombreSala);

     /**
     * @brief invitarCuartoVarios; Invitamos al cuarto a varios. 
     * @param Una lista de nombres de usuarios, el nombre de la sala. 
     * @return Un string con formato json.  
     */
     std::string invitarCuartoVarios(std::vector<std::string> nombres, std::string nombreSala);
     
     /**
     * @brief entrarCuarto; método para acceder a una sala. 
     * @param El nombre de la sala.  
     * @return Un string con formato json.  
     */
     std::string entrarCuarto(std::string nombreSala); 

     /**
     * @brief roomUsers; llamada al servidor para tener la lista de usuarios de un cuarto. 
     * @param El nombre de la sala.  
     * @return Un string con formato json.  
     */
     std::string roomUsers(std::string cuarto);
     
     /**
     * @brief mensajeCuarto; método para mandar un mensaje a cierto cuarto  
     * @param El nombre de la sala y el mensaje a mandar  
     * @return Un string con formato json.  
     */
     std::string mensajeCuarto(std::string msg,std::string nombreSala); 

     /**
     * @brief salirCuarto; método para salir de un cuarto 
     * @param El nombre de la sala.  
     * @return Un string con formato json.  
     */
     std::string salirCuarto(std::string nombreSala); 

    /**
     * @brief desconectar; nos permite salir del servidor 
     * @param Sin parametros  
     * @return Un string en formato json. 
     */
     std::string desconectar(); 

     /**
     * @brief enviarInformación
     * @param La estructura Json de tipo string a mandar  
     * @return nada
     */
     void enviarInformacion(std::string estrucJson);

    
     /**
     * @brief toString; pasa de tipoEstatus a cadena 
     * @param El valor de tipo estatus 
     * @return El valor como string
     */
    std::string toString(tipoEstatus estatus);
    
     /**
     * @brief toEstatus; pasa de cadena a tipoEstatus
     * @param El valor en string  
     * @return El valor como tipoEstatus
     */
    tipoEstatus toEstatus( std::string cadenaEstatus);


}; 

 #endif //CLIENTE_HPP
