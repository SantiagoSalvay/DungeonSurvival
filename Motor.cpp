#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>
#include "Menu.h"
#include "structs.h"
#include "EstadoJuego.h"
#include "Renderizado.h"
#include "Batalla.h"
#include "Entrada.h"

int iniciarjuego() {
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Dungeon Survival");
    window.setFramerateLimit(60);

    RecursosVisuales recursos;
    cargarRecursosVisuales(recursos, window);

    estado_pantalla estado_actual = menu_principal;

    string matriz_fondo[max_filas][max_columnas];
    string matriz_entidades[max_filas][max_columnas];
    cargarnivel(1, matriz_fondo, matriz_entidades);

    EstadoBatalla batalla;

    personaje paolo;
    protagonista(paolo);

    mercader vendedor;
    inicializarmercader(vendedor);
    ordenarmercader(vendedor.catalogo, vendedor.precios, 6);

    EstadoUI ui;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* text_event = event->getIf<sf::Event::TextEntered>()) {
                // Capturamos los caracteres tipeados cuando estamos pidiendo el nombre del personaje
                if (estado_actual == pedir_nombre) {
                    manejarTextoNombre(ui.nombre_input, text_event->unicode);
                }
            }
            else if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {

                if (estado_actual == menu_principal) {
                    manejarTeclaMenuPrincipal(ui, recursos, window, estado_actual, key_pressed->code);
                }
                else if (estado_actual == pedir_nombre) {
                    manejarTeclaPedirNombre(ui, paolo, matriz_fondo, matriz_entidades, estado_actual, key_pressed->code);
                }
                else if (estado_actual == intro_historia) {
                    manejarTeclaIntro(estado_actual, key_pressed->code);
                }
                else if (estado_actual == aviso_guardado) {
                    manejarTeclaAvisoGuardado(ui, estado_actual, key_pressed->code);
                }
                else if (estado_actual == reglas || estado_actual == controles || estado_actual == creditos) {
                    manejarTeclaReglasControlesCreditos(ui, estado_actual, key_pressed->code);
                }
                else if (estado_actual == cargar) {
                    manejarTeclaCargar(ui, paolo, matriz_fondo, matriz_entidades, estado_actual, key_pressed->code);
                }
                else if (estado_actual == confirmar_guardado) {
                    if (manejarTeclaConfirmarGuardado(ui, recursos, paolo, matriz_entidades, estado_actual, key_pressed->code)) {
                        break;
                    }
                }
                else if (estado_actual == jugando) {
                    manejarTeclaJugando(ui, batalla, recursos, paolo, matriz_fondo, matriz_entidades, estado_actual, key_pressed->code);
                }
                else if (estado_actual == en_inventario) {
                    manejarTeclaInventario(ui, paolo, estado_actual, key_pressed->code);
                }
                else if (estado_actual == en_tienda) {
                    manejarTeclaTienda(ui, paolo, vendedor, estado_actual, key_pressed->code);
                }
                else if (estado_actual == en_batalla) {
                    manejarEntradaBatalla(batalla, paolo, matriz_fondo, matriz_entidades, estado_actual, key_pressed->code);
                }
            }
        }

        // --- ACTUALIZACION DEL TURNO Y ANIMACIONES DE BATALLA ---
        if (estado_actual == en_batalla) {
            actualizarTurnoBatalla(batalla, paolo, matriz_entidades);
        }

        window.clear();

        if (estado_actual == en_batalla) {
            dibujarBatalla(window, recursos, batalla, paolo);
            window.display();
            continue;
        }

        dibujarFondoMenu(window, recursos);

        if (estado_actual == menu_principal) {
            dibujarMenuPrincipal(window, recursos);
        }
        else if (estado_actual == pedir_nombre) {
            dibujarPedirNombre(window, recursos, ui);
        }
        else if (estado_actual == intro_historia) {
            dibujarIntroHistoria(window, recursos, ui);
            window.display();
            continue;
        }
        else {
            if (estado_actual == jugando || estado_actual == en_tienda || estado_actual == en_inventario) {
                dibujarMapaConCamara(window, matriz_fondo, matriz_entidades, recursos);
            }

            if (estado_actual != jugando) {
                window.draw(recursos.panel_oscuro);
            }

            if (estado_actual == reglas) {
                window.draw(recursos.texto_reglas);
            }
            else if (estado_actual == controles) {
                window.draw(recursos.texto_controles);
            }
            else if (estado_actual == creditos) {
                window.draw(recursos.texto_creditos);
            }
            else if (estado_actual == jugando) {
                dibujarPantallaJuego(window, recursos, ui);
            }
            else if (estado_actual == cargar) {
                dibujarCargarPartida(window, recursos, ui);
            }
            else if (estado_actual == confirmar_guardado) {
                dibujarConfirmarGuardado(window, recursos);
            }
            else if (estado_actual == aviso_guardado) {
                dibujarAvisoGuardado(window, recursos);
            }
            else if (estado_actual == en_inventario) {
                dibujarInventario(window, recursos, paolo, ui);
            }
            else if (estado_actual == en_tienda) {
                dibujarTienda(window, recursos, paolo, vendedor, ui);
            }
        }

        window.display();
    }

    return 0;
}
