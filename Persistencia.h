#pragma once
#include "structs.h"
#include "mapa.h"
#include <string>
#include <vector>

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
