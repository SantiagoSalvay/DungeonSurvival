#pragma once
#include "structs.h"
#include "mapa.h"
#include <fstream>
#include <sstream>
#include <vector>

void protagonista(personaje& pj);
void inicializarmercader(mercader& vendedor);
void inicializarenemigo(enemigo& en, bool es_boss);

void moverpj(personaje& pj, char direccion, string matriz_fondo[max_filas][max_columnas], string matriz_entidades[max_filas][max_columnas]);
char interactuar(personaje& pj, string matriz_entidades[max_filas][max_columnas], string matriz_fondo[max_filas][max_columnas], cofre& cofre_resultado);

std::string formatearFecha(long long timestamp);

void completar(string v[], int tam, int pos, string c[], int& k);
int fusionar(string a[], int n, string b[], int m, string c[]);
int obtenerprecioventa(string nombre_item);
int buscaritem(string v[50], int n, string x);
void ordenarburbuja(string v[50], int n);
void ordenarmercader(string catalogo[6], int precios[6], int n);

int obtenerataque(string arma_nombre);
int obtenerdefensa(string armadura_nombre);

struct registro_partida {
	personaje pj;
	string entidades[max_filas][max_columnas];
	long long ultimo_guardado = 0;
};

std::vector<registro_partida> obtenerPartidas();
void guardarPartida(const personaje& pj, string matriz_entidades[max_filas][max_columnas]);
bool cargarPartida(personaje& pj, string matriz_entidades[max_filas][max_columnas]);
bool cargarPartidaPorIndice(personaje& pj, int indice, string matriz_entidades[max_filas][max_columnas]);
bool cargarPartidaPorIndice(personaje& pj, int indice);
bool eliminarPartidaPorIndice(int indice);
bool eliminarPartidaPorNombre(const std::string& nombre);
