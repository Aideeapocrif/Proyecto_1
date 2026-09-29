#include "Cliente.hpp"
#include "Cuarto.hpp"
#include "Servidor.hpp"

#include <iostream>
#include <string>
#include <vector>


void mostrarMenu(){

    std::cout << "\n";
    std::cout << "========== SERVICIO DE MENSAJERIA ==========\n";
    std::cout << "1. Mandar mensaje\n";
    std::cout << "2. Mandar mensaje a todos\n";
    std::cout << "3. Crear cuarto\n";
    std::cout << "4. Invitar usuario a cuarto\n";
    std::cout << "5. Entrar a cuarto\n";
    std::cout << "6. Ver usuarios de cuarto\n";
    std::cout << "7. Mandar mensaje a cuarto\n";
    std::cout << "8. Salir de cuarto\n";
    std::cout << "9. Cambiar estatus\n";
    std::cout << "10. Desconectar\n";
    std::cout << "============================================\n";
    std::cout << "Opcion: ";
}


int main(){

    std::string nombre;
    std::cout << "Escribe tu nombre: ";
    std::cin >> nombre;

    Servidor* elServidor = nullptr;

    Cliente cliente(nombre, elServidor);

    int opcion = 0;

    while(opcion != 10){

        mostrarMenu();
        std::cin >> opcion;

        if(opcion == 1){

            std::string nombrePersona;
            std::string msg;

            std::cout << "Nombre de la persona: ";
            std::cin >> nombrePersona;

            std::cin.ignore();

            std::cout << "Mensaje: ";
            std::getline(std::cin, msg);

            std::string json = cliente.mensaje(nombrePersona, msg);

            std::cout << json << std::endl;

            cliente.enviarInformacion(json);

        }else if(opcion == 2){

            std::string msg;

            std::cin.ignore();

            std::cout << "Mensaje: ";
            std::getline(std::cin, msg);

            std::string json = cliente.mensajeTodos(msg);

            std::cout << json << std::endl;

            cliente.enviarInformacion(json);

        }else if(opcion == 3){

            std::string nombreSala;

            std::cout << "Nombre del cuarto: ";
            std::cin.ignore();
            std::getline(std::cin, nombreSala);

            std::string json = cliente.crearCuarto(nombreSala);

            std::cout << json << std::endl;

            cliente.enviarInformacion(json);

        }else if(opcion == 4){

            std::string nombrePersona;
            std::string nombreSala;

            std::cout << "Nombre del usuario: ";
            std::cin >> nombrePersona;

            std::cout << "Nombre del cuarto: ";
            std::cin >> nombreSala;

            std::string json =
                cliente.invitarCuartoUno(nombrePersona, nombreSala);

            std::cout << json << std::endl;

            cliente.enviarInformacion(json);

        }else if(opcion == 5){

            std::string nombreSala;

            std::cout << "Nombre del cuarto: ";
            std::cin >> nombreSala;

            std::string json =
                cliente.entrarCuarto(nombreSala);

            std::cout << json << std::endl;

            cliente.enviarInformacion(json);

        }else if(opcion == 6){

            std::string nombreSala;

            std::cout << "Nombre del cuarto: ";
            std::cin >> nombreSala;

            std::string json =
                cliente.roomUsers(nombreSala);

            std::cout << json << std::endl;

            cliente.enviarInformacion(json);

        }else if(opcion == 7){

            std::string nombreSala;
            std::string msg;

            std::cout << "Nombre del cuarto: ";
            std::cin >> nombreSala;

            std::cin.ignore();

            std::cout << "Mensaje: ";
            std::getline(std::cin, msg);

            std::string json =
                cliente.mensajeCuarto(msg, nombreSala);

            std::cout << json << std::endl;

            cliente.enviarInformacion(json);

        }else if(opcion == 8){

            std::string nombreSala;

            std::cout << "Nombre del cuarto: ";
            std::cin >> nombreSala;

            std::string json =
                cliente.salirCuarto(nombreSala);

            std::cout << json << std::endl;

            cliente.enviarInformacion(json);

        }else if(opcion == 9){

            std::string estatus;

            std::cout << "Nuevo estatus (ACTIVE/AWAY/BUSY): ";
            std::cin >> estatus;

            std::string json =
                cliente.nuevoEstatus(estatus);

            std::cout << json << std::endl;

            cliente.enviarInformacion(json);

        }else if(opcion == 10){

            std::cout << "Desconectando..." << std::endl;

            cliente.desconectar();

        }else{

            std::cout << "Opcion no valida." << std::endl;
        }
    }

    return 0;
}
