#ifndef SUJETO_HPP
#define SUJETO_HPP 

/**
* @class Clase interface para el sujeto.
         Quien manda actualizaciones a los obesrvadores. 
* @brief Permite mandar respuestas a los obesrvadores.  
*/
class Sujeto{

    public: 

     /**
      * @brief Método respuesta; mandar actualizaciones/respuestas a los observadores
      * @param sin parametros.  
      */
      virtual void respuesta() = 0;

     /**
      * @brief Destructor Sujeto; lo genera automaticamente. 
      * @param in parametros.  
      */
     virtual ~Sujeto() = default;

       
 
     
     

};

#endif //SUJETO_HPP
