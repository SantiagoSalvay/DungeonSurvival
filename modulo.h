#pragma once
#include "structs.h"
#include "mapa.h"
#include "funciones.h"


// --- Responsabilidad 1: Datos del juego ---

personaje crearPersonajeVacio();

// --- Responsabilidad 2: Inicializacion de las entidades ---

void inicializarEntidadesNivel(personaje& pj, mercader& vendedor, enemigo& en, bool es_boss);

// --- Responsabilidad 3: Mapas y dibujo ---
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

char procesarTurno(
	personaje& pj, char direccion,
	string matriz_fondo[max_filas][max_columnas],
	string matriz_entidades[max_filas][max_columnas],
	cofre& cofre_resultado
);

// --- Responsabilidad 5: Guardado y carga de partidas ---
void guardarProgreso(const personaje& pj, string matriz_entidades[max_filas][max_columnas]);
bool cargarProgreso(personaje& pj, string matriz_entidades[max_filas][max_columnas]);
