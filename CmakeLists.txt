cmake_minimum_required(VERSION 3.29)

project(Servicio_Mensajeria
        VERSION 1.0
        LANGUAGES CXX
      )

find_package(Doxygen REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest)

include_directories(include)

add_library(Servicio_Mensajeria
             ./src/Cliente.cpp
             ./src/Cuarto.cpp
             ./src/Servidor.cpp
             ./src/tipoEstatus.cpp
           )

target_include_directories(Servicio_Mensajeria PUBLIC include)

target_compile_features(Servicio_Mensajeria
                        PUBLIC
                        cxx_std_20
                       )

target_compile_options(Servicio_Mensajeria
                       PUBLIC
                       -Wall -Wextra
                       )


add_executable(ServicioMensajeriaTest
              ./test/ClienteTest.cpp
              ./test/ServidorTest.cpp
              ./test/CuartoTest.cpp
              )


add_executable(ServicioMensajeriaApp
              ./src/main.cpp
             )



target_link_libraries(ServicioMensajeriaTest
    Servicio_Mensajeria
    GTest::gtest
    GTest::gtest_main
)


target_link_libraries(ServicioMensajeriaApp
         Servicio_Mensajeria
         )

enable_testing()

add_test(NAME Servicio_MensajeriaTEST COMMAND ServicioMensajeriaTest)

if(DOXYGEN_FOUND)
add_custom_target(doc 
  COMMAND ${DOXYGEN_EXECUTABLE}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Generando documentación con doxigen. "
  )

endif()
