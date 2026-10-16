#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "structs.h"
#include "mapa.h"
#include "funciones.h"
#include "EstadoJuego.h"

// Fuente, texturas y elementos visuales que se cargan/arman una sola vez al arrancar el juego.
struct RecursosVisuales {
    sf::Font alagard;

    sf::Texture textura_fondo;
    sf::Texture tex_suelo, tex_pared_arriba, tex_pared_abajo, tex_pared_izq, tex_pared_der;
    sf::Texture tex_prota, tex_boss, tex_enemigo, tex_mercader, tex_cofre, tex_salida;
    sf::Texture tex_fondo_pelea;

    sf::Text texto_titulo{ alagard };
    std::vector<sf::Text> opciones_menu;

    sf::RectangleShape panel_menu;
    sf::RectangleShape panel_oscuro;

    sf::Text texto_reglas{ alagard };
    sf::Text texto_controles{ alagard };
    sf::Text texto_creditos{ alagard };

    sf::RectangleShape fondo_pausa;
    sf::Text texto_pausa_titulo{ alagard };
    std::vector<sf::Text> opciones_pausa;

    sf::RectangleShape fondo_confirmacion;
    sf::Text texto_confirmacion_titulo{ alagard };
    std::vector<sf::Text> opciones_confirmacion;

    sf::RectangleShape fondo_aviso_guardado;
    sf::RectangleShape linea_deco_guardado;
    sf::Text texto_guardado_titulo{ alagard };
    sf::Text texto_guardado_subtitulo{ alagard };
};

// Carga fuente/texturas y arma los textos/paneles estaticos. Se llama una sola vez al iniciar.
void cargarRecursosVisuales(RecursosVisuales& recursos, sf::RenderWindow& window);

void dibujarFondoMenu(sf::RenderWindow& window, const RecursosVisuales& recursos);
void dibujarMenuPrincipal(sf::RenderWindow& window, const RecursosVisuales& recursos);
void dibujarPedirNombre(sf::RenderWindow& window, const RecursosVisuales& recursos, const EstadoUI& ui);
void dibujarIntroHistoria(sf::RenderWindow& window, const RecursosVisuales& recursos, const EstadoUI& ui);

void dibujarMapaConCamara(
    sf::RenderWindow& window,
    string matriz_fondo[max_filas][max_columnas],
    string matriz_entidades[max_filas][max_columnas],
    RecursosVisuales& recursos
);

void dibujarPantallaJuego(sf::RenderWindow& window, const RecursosVisuales& recursos, const EstadoUI& ui);
void dibujarCargarPartida(sf::RenderWindow& window, const RecursosVisuales& recursos, EstadoUI& ui);
void dibujarConfirmarGuardado(sf::RenderWindow& window, const RecursosVisuales& recursos);
void dibujarAvisoGuardado(sf::RenderWindow& window, const RecursosVisuales& recursos);
void dibujarInventario(sf::RenderWindow& window, const RecursosVisuales& recursos, const personaje& paolo, EstadoUI& ui);
void dibujarTienda(sf::RenderWindow& window, const RecursosVisuales& recursos, const personaje& paolo, const mercader& vendedor, const EstadoUI& ui);
// Nota: tambien avanza la cinematica inicial del boss cuando termina su tiempo (igual que el codigo original).
void dibujarBatalla(sf::RenderWindow& window, const RecursosVisuales& recursos, EstadoBatalla& batalla, const personaje& paolo);
