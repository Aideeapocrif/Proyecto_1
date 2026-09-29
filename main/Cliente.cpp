#include "Cliente.hpp"
#include "Servidor.hpp"

bool Cliente::operator==(const Cliente& otro) const{
    return this->nombre == otro.nombre;
}

std::string Cliente::getNombre(){
    return this->nombre;
}

Cliente* Cliente::getInstanciaNombre(std::string nombre){
    return (nombre == this->nombre) ? this : nullptr; 
}

tipoEstatus Cliente::getEstatus(){
    return this->estatus;
}

std::string Cliente::getPersonaEstatus(){
    return this->nombre + " : " + toString(this->estatus);
}

void Cliente::actualizar(){}

bool Cliente::verificarNombre(std::string nombre){
    return (nombre.size() <= 8) ? true : false; 
}

std::string Cliente::mensaje(std::string nombre, std::string msg){

    return "{ \"type\": \"TEXT\", "
           "\"username\": \"" + nombre + "\", "
           "\"text\": " + msg + " }\n";
}

std::string Cliente::nuevoEstatus(std::string estatus){
    this->estatus = toEstatus(estatus); 
    return "{ \"type\": \"STATUS\", "
           "\"status\": \"" + estatus + "\" }\n";
}

std::string Cliente::listaUsuarios(){
    return " { \"type\": \"USERS\" }\n";
}

std::string Cliente::mensajeTodos(std::string msg){

    return "{ \"type\": \"PUBLIC_TEXT\", "
           "\"text\": " + msg + " }\n";
}

std::string Cliente::crearCuarto(std::string nombreSala){

    return "{ \"type\": \"NEW_ROOM\", "
           "\"roomname\": \"" + nombreSala + "\" }\n";
}

std::string Cliente::invitarCuartoUno(std::string nombre, std::string nombreSala){

    return "{ \"type\": \"INVITE\", "
           "\"roomname\": \"" + nombreSala + "\", "
           "\"usernames\": [\"" + nombre + "\"] }\n";
}

std::string Cliente::invitarCuartoVarios(
    std::vector<std::string> nombres,
    std::string nombreSala
){

    std::string nombreAux = "[";

    for(size_t i = 0; i < nombres.size(); i++){
        nombreAux += "\"" + nombres[i] + "\"";

        if(i < nombres.size() - 1){
            nombreAux += ", ";
        }
    }

    nombreAux += "]";

    return "{ \"type\": \"INVITE\", "
           "\"roomname\": \"" + nombreSala + "\", "
           "\"usernames\": " + nombreAux + " }\n";
}

std::string Cliente::entrarCuarto(std::string nombreSala){

    return "{ \"type\": \"JOIN_ROOM\", "
           "\"roomname\": \"" + nombreSala + "\" }\n";
}

std::string Cliente::roomUsers(std::string cuarto){

    return "{ \"type\": \"ROOM_USERS\", "
           "\"roomname\": \"" + cuarto + "\" }\n";
}

std::string Cliente::mensajeCuarto(
    std::string msg,
    std::string nombreSala
){

    return "{ \"type\": \"ROOM_TEXT\", "
           "\"roomname\": \"" + nombreSala + "\", "
           "\"text\": \"" + msg + "\" }\n";
}

std::string Cliente::salirCuarto(std::string nombreSala){

    return "{ \"type\": \"LEAVE_ROOM\", "
           "\"roomname\": \"" + nombreSala + "\" }\n";
}

std::string Cliente::desconectar(){
     
    close(this->socketCliente);
    return "{ \"type\": \"DISCONNECT\" }\n";
}

void Cliente::enviarInformacion(std::string estrucJson){
    send(this->socketCliente,estrucJson.c_str(), estrucJson.size(),0);
}

std::string Cliente::toString(tipoEstatus estatus){
    switch (estatus) {
        case tipoEstatus::ACTIVE: return "ACTIVE";
        case tipoEstatus::AWAY:   return "AWAY";
        case tipoEstatus::BUSY:   return "BUSY";
    }
}

tipoEstatus Cliente::toEstatus(std::string cadenaEstatus){
    if (cadenaEstatus == "ACTIVE"){
        return tipoEstatus::ACTIVE;
    }else if (cadenaEstatus == "AWAY"){
        return tipoEstatus::AWAY;
    }else if (cadenaEstatus == "BUSY"){
        return tipoEstatus::BUSY;
    }else{
        return tipoEstatus::INVALID;
    }
}
