#include "Servidor.hpp"
#include "Cuarto.hpp"


void Servidor::respuesta(){

}


bool Servidor::existeElUsuario(Cliente usuario){

    for (const auto& it : listClientes) {
        if (*it == usuario) {
            return true;
        }
    }

    return false;
}


bool Servidor::existeElCuarto(Cuarto sala){

    for (const auto& it : listCuartos) {
        if ((*it).getNombre() == sala.getNombre()) {
            return true;
        }
    }

    return false;
}


bool Servidor::verExisUsuario(Cliente usuario){
    return existeElUsuario(usuario);
}


bool Servidor::fueInvitado(Cliente usuario){
    for (const auto& cuarto : listCuartos){
        if (cuarto->fueInvitado(usuario)){
            return true;
        }
    }
    return false;
}


std::string Servidor::nuevoUsuario(std::string nombre){

    return "{ \"type\": \"NEW_USER\", "
           "\"username\": \"" + nombre + "\" }\n";
}


std::string Servidor::nuevoStatus(
    std::string nombre,
    std::string estatus
){

    return "{ \"type\": \"NEW_STATUS\", "
           "\"username\": \"" + nombre + "\", "
           "\"status\": \"" + estatus + "\" }\n";
}


std::string Servidor::usuariosList(
    std::vector<std::string> listaUsuarios
){

    std::string usersJson;

    for (size_t i = 0; i < listaUsuarios.size(); ++i){

        usersJson += "\"" + listaUsuarios[i] + "\"";

        if (i != listaUsuarios.size() - 1){
            usersJson += ", ";
        }
    }

    return "{ \"type\": \"USER_LIST\", "
           "\"users\": [" + usersJson + "] }\n";
}


std::string Servidor::mandarMensaje(
    std::string msg,
    Cliente usuario
){

    if (existeElUsuario(usuario)){

        return "{ \"type\": \"TEXT_FROM\", "
               "\"username\": \"" + usuario.getNombre() + "\", "
               "\"text\": \"" + msg + "\" }\n";

    }else{

        return "{ \"type\": \"RESPONSE\", "
               "\"operation\": \"TEXT\", "
               "\"result\": \"NO_SUCH_USER\", "
               "\"extra\": \"" + usuario.getNombre() + "\" }\n";
    }
}


std::string Servidor::mandarMensajePublico(
    std::string msg,
    Cliente usuario
){

    return "{ \"type\": \"PUBLIC_TEXT_FROM\", "
           "\"username\": \"" + usuario.getNombre() + "\", "
           "\"text\": \"" + msg + "\" }\n";
}


std::string Servidor::mandarMensajeCuarto(
    std::string msg,
    Cuarto sala,
    Cliente usuario
){

    for (const auto& cuarto : listCuartos){

        if (cuarto->getNombre() == sala.getNombre()){

            if (cuarto->saberPersonaEsta(usuario.getNombre())){

                return "{ \"type\": \"ROOM_TEXT_FROM\", "
                       "\"roomname\": \"" + sala.getNombre() + "\", "
                       "\"username\": \"" + usuario.getNombre() + "\", "
                       "\"text\": \"" + msg + "\" }\n";

            }else{

                return "{ \"type\": \"RESPONSE\", "
                       "\"operation\": \"ROOM_TEXT\", "
                       "\"result\": \"NOT_JOINED\", "
                       "\"extra\": \"" + sala.getNombre() + "\" }\n";
            }
        }
    }

    return "{ \"type\": \"RESPONSE\", "
           "\"operation\": \"ROOM_TEXT\", "
           "\"result\": \"NO_SUCH_ROOM\", "
           "\"extra\": \"" + sala.getNombre() + "\" }\n";
}


std::string Servidor::respuestaNuevoCuarto(
    std::string cuartoNuevo
){

    for (const auto& cuarto : listCuartos){

        if (cuarto->getNombre() == cuartoNuevo){

            return "{ \"type\": \"RESPONSE\", "
                   "\"operation\": \"NEW_ROOM\", "
                   "\"result\": \"ROOM_ALREADY_EXISTS\", "
                   "\"extra\": \"" + cuartoNuevo + "\" }\n";
        }
    }

    listCuartos.push_back(
        std::make_unique<Cuarto>(cuartoNuevo)
    );

    return "{ \"type\": \"RESPONSE\", "
           "\"operation\": \"NEW_ROOM\", "
           "\"result\": \"SUCCESS\", "
           "\"extra\": \"" + cuartoNuevo + "\" }\n";
}


