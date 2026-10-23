#pragma once
#include <string>
#include <vector>
#include "Datos.h"
#include "ErroresMios.h"

// PERSISTENCIA: guardado y carga de partidas en partidas.txt
// (registro_partida, el registro de una partida, esta declarado en Datos.h)

// Version simple: devuelve true/false segun salio bien
std::vector<registro_partida> obtenerPartidas();
void guardarPartida(const personaje& pj, string matriz_entidades[max_filas][max_columnas]);
bool cargarPartida(personaje& pj, string matriz_entidades[max_filas][max_columnas]);
bool cargarPartidaPorIndice(personaje& pj, int indice, string matriz_entidades[max_filas][max_columnas]);
bool cargarPartidaPorIndice(personaje& pj, int indice);
bool eliminarPartidaPorIndice(int indice);
bool eliminarPartidaPorNombre(const std::string& nombre);

// Convierte un timestamp en texto "dd/mm/aaaa hh:mm"
std::string formatearFecha(long long timestamp);

// Version alternativa: en vez de devolver false, lanza excepciones de ErroresMios.h
namespace persistencia {

struct partidaGuardada {
	personaje pj;
	string entidades[max_filas][max_columnas];
	long long ultimo_guardado = 0;
};

std::vector<partidaGuardada> listarPartidas();
void guardarPartidaPersistente(const personaje& pj, string entidades[max_filas][max_columnas]);
void cargarUltimaPartida(personaje& pj, string entidades[max_filas][max_columnas]);
void cargarPartidaPorIndice(personaje& pj, int indice, string entidades[max_filas][max_columnas]);
void eliminarPartidaPorNombre(string nombre);

}
