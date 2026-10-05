#pragma once
#include "structs.h"
#include "mapa.h"
#include "funciones.h"

// Modulo que agrupa las cinco responsabilidades minimas del juego:
//   1) Datos del juego
//   2) Inicializacion de las entidades
//   3) Mapas y dibujo
//   4) Movimiento e interaccion
//   5) Guardado y carga de partidas
//
// Cada responsabilidad se expone como su propia funcion. El modulo no
// reimplementa logica: organiza y reexpone lo que ya vive en structs.h,
// entidades.cpp, mapa.h/mapaf.cpp y funciones.cpp, para que se pueda
// usar como una unica unidad desde Motor.cpp.

// --- Responsabilidad 1: Datos del juego ---
// Los tipos personaje, enemigo, mercader y cofre vienen de structs.h.
// Esta funcion arma un personaje "en blanco" listo para inicializar.
personaje crearPersonajeVacio();

// --- Responsabilidad 2: Inicializacion de las entidades ---
// Carga los valores iniciales del protagonista, el mercader y un enemigo
// (comun o jefe, segun es_boss).
void inicializarEntidadesNivel(personaje& pj, mercader& vendedor, enemigo& en, bool es_boss);

// --- Responsabilidad 3: Mapas y dibujo ---
// Arma las matrices del nivel pedido y las dibuja en la ventana con SFML.
void cargarYDibujarNivel(
	int numero_nivel,
	string matriz_fondo[max_filas][max_columnas],
	string matriz_entidades[max_filas][max_columnas],
	sf::RenderWindow& ventana,
	sf::Texture& tex_suelo,
	sf::Texture& tex_pared_arriba, sf::Texture& tex_pared_abajo,
	sf::Texture& tex_pared_izq, sf::Texture& tex_pared_der,
	sf::Texture& tex_prota, sf::Texture& tex_boss, sf::Texture& tex_enemigo,
	sf::Texture& tex_mercader, sf::Texture& tex_cofre, sf::Texture& tex_salida
);

// --- Responsabilidad 4: Movimiento e interaccion ---
// Mueve al personaje en la direccion indicada y resuelve la interaccion
// con lo que haya en la casilla de destino (cofre, mercader, enemigo, salida).
char procesarTurno(
	personaje& pj, char direccion,
	string matriz_fondo[max_filas][max_columnas],
	string matriz_entidades[max_filas][max_columnas],
	cofre& cofre_resultado
);

// --- Responsabilidad 5: Guardado y carga de partidas ---
// Persisten y recuperan el estado del personaje y del mapa en partidas.txt.
void guardarProgreso(const personaje& pj, string matriz_entidades[max_filas][max_columnas]);
bool cargarProgreso(personaje& pj, string matriz_entidades[max_filas][max_columnas]);
