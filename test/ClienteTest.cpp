#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "Cliente.hpp"
#include "Cuarto.hpp"
#include "Servidor.hpp"

Servidor servidorPruebaUnitaria("ServidorPrueba");

// Caso Mensaje
/**
* @brief Prueba metodo mensaje:
* @note Verifica que el string sea el correcto.
 */
TEST(ServicioMensajeriaTest, CasoMensaje) {

    Cliente cliente_uno("Aidee", servidorPruebaUnitaria);
    std::string msg = "Hola como estas Danielcin.";
    std::string persona = "Danielcin";

    std::string esperadoUno =
        "{ \"type\": \"TEXT\", "
        "\"username\": \"Danielcin\", "
        "\"text\": \"Hola como estas Danielcin.\" }\n";

    EXPECT_EQ(cliente_uno.mensaje(persona, msg), esperadoUno);
}


// Caso MensajeTodos
/**
* @brief Prueba metodo mensaje para todos:
* @note Verifica que el string sea el correcto.
 */
TEST(ServicioMensajeriaTest, CasoMensajeTodos) {

    Cliente cliente_uno("Aidee", servidorPruebaUnitaria);
    std::string msg = "Hola a todos.";

    std::string esperadoDos =
        "{ \"type\": \"PUBLIC_TEXT\", "
        "\"text\": \"Hola a todos.\" }\n";

    EXPECT_EQ(cliente_uno.mensajeTodos(msg), esperadoDos);
}


// Caso crearCuarto
/**
* @brief Prueba metodo crear cuarto
* @note Verifica que el string sea el correcto.
*/
TEST(ServicioMensajeriaTest, casoCrearCuarto) {

    Cliente cliente_uno("Aidee", servidorPruebaUnitaria);
    std::string nombreSala = "Modelado y Programación.";

    std::string esperadoTres =
        "{ \"type\": \"NEW_ROOM\", "
        "\"roomname\": \"Modelado y Programación.\" }\n";

    EXPECT_EQ(cliente_uno.crearCuarto(nombreSala), esperadoTres);
}


// Caso invitar a uno al Cuarto
/**
* @brief Prueba para invitar a uno a la sala.
* @note Verifica que el string sea el correcto.
*/
TEST(ServicioMensajeriaTest, casoInvitarUnoCuarto) {

    Cliente cliente_uno("Aidee", servidorPruebaUnitaria);
    std::string nombreSala = "Modelado y Programación.";
    std::string nombre = "Aidee";

    std::string esperadoCuatro =
        "{ \"type\": \"INVITE\", "
        "\"roomname\": \"Modelado y Programación.\", "
        "\"usernames\": [\"Aidee\"] }\n";

    EXPECT_EQ(cliente_uno.invitarCuartoUno(nombre, nombreSala), esperadoCuatro);
}


// Caso invitar a varios al Cuarto
/**
* @brief Prueba para invitar a varios a la sala.
* @note Verifica que el string sea el correcto.
*/
TEST(ServicioMensajeriaTest, casoInvitarVariosCuarto) {

    Cliente cliente_uno("Aidee", servidorPruebaUnitaria);
    std::string nombreSala = "Modelado y Programación.";
    std::vector<std::string> nombres = {"Aidee", "Santana", "Abeja"};

    std::string esperadoCinco =
        "{ \"type\": \"INVITE\", "
        "\"roomname\": \"Modelado y Programación.\", "
        "\"usernames\": [\"Aidee\", \"Santana\", \"Abeja\"] }\n";

    EXPECT_EQ(cliente_uno.invitarCuartoVarios(nombres, nombreSala), esperadoCinco);
}


// Caso entrar al cuarto
/**
* @brief Prueba para entrar al cuarto
* @note Verifica que el string sea el correcto.
*/
TEST(ServicioMensajeriaTest, casoEntrarCuarto) {

    Cliente cliente_uno("Aidee", servidorPruebaUnitaria);
    std::string nombreSala = "Modelado y Programación.";

    std::string esperadoSeis =
        "{ \"type\": \"JOIN_ROOM\", "
        "\"roomname\": \"Modelado y Programación.\" }\n";

    EXPECT_EQ(cliente_uno.entrarCuarto(nombreSala), esperadoSeis);
}


// Caso listar usuarios
/**
* @brief Prueba enviar string para listar usuarios
* @note Verifica que el string sea el correcto.
*/
TEST(ServicioMensajeriaTest, casoRoomUsers) {

    Cliente cliente_uno("Aidee", servidorPruebaUnitaria);
    std::string nombreSala = "Modelado y Programación.";

    std::string esperadoSiete =
        "{ \"type\": \"ROOM_USERS\", "
        "\"roomname\": \"Modelado y Programación.\" }\n";

    EXPECT_EQ(cliente_uno.roomUsers(nombreSala), esperadoSiete);
}


// Caso MensajeCuarto
/**
* @brief Prueba enviar mensaje a un cuarto en especifico.
* @note Verifica que el string sea el correcto.
*/
TEST(ServicioMensajeriaTest, casoMensajeCuarto) {

    Cliente cliente_uno("Aidee", servidorPruebaUnitaria);
    std::string msg = "Hola personas de esta sala. ";
    std::string nombreSala = "Modelado y Programación.";

    std::string esperadoOcho =
        "{ \"type\": \"ROOM_TEXT\", "
        "\"roomname\": \"Modelado y Programación.\", "
        "\"text\": \"Hola personas de esta sala. \" }\n";

    EXPECT_EQ(cliente_uno.mensajeCuarto(msg, nombreSala), esperadoOcho);
}


// Caso salirCuarto
/**
* @brief Prueba salir del cuarto
* @note Verifica que el string sea el correcto.
*/
TEST(ServicioMensajeriaTest, casoSalirCuarto) {

    Cliente cliente_uno("Aidee", servidorPruebaUnitaria);

    std::string nombreSala = "Modelado y Programación.";

    std::string esperadoNueve =
        "{ \"type\": \"LEAVE_ROOM\", "
        "\"roomname\": \"Modelado y Programación.\" }\n";

    EXPECT_EQ(cliente_uno.salirCuarto(nombreSala), esperadoNueve);
}


// Caso desconectar
/**
* @brief Prueba salir del servidor
* @note Verifica que el string sea el correcto.
*/
TEST(ServicioMensajeriaTest, casoDesconectar) {

    Cliente cliente_uno("Aidee", servidorPruebaUnitaria);

    std::string esperadoDiez =
        "{ \"type\": \"DISCONNECT\" }\n";

    EXPECT_EQ(cliente_uno.desconectar(), esperadoDiez);
}
