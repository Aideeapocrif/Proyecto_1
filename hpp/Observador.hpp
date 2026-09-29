#ifndef OBSERVADOR_HPP
#define OBSERVADOR_HPP 

/**
* @class Clase interface para los observadores. 
* @brief Permite actualizarlos 
*/
class Observador{

    public: 

     /**
     * @brief Método actualizar; permite actulizar el estado de la clase al recibir 
     *        una actualización 
     * @param Sin parametros. 
     * @return  
     */
     virtual void actualizar() = 0; 
     
     /**
     * @brief Destructor Observador; lo genera automaticamente. 
     * @param Sin parametros.  
     */
     virtual  ~Observador() = default;

};

#endif //OBSERVADOR_HPP
