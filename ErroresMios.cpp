#include "ErroresMios.h"

namespace errores {

    std::runtime_error archivo(const std::string& detalle) {
        return std::runtime_error("Error de archivo: " + detalle);
    }

    std::runtime_error partidaNoEncontrada(const std::string& detalle) {
        return std::runtime_error("Partida no encontrada: " + detalle);
    }

    std::out_of_range indiceInvalido(const std::string& detalle) {
        return std::out_of_range("Indice invalido: " + detalle);
    }

    std::invalid_argument itemNoEncontrado(const std::string& detalle) {
        return std::invalid_argument("Item no encontrado: " + detalle);
    }

}
