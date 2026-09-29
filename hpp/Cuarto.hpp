#ifndef CUARTO_HPP
#define CUARTO_HPP 

#include "Observador.hpp"
#include "Cliente.hpp"


//Librerias basicas 
#include <string>
#include <vector>
#include <algorithm>

//Libreria para json
#include <nlohmann/json.hpp>



class Cuarto : public Observador{
    
    private: 
     std::string nombre; 
     std::vector<Cliente> integrantes; 
     std::vector<Cliente> invitados; 

     

    public: 
     
    /**
     * @brief Cuarto; El constructor de cuarto 
     * @param El nombre del cuarto. 
     * @return Nada
     */
     Cuarto(std::string nombre) : nombre(nombre) {
        if(!verificarNombreCuarto(nombre)){
            std::cout << "La longitud de del nombre del cuarto debe ser menor o igual a 16 caractares.  " << std::endl;
        }
     }

     /**
     * @brief ==; operador para permitir la comparación usando ==
     * @param La referencia a un cliente
     * @return booleano, si es el mismo o no lo es. 
     */
     bool operator==(const Cuarto& otro) const;

     /**
     * @brief getIntegrantes; retorna el nombre 
     * @param No tiene
     * @return El string del nombre  
     */
    std::string getNombre(); 

     /**
     * @brief getInstanciaCuarto; para obtener la instancia a partir del nombre
     * @param El nombre
     * @return  el puntero de la instancia. 
     */
     Cuarto* getInstanciaCuarto(std::string sala);

     /**
     * @brief getIntegrantes; retorna los integrantes del cuarto 
     * @param No tiene
     * @return Un vector de clientes  
     */
    std::vector<Cliente> getIntegrantes(); 
    
    /**
     * @brief getInvitados; retorna los integrantesinvitados. 
     * @param No tiene
     * @return Un vector de clientes  
     */
    std::vector<Cliente> getInvitados();

     /**
     * @brief actualizar; actualiza los datos del cuarto
     * @param No tiene 
     * @return No tiene  
     */
    void actualizar() override; 
    
     /**
     * @brief listarPersonas; manda una lista de string de las personas con su estatus
     * @param No tiene
     * @return Un string de las personas 
     */
    std::string listarPersonas();

    /**
     * @brief verificarNombreCuarto; verifica que el número de caracteres del cuerto, sea menor o igual a 16. 
     * @param  El nombre, string
     * @return un booleano, true or false. 
     */
     bool verificarNombreCuarto(std::string nombre);

     /**
     * @brief agregarPersona; agrega una persona al cuarto  de invitados
     * @param El invitado a agregar
     * @return nada
     */
    std::string agregarInvitado(Cliente persona);

    /**
     * @brief fueInvitado; checa si una persona fue invitada. 
     * @param La persona a checar 
     * @return booleano
     */
    bool fueInvitado(Cliente persona);
    
     /**
     * @brief agregarPersona; agrega una persona al cuarto 
     * @param El cliente a agregar
     * @return string de tipo json
     */
    std::string agregarPersona(Cliente persona);

    /**
     * @brief sacarPersona; Elimina un cliente del cuarto
     * @param La persona 
     * @return Un booleano para saber si se logro sacar o no.  
     */
    bool sacarPersona(Cliente persona);


    /**
     * @brief saberPersonaEsta; Indica si hay una persona en el grupo
     * @param El nombre de la persona. 
     * @return Un booleano para saber si esta o no esta  
     */
    bool saberPersonaEsta(std::string nombre);



};

#endif //CUARTO_HPP
