#pragma once
#include <stdexcept>
#include <string>

// ERRORES PROPIOS DEL JUEGO
// Cada funcion arma una excepcion estandar con un mensaje claro.
// Se usan asi:  throw errores::archivo("no se pudo abrir partidas.txt");
namespace errores {

    // No se pudo abrir o escribir un archivo (por ejemplo partidas.txt)
    std::runtime_error archivo(const std::string& detalle);

    // No hay ninguna partida guardada, o no existe una con el nombre pedido
    std::runtime_error partidaNoEncontrada(const std::string& detalle);

    // Se pidio una partida con un indice fuera de rango
    std::out_of_range indiceInvalido(const std::string& detalle);

    // La busqueda binaria no encontro el item o la clave pedida
    std::invalid_argument itemNoEncontrado(const std::string& detalle);

}
