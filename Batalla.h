#pragma once
#include <SFML/Window.hpp>
#include "structs.h"
#include "mapa.h"
#include "funciones.h"
#include "EstadoJuego.h"

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
