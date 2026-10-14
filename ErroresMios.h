#pragma once
#include <string>
#include <exception>

class ErrorDungeon : public std::exception {
public:
	explicit ErrorDungeon(const std::string& mensaje) : mensaje(mensaje) {}
	const char* what() const noexcept override { return mensaje.c_str(); }
private:
	std::string mensaje;
};

class ErrorArchivo : public ErrorDungeon {
public:
	explicit ErrorArchivo(const std::string& mensaje) : ErrorDungeon(mensaje) {}
};

class ErrorPartidaNoEncontrada : public ErrorDungeon {
public:
	explicit ErrorPartidaNoEncontrada(const std::string& mensaje) : ErrorDungeon(mensaje) {}
};

class ErrorIndiceInvalido : public ErrorDungeon {
public:
	explicit ErrorIndiceInvalido(const std::string& mensaje) : ErrorDungeon(mensaje) {}
};

class ErrorItemNoEncontrado : public ErrorDungeon {
public:
	explicit ErrorItemNoEncontrado(const std::string& mensaje) : ErrorDungeon(mensaje) {}
};
