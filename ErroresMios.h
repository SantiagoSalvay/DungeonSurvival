#pragma once
#include <exception>
#include <string>

// ERRORES PROPIOS DEL JUEGO
// Todas las excepciones del juego heredan de ErrorDungeon, que a su vez hereda de
// std::exception. Asi se puede atrapar cualquiera con un solo catch (const ErrorDungeon&)
// o atrapar una en particular. what() devuelve el mensaje que se paso al lanzarla.
class ErrorDungeon : public std::exception {
public:
	explicit ErrorDungeon(const std::string& mensaje) : mensaje(mensaje) {}
	const char* what() const noexcept override { return mensaje.c_str(); }
private:
	std::string mensaje;
};

// No se pudo abrir o escribir un archivo (por ejemplo partidas.txt)
class ErrorArchivo : public ErrorDungeon {
public:
	explicit ErrorArchivo(const std::string& mensaje) : ErrorDungeon(mensaje) {}
};

// No hay ninguna partida guardada, o no existe una con el nombre pedido
class ErrorPartidaNoEncontrada : public ErrorDungeon {
public:
	explicit ErrorPartidaNoEncontrada(const std::string& mensaje) : ErrorDungeon(mensaje) {}
};

// Se pidio una partida con un indice fuera de rango
class ErrorIndiceInvalido : public ErrorDungeon {
public:
	explicit ErrorIndiceInvalido(const std::string& mensaje) : ErrorDungeon(mensaje) {}
};

// La busqueda binaria no encontro el item o la clave pedida
class ErrorItemNoEncontrado : public ErrorDungeon {
public:
	explicit ErrorItemNoEncontrado(const std::string& mensaje) : ErrorDungeon(mensaje) {}
};
