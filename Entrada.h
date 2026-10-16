#pragma once
#include <cstdint>
#include <SFML/Window.hpp>
#include "structs.h"
#include "mapa.h"
#include "funciones.h"
#include "EstadoJuego.h"
#include "Renderizado.h"

// Captura de texto mientras se esta escribiendo el nombre del personaje (pantalla pedir_nombre).
void manejarTextoNombre(std::string& nombre_input, std::uint32_t code);

void manejarTeclaMenuPrincipal(
    EstadoUI& ui,
    RecursosVisuales& recursos,
    sf::RenderWindow& window,
    estado_pantalla& estado_actual,
    sf::Keyboard::Key tecla
);

void manejarTeclaPedirNombre(
    EstadoUI& ui,
    personaje& paolo,
    string matriz_fondo[max_filas][max_columnas],
    string matriz_entidades[max_filas][max_columnas],
    estado_pantalla& estado_actual,
    sf::Keyboard::Key tecla
);

void manejarTeclaIntro(estado_pantalla& estado_actual, sf::Keyboard::Key tecla);

void manejarTeclaReglasControlesCreditos(EstadoUI& ui, estado_pantalla& estado_actual, sf::Keyboard::Key tecla);

// Cubre tanto la pantalla "sin partidas guardadas" como la navegacion normal de la lista.
void manejarTeclaCargar(
    EstadoUI& ui,
    personaje& paolo,
    string matriz_fondo[max_filas][max_columnas],
    string matriz_entidades[max_filas][max_columnas],
    estado_pantalla& estado_actual,
    sf::Keyboard::Key tecla
);

// Devuelve true si, igual que el codigo original, hay que dejar de procesar mas eventos
// encolados en este mismo frame (ocurre justo al confirmar el guardado).
bool manejarTeclaConfirmarGuardado(
    EstadoUI& ui,
    RecursosVisuales& recursos,
    const personaje& paolo,
    string matriz_entidades[max_filas][max_columnas],
    estado_pantalla& estado_actual,
    sf::Keyboard::Key tecla
);

void manejarTeclaAvisoGuardado(EstadoUI& ui, estado_pantalla& estado_actual, sf::Keyboard::Key tecla);

// Cubre tanto la pausa como la exploracion normal (movimiento, interaccion, disparo de batalla).
void manejarTeclaJugando(
    EstadoUI& ui,
    EstadoBatalla& batalla,
    RecursosVisuales& recursos,
    personaje& paolo,
    string matriz_fondo[max_filas][max_columnas],
    string matriz_entidades[max_filas][max_columnas],
    estado_pantalla& estado_actual,
    sf::Keyboard::Key tecla
);

void manejarTeclaInventario(EstadoUI& ui, personaje& paolo, estado_pantalla& estado_actual, sf::Keyboard::Key tecla);

void manejarTeclaTienda(EstadoUI& ui, personaje& paolo, const mercader& vendedor, estado_pantalla& estado_actual, sf::Keyboard::Key tecla);
