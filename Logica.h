#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <SFML/Window.hpp>
#include "Datos.h"
#include "Persistencia.h"
#include "Gestion.h"

// REGLAS DEL JUEGO
void protagonista(personaje& pj);
void inicializarmercader(mercader& vendedor);
void inicializarenemigo(enemigo& en, bool es_boss);

void moverpj(personaje& pj, char direccion, string matriz_fondo[max_filas][max_columnas], string matriz_entidades[max_filas][max_columnas]);
char interactuar(personaje& pj, string matriz_entidades[max_filas][max_columnas], string matriz_fondo[max_filas][max_columnas], cofre& cofre_resultado);


void completar(string v[], int tam, int pos, string c[], int& k);
int fusionar(string a[], int n, string b[], int m, string c[]);
int obtenerprecioventa(string nombre_item);
int buscaritem(string v[50], int n, string x);

int obtenerataque(string arma_nombre);
int obtenerdefensa(string armadura_nombre);

// BATALLA POR TURNOS
// Prepara el EstadoBatalla para enfrentar al enemigo ubicado en (pos_x, pos_y) del mapa.
void iniciarBatalla(EstadoBatalla& batalla, int pos_x, int pos_y, bool es_boss);

// Decide si el enemigo hace su ataque normal o (solo el boss, tras regenerarse) un golpe devastador.
void iniciarTurnoEnemigo(EstadoBatalla& batalla);

// Avanza el turno segun la fase actual: aplica dano, decide transiciones de fase y fin de combate.
void actualizarTurnoBatalla(
    EstadoBatalla& batalla,
    personaje& paolo,
    string matriz_entidades[max_filas][max_columnas]
);

// Maneja una tecla presionada mientras estado_actual == en_batalla.
void manejarEntradaBatalla(
    EstadoBatalla& batalla,
    personaje& paolo,
    string matriz_fondo[max_filas][max_columnas],
    string matriz_entidades[max_filas][max_columnas],
    estado_pantalla& estado_actual,
    sf::Keyboard::Key tecla
);

// ORQUESTACION DE TURNOS
// --- Responsabilidad 1: Datos del juego ---

personaje crearPersonajeVacio();

// --- Responsabilidad 2: Inicializacion de las entidades ---

void inicializarEntidadesNivel(personaje& pj, mercader& vendedor, enemigo& en, bool es_boss);

// --- Responsabilidad 4: Movimiento e interaccion ---

char procesarTurno(
	personaje& pj, char direccion,
	string matriz_fondo[max_filas][max_columnas],
	string matriz_entidades[max_filas][max_columnas],
	cofre& cofre_resultado
);

// --- Responsabilidad 5: Guardado y carga de partidas ---
void guardarProgreso(const personaje& pj, string matriz_entidades[max_filas][max_columnas]);
bool cargarProgreso(personaje& pj, string matriz_entidades[max_filas][max_columnas]);
