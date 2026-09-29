#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "Cliente.hpp"
#include "Cuarto.hpp"
#include "Servidor.hpp"

Servidor* servidorPruebaUnitaria = nullptr;


// Caso NombreCuarto
/**
* @brief Prueba obtener el nombre del cuarto.
* @note Verifica que el nombre sea el correcto.
*/
TEST(ServicioMensajeriaTest, CasoNombreCuarto) {

    Cuarto cuarto_uno("Sala 1");

    EXPECT_EQ(cuarto_uno.getNombre(), "Sala 1");
}


// Caso AgregarInvitado
/**
* @brief Prueba agregar un invitado al cuarto.
* @note Verifica que el usuario haya sido invitado.
*/
TEST(ServicioMensajeriaTest, CasoAgregarInvitado) {

    Cuarto cuarto_uno("Sala 1");
    Cliente cliente_uno("Aidee", servidorPruebaUnitaria);

    cuarto_uno.agregarInvitado(cliente_uno);

    EXPECT_TRUE(cuarto_uno.fueInvitado(cliente_uno));
}


// Caso NoFueInvitado
/**
* @brief Prueba verificar que una persona no haya sido invitada.
* @note Verifica que el resultado sea falso.
*/
TEST(ServicioMensajeriaTest, CasoNoFueInvitado) {

    Cuarto cuarto_uno("Sala 1");
    Cliente cliente_uno("Aidee", servidorPruebaUnitaria);

    EXPECT_FALSE(cuarto_uno.fueInvitado(cliente_uno));
}


// Caso AgregarPersona
/**
* @brief Prueba agregar una persona al cuarto.
* @note Verifica que la persona este dentro del cuarto.
*/
TEST(ServicioMensajeriaTest, CasoAgregarPersona) {

    Cuarto cuarto_uno("Sala 1");
    Cliente cliente_uno("Aidee", servidorPruebaUnitaria);

    cuarto_uno.agregarPersona(cliente_uno);

    EXPECT_TRUE(cuarto_uno.saberPersonaEsta("Aidee"));
}


// Caso SacarPersona
/**
* @brief Prueba sacar una persona del cuarto.
* @note Verifica que la persona ya no este dentro del cuarto.
*/
TEST(ServicioMensajeriaTest, CasoSacarPersona) {

    Cuarto cuarto_uno("Sala 1");
    Cliente cliente_uno("Aidee", servidorPruebaUnitaria);

    cuarto_uno.agregarPersona(cliente_uno);

    EXPECT_TRUE(cuarto_uno.sacarPersona(cliente_uno));
    EXPECT_FALSE(cuarto_uno.saberPersonaEsta("Aidee"));
}


// Caso CompararCuartos
/**
* @brief Prueba el operador == de Cuarto.
* @note Verifica que dos cuartos con el mismo nombre sean iguales.
*/
TEST(ServicioMensajeriaTest, CasoCompararCuartos) {

    Cuarto cuarto_uno("Sala 1");
    Cuarto cuarto_dos("Sala 1");

    EXPECT_TRUE(cuarto_uno == cuarto_dos);
}


// Caso CompararCuartosDiferentes
/**
* @brief Prueba comparar dos cuartos diferentes.
* @note Verifica que no sean iguales.
*/
TEST(ServicioMensajeriaTest, CasoCompararCuartosDiferentes) {

    Cuarto cuarto_uno("Sala 1");
    Cuarto cuarto_dos("Sala 2");

    EXPECT_FALSE(cuarto_uno == cuarto_dos);
}