std::string Servidor::invitacion(
    Cuarto sala,
    std::vector<Cliente> listaUsuarios
){

    Cuarto* cuartoPtr = nullptr;

    for (const auto& cuarto : listCuartos){

        if (cuarto->getNombre() == sala.getNombre()){

            cuartoPtr = cuarto.get();
            break;
        }
    }

    if (!cuartoPtr){

        return "{ \"type\": \"RESPONSE\", "
               "\"operation\": \"INVITE\", "
               "\"result\": \"NO_SUCH_ROOM\", "
               "\"extra\": \"" + sala.getNombre() + "\" }\n";
    }

    for (const auto& usuario : listaUsuarios){

        bool encontrado = false;

        for (const auto& cliente : listClientes){

            if (cliente->getNombre() == usuario.getNombre()){

                encontrado = true;
                break;
            }
        }

        if (!encontrado){

            return "{ \"type\": \"RESPONSE\", "
                   "\"operation\": \"INVITE\", "
                   "\"result\": \"NO_SUCH_USER\", "
                   "\"extra\": \"" + usuario.getNombre() + "\" }\n";
        }
    }

    std::string retorno;

    for (const auto& usuario : listaUsuarios){

        if (!cuartoPtr->saberPersonaEsta(usuario.getNombre())){

            retorno += "{ \"type\": \"INVITATION\", "
                        "\"username\": \"" + usuario.getNombre() + "\", "
                        "\"roomname\": \"" + sala.getNombre() + "\" }\n";
        }
    }

    return retorno;
}


std::string Servidor::seUnioCuarto(
    Cliente usuario,
    Cuarto sala
){

    Cuarto* cuartoPtr = nullptr;

    for (const auto& cuarto : listCuartos){

        if (cuarto->getNombre() == sala.getNombre()){

            cuartoPtr = cuarto.get();
            break;
        }
    }

    if (!cuartoPtr){

        return "{ \"type\": \"RESPONSE\", "
               "\"operation\": \"JOIN_ROOM\", "
               "\"result\": \"NO_SUCH_ROOM\", "
               "\"extra\": \"" + sala.getNombre() + "\" }\n";
    }

    if (!existeElUsuario(usuario)){

        return "{ \"type\": \"RESPONSE\", "
               "\"operation\": \"JOIN_ROOM\", "
               "\"result\": \"NO_SUCH_ROOM\", "
               "\"extra\": \"" + sala.getNombre() + "\" }\n";
    }

    if (!fueInvitado(usuario)){

        return "{ \"type\": \"RESPONSE\", "
               "\"operation\": \"JOIN_ROOM\", "
               "\"result\": \"NOT_INVITED\", "
               "\"extra\": \"" + sala.getNombre() + "\" }\n";
    }

    std::string addResult = cuartoPtr->agregarPersona(usuario);

    return addResult +
           "{ \"type\": \"JOINED_ROOM\", "
           "\"roomname\": \"" + sala.getNombre() + "\", "
           "\"username\": \"" + usuario.getNombre() + "\" }\n";
}


std::string Servidor::listaUsuariosCuarto(
    Cuarto sala,
    Cliente usuario
){

    Cuarto* cuartoPtr = nullptr;

    for (const auto& cuarto : listCuartos){

        if (cuarto->getNombre() == sala.getNombre()){

            cuartoPtr = cuarto.get();
            break;
        }
    }

    if (!cuartoPtr){

        return "{ \"type\": \"RESPONSE\", "
               "\"operation\": \"ROOM_USERS\", "
               "\"result\": \"NO_SUCH_ROOM\", "
               "\"extra\": \"" + sala.getNombre() + "\" }\n";
    }

    if (!cuartoPtr->saberPersonaEsta(usuario.getNombre())){

        return "{ \"type\": \"RESPONSE\", "
               "\"operation\": \"ROOM_USERS\", "
               "\"result\": \"NOT_JOINED\", "
               "\"extra\": \"" + sala.getNombre() + "\" }\n";
    }

    return cuartoPtr->listarPersonas();
}


std::string Servidor::abandonarCuarto(
    Cliente usuario,
    Cuarto sala
){

    Cuarto* cuartoPtr = nullptr;

    for (const auto& cuarto : listCuartos){

        if (cuarto->getNombre() == sala.getNombre()){

            cuartoPtr = cuarto.get();
            break;
        }
    }

    if (!cuartoPtr){

        return "{ \"type\": \"RESPONSE\", "
               "\"operation\": \"LEAVE_ROOM\", "
               "\"result\": \"NO_SUCH_ROOM\", "
               "\"extra\": \"" + sala.getNombre() + "\" }\n";
    }

    if (cuartoPtr->sacarPersona(usuario)){

        return "{ \"type\": \"LEFT_ROOM\", "
               "\"roomname\": \"" + sala.getNombre() + "\", "
               "\"username\": \"" + usuario.getNombre() + "\" }\n";

    }else{

        return "{ \"type\": \"RESPONSE\", "
               "\"operation\": \"LEAVE_ROOM\", "
               "\"result\": \"NOT_JOINED\", "
               "\"extra\": \"" + sala.getNombre() + "\" }\n";
    }
}


void Servidor::eliminarCuarto(Cuarto sala){

    for (auto it = listCuartos.begin();
         it != listCuartos.end();
         ++it){

        if ((*it)->getNombre() == sala.getNombre()){

            listCuartos.erase(it);
            break;
        }
    }
}


std::string Servidor::desconectado(Cliente usuario){

    return "{ \"type\": \"DISCONNECTED\", "
           "\"username\": \"" + usuario.getNombre() + "\" }\n";
}
