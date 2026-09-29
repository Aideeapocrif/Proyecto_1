#include "Cuarto.hpp"


bool Cuarto::operator==(const Cuarto& otro) const{
    return this->nombre == otro.nombre;
}


std::vector<Cliente> Cuarto::getIntegrantes(){
    return this->integrantes;
}


std::vector<Cliente> Cuarto::getInvitados(){
    return this->invitados;
}

std::string Cuarto::getNombre(){
    return this->nombre;
}

Cuarto* Cuarto::getInstanciaCuarto(std::string sala){
    return (sala == this->nombre) ? this : nullptr;
}



void Cuarto::actualizar(){}

std::string Cuarto::listarPersonas(){

    std::string listaPersonas = "";

    for (int i = 0; i < this->integrantes.size(); i++){

        listaPersonas += "\"" + integrantes[i].getNombre() + "\": \""
                      + integrantes[i].toString(integrantes[i].getEstatus()) + "\"";

        if (i != this->integrantes.size() - 1){
            listaPersonas += ", ";
        }
    }

    return "{ \"type\": \"ROOM_USER_LIST\", "
           "\"roomname\": \"" + nombre + "\", "
           "\"users\": {" + listaPersonas + "} }\n";
}

bool Cuarto::verificarNombreCuarto(std::string nombre){
    return nombre.size() <= 16 ? true : false;
}

 
std::string Cuarto::agregarInvitado(Cliente persona){
    this->invitados.push_back(persona);
    return persona.getNombre();
}

bool Cuarto::fueInvitado(Cliente persona){
    for (const auto& invitado : this->invitados){
        if (invitado == persona){
            return true;
        }
    }
    return false;
}

std::string Cuarto::agregarPersona(Cliente persona){
    this->integrantes.push_back(persona);
    std::erase(this->invitados, persona);
    
    return " { \"type\": \"RESPONSE\", "
           "\"operation\": \"JOIN_ROOM\", "
           "\"result\": \"SUCCESS\", "
           "\"extra\": " + persona.getNombre() + " }\n";
}

bool Cuarto::sacarPersona(Cliente persona){

    auto estaPersona = std::find(
        this->integrantes.begin(),
        this->integrantes.end(),
        persona
    );

    if (estaPersona != this->integrantes.end()) {
        std::erase(this->integrantes, persona);
        return true;
    }else{
        return false;
    }
}

bool Cuarto::saberPersonaEsta(std::string nombre){

    for(int i = 0; i < this->integrantes.size(); i++){

        if (nombre == this->integrantes[i].getNombre()){
            return true;
        }
    }

    return false;
}
