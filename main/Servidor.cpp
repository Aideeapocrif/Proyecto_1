#include "Servidor.hpp"
#include "Cuarto.hpp"





void Servidor::conexion(){
    while (true) {
      // cuando un cliente hace conect accept es quien lo enlaza con el servidor. 
      int socketCliente = accept(socketServidor, nullptr, nullptr);
      std::thread(&Servidor::entradaUsuario, this, socketCliente).detach(); 
    }
        
}

json Servidor::recibo(int socketParam){
   
    char buffer[1024];
    int bytesRecibidos = recv(socketParam, buffer, sizeof(buffer) - 1, 0);
    if (bytesRecibidos > 0) {
       buffer[bytesRecibidos] = '\0';
       std::string mensaje(buffer, bytesRecibidos);
       nlohmann::json datos = nlohmann::json::parse(mensaje);
       return datos;
    }
   return nullptr;
}

void Servidor::respuesta(std::vector<Cliente> PersonasEnviar, std::string msg){

    if (PersonasEnviar.size() == listaConectados.size()) {
       std::lock_guard<std::mutex> lock(mtx);
       for(int j = 0; j < listaConectados.size(); j++){
         send(listaConectados.socketCliente, msg.c_str(), msg.size(), 0);
       }
    }else{
        for (int i = 0; i < PersonasEnviar.size(); i++){
            std::lock_guard<std::mutex> lock(mtx);
            for(int j = 0; j < listaConectados.size(); j++){
              if (PersonasEnviar.getNombre() == listaConectados.nombreCliente){
                 send(listaConectados.socketCliente, msg.c_str(), msg.size(), 0);
              }
            }
        }
    }

void Servidor::entradaUsuario(int socketCliente){
    json datos = recibo(socketCliente);

      if (datos["type"] == "IDENTIFY"){
          conectClienteSocket relacionClieSocket(datos["username"], socketCliente);
          std::lock_guard<std::mutex> lock(mtx);
          listaConectados.push_back(relacionClieSocket);

      }else if(datos["type"] == "TEXT"){
        std::string json  = mandarMensaje(datos["text"], datos["username"]);
        respuesta(datos["username"], json)


      }else if(datos["type"] == "STATUS"){
        std::string json = nuevoEstatus(buscarNombre(socketCliente) , datos["status"]);
        respuesta(listClientes, json);
          
      }else if(datos["type"] == "USERS"){
        std::string json = usuariosList(); 
        respuesta(buscarNombre(socketCliente), json); 

      }else if(datos["type"] == "PUBLIC_TEXT"){
         

      }else if(datos["type"] == "NEW_ROOM"){
          
      }else if(datos["type"] == "INVITE"){
          
      }else if(datos["type"] == "JOIN_ROOM"){
          
      }else if(datos["type"] == "ROOM_USERS"){
          
      }else if(datos["type"] == "ROOM_TEXT"){
          
      }else if(datos["type"] == "LEAVE_ROOM"){
          
      }else if(datos["type"] == "DISCONNECT"){
          
      }else {

      }

}




std::string buscarNombre(int socketParam){
    for(size_t i = 0; i < listaConectados.size(); i++){
        if(listaConectados[i].socketCliente == socketParam){
            return listaConectados[i].nombreCliente;
        }
    }
}


int buscarSocket(std::string nombre){
    for(size_t i = 0; i < listaConectados.size(); i++){
        if(listaConectados[i].nombreCliente == nombre){
            return listaConectados[i].socketCliente;
        }
    }
}

bool Servidor::existeElUsuario(Cliente usuario){
    for (const auto& este : listClientes) {
        if (*este == usuario) {
            return true;
        }
    }
    return false;
}


bool Servidor::existeElCuarto(Cuarto sala){

    for (const auto& este : listCuartos) {
        if (*este == sala) {
            return true;
        }
    }
    return false;
}



std::string Servidor::nuevoUsuario(std::string nombre){
    return "{ \"type\": \"NEW_USER\", "
             "\"username\": \"" + nombre + "\" }\n";
}


std::string Servidor::nuevoStatus(std::string nombre,std::string estatus){

    return "{ \"type\": \"NEW_STATUS\", "
           "\"username\": \"" + nombre + "\", "
           "\"status\": \"" + estatus + "\" }\n";
}


std::string Servidor::usuariosList(){

    std::string usuariosJSON;

    for (size_t i = 0; i < listUsuarios.size(); ++i){
        usuariosJSON += "\"" + listUsuarios[i] + "\"";
        if (i != listUsuarios.size() - 1){
            usuariosJSON += ", ";
        }
    }

    return "{ \"type\": \"USER_LIST\", "
             "\"users\": [" + usuariosJSON + "] }\n";
}


std::string Servidor::mandarMensaje(std::string msg, Cliente usuario){

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


std::string Servidor::mandarMensajePublico( std::string msg, Cliente usuario){

    return "{ \"type\": \"PUBLIC_TEXT_FROM\", "
             "\"username\": \"" + usuario.getNombre() + "\", "
             "\"text\": \"" + msg + "\" }\n";
}


std::string Servidor::mandarMensajeCuarto( std::string msg, Cuarto sala, Cliente usuario){

    if (existeElCuarto(sala)){
       if (existeElUsuario(usuario)){
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

    return "{ \"type\": \"RESPONSE\", "
           "\"operation\": \"ROOM_TEXT\", "
           "\"result\": \"NO_SUCH_ROOM\", "
           "\"extra\": \"" + sala.getNombre() + "\" }\n";
}


std::string Servidor::respuestaNuevoCuarto(std::string cuartoNuevo){

    for (const auto& cuarto : listCuartos){
        if (cuarto->getNombre() == cuartoNuevo){
            return "{ \"type\": \"RESPONSE\", "
                   "\"operation\": \"NEW_ROOM\", "
                   "\"result\": \"ROOM_ALREADY_EXISTS\", "
                   "\"extra\": \"" + cuartoNuevo + "\" }\n";
        }
    }

    listCuartos.push_back(std::make_unique<Cuarto>(cuartoNuevo));

    return "{ \"type\": \"RESPONSE\", "
           "\"operation\": \"NEW_ROOM\", "
           "\"result\": \"SUCCESS\", "
           "\"extra\": \"" + cuartoNuevo + "\" }\n";
}


std::string Servidor::invitacion(Cuarto sala, std::vector<Cliente> listaUsuarios){

    Cuarto* cuartoPtr = nullptr;
    if (existeElCuarto(sala)){
        cuartoPtr = sala;
        break;
    }

    if (!cuartoPtr){
        return "{ \"type\": \"RESPONSE\", "
               "\"operation\": \"INVITE\", "
               "\"result\": \"NO_SUCH_ROOM\", "
               "\"extra\": \"" + sala.getNombre() + "\" }\n";
    }

    for (const auto& usuario : listaUsuarios){
        bool encontrado = false;
        if (existeElUsuario(usuario)){
                encontrado = true;
                break;
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


std::string Servidor::seUnioCuarto(Cliente usuario, Cuarto sala){

    Cuarto* cuartoPtr = nullptr;
        if (existeElCuarto(sala)){
            cuartoPtr = sala;
            break;
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

    std::string agregarUsuario = cuartoPtr->agregarPersona(usuario);

    return agregarUsuario +
           "{ \"type\": \"JOINED_ROOM\", "
           "\"roomname\": \"" + sala.getNombre() + "\", "
           "\"username\": \"" + usuario.getNombre() + "\" }\n";
}


std::string Servidor::listaUsuariosCuarto( Cuarto sala, Cliente usuario){

    Cuarto* cuartoPtr = nullptr;
    if (existeElCuarto(sala)){
            cuartoPtr = sala;
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


std::string Servidor::abandonarCuarto( Cliente usuario, Cuarto sala){

    Cuarto* cuartoPtr = nullptr;

     if (existeElCuarto(sala)){
            cuartoPtr = sala;
            break;
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

    for (auto este = listCuartos.begin();   este != listCuartos.end();   ++este){
        if ((*este)->getNombre() == sala.getNombre()){
            listCuartos.erase(este);
            break;
        }
    }
}


std::string Servidor::desconectado(Cliente usuario){
    return "{ \"type\": \"DISCONNECTED\", "
             "\"username\": \"" + usuario.getNombre() + "\" }\n";
}
