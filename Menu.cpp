#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <optional>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include "Menu.h"
#include "Mapa.h"
#include "funciones.h"
#include "structs.h"

enum estado_pantalla { menu_principal, jugando, cargar, controles, reglas, creditos, en_tienda, en_batalla, en_inventario, confirmar_guardado, aviso_guardado };

enum class fase_batalla { cinematica_boss, espera_input, anim_pj_ataca, anim_enemigo_ataca, anim_pocion, ganada, victoria_final, perdida, huida };

int iniciarjuego() {
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Dungeon Survival");
    window.setFramerateLimit(60);

    int item_seleccionado = 0;
    std::vector<sf::Text> opciones_menu;

    sf::Font alagard;
    (void)alagard.openFromFile("medieval.ttf");

    sf::Texture textura_fondo;
    (void)textura_fondo.loadFromFile("fondo.png");
    sf::Sprite sprite_fondo(textura_fondo);

    inicializarmenu(opciones_menu, alagard, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

    sf::Text texto_titulo(alagard);
    texto_titulo.setString("DUNGEON SURVIVAL");
    texto_titulo.setCharacterSize(65);
    texto_titulo.setFillColor(sf::Color::White);
    texto_titulo.setOutlineThickness(4.0f);
    texto_titulo.setOutlineColor(sf::Color::Black);
    {
        auto bounds = texto_titulo.getLocalBounds();
        texto_titulo.setOrigin({ bounds.size.x / 2.0f, 0.0f });
    }
    texto_titulo.setPosition({ window.getSize().x / 2.0f, 40.0f });

    sf::RectangleShape panel_menu({ 280.0f, 330.0f });
    panel_menu.setPosition({ 260.0f, 200.0f });
    panel_menu.setFillColor(sf::Color(20, 20, 20, 220));
    panel_menu.setOutlineColor(sf::Color(140, 140, 140));
    panel_menu.setOutlineThickness(3.0f);

    sf::RectangleShape panel_oscuro({ 720.0f, 520.0f });
    panel_oscuro.setPosition({ 40.0f, 40.0f });
    panel_oscuro.setFillColor(sf::Color(0, 0, 0, 200));
    panel_oscuro.setOutlineColor(sf::Color(139, 69, 19));
    panel_oscuro.setOutlineThickness(3.0f);

    float spacing_amount = 1.6f;
    float outline_thickness = 2.0f;
    sf::Color outline_color = sf::Color::Black;

    sf::Text texto_reglas(alagard);
    texto_reglas.setString("================= REGLAS =================\n\n"
        " 1) Sos Paolo, un aventurero con 1 sola vida.\n"
        " 2) Debes atravesar 3 mazmorras (niveles).\n"
        " 3) En cada mazmorra hay enemigos, cofres y\n"
        "    un comerciante (excepto el ultimo nivel).\n"
        " 4) Si tu vida llega a 0, perdes el juego.\n"
        " 5) Para ganar, derrota al boss final del nivel 3.\n"
        " 6) Empezas con un Palo y poco oro.\n"
        " 7) Podes comprar pociones y mejoras.\n"
        " 8) Cada enemigo derrotado deja oro y/o loot.\n\n"
        "        (Presiona ENTER para volver al menu)");
    texto_reglas.setCharacterSize(21);
    texto_reglas.setPosition({ 60.0f, 60.0f });
    texto_reglas.setFillColor(sf::Color::White);
    texto_reglas.setLineSpacing(spacing_amount);
    texto_reglas.setOutlineThickness(outline_thickness);
    texto_reglas.setOutlineColor(outline_color);
    {
        auto bounds = texto_reglas.getLocalBounds();
        texto_reglas.setOrigin({ bounds.size.x / 2.0f, 0.0f });
        texto_reglas.setPosition({ window.getSize().x / 2.0f, 60.0f });
    }

    sf::Text texto_controles(alagard);
    texto_controles.setString("============ MANUAL DE CONTROLES ============\n\n"
        " EXPLORACION (en la mazmorra):\n"
        "   W = Mover arriba\n"
        "   S = Mover abajo\n"
        "   A = Mover izquierda\n"
        "   D = Mover derecha\n\n"
        "   5 = Abrir inventario | 6 = Ordenar | 7 = Estado\n"
        "   8 = Guardar partida  | 9 = Volver al menu\n\n"
        " COMBATE (por turnos):\n"
        "   1 = Atacar | 2 = Usar pocion\n"
        "   3 = Defender | 4 = Huir\n\n"
        "        (Presiona ESC para volver)");
    texto_controles.setCharacterSize(21);
    texto_controles.setPosition({ 60.0f, 60.0f });
    texto_controles.setFillColor(sf::Color::White);
    texto_controles.setLineSpacing(spacing_amount);
    texto_controles.setOutlineThickness(outline_thickness);
    texto_controles.setOutlineColor(outline_color);
    {
        auto bounds = texto_controles.getLocalBounds();
        texto_controles.setOrigin({ bounds.size.x / 2.0f, 0.0f });
        texto_controles.setPosition({ window.getSize().x / 2.0f, 60.0f });
    }

    sf::Text texto_creditos(alagard);
    texto_creditos.setString("================ CREDITOS ================\n\n"
        " Proyecto Parcial 2 - Programacion I\n\n"
        " Desarrollado por:\n"
        "   - Ignacio Gonzalez\n"
        "   - Santiago Oviedo\n"
        "   - Santiago Salvay\n\n"
        " Profesora: Monica Liliana Nano\n"
        " Carrera: Ing. en Informatica / Telecomunicaciones\n\n"
        "        (Presiona ENTER para volver al menu)");
    texto_creditos.setCharacterSize(21);
    texto_creditos.setPosition({ 60.0f, 60.0f });
    texto_creditos.setFillColor(sf::Color::White);
    texto_creditos.setLineSpacing(spacing_amount);
    texto_creditos.setOutlineThickness(outline_thickness);
    texto_creditos.setOutlineColor(outline_color);
    {
        auto bounds = texto_creditos.getLocalBounds();
        texto_creditos.setOrigin({ bounds.size.x / 2.0f, 0.0f });
        texto_creditos.setPosition({ window.getSize().x / 2.0f, 60.0f });
    }

    estado_pantalla estado_actual = menu_principal;

    string matriz_fondo[max_filas][max_columnas];
    string matriz_entidades[max_filas][max_columnas];
    cargarnivel(1, matriz_fondo, matriz_entidades);

    sf::Texture tex_suelo, tex_pared_arriba, tex_pared_abajo, tex_pared_izq, tex_pared_der, tex_prota, tex_boss, tex_enemigo, tex_mercader, tex_cofre, tex_salida, tex_fondo_pelea;
    (void)tex_suelo.loadFromFile("suelo.jpg");
    (void)tex_pared_izq.loadFromFile("customladrillo.png");
    (void)tex_pared_abajo.loadFromFile("customladrillo.png");
    (void)tex_pared_der.loadFromFile("customladrillo.png");
    (void)tex_pared_arriba.loadFromFile("customladrillo.png");
    (void)tex_prota.loadFromFile("prota_01.png");
    (void)tex_enemigo.loadFromFile("Enemigo.png");
    (void)tex_mercader.loadFromFile("mercader.png");
    (void)tex_cofre.loadFromFile("cofre.png");
    (void)tex_salida.loadFromFile("salida.png");
    (void)tex_boss.loadFromFile("boss-01.png");
    (void)tex_fondo_pelea.loadFromFile("fondo_pelea.png");

    sf::Sprite sprite_fondo_pelea(tex_fondo_pelea);
    {
        auto tam_fondo = tex_fondo_pelea.getSize();
        if (tam_fondo.x > 0 && tam_fondo.y > 0) {
            sprite_fondo_pelea.setScale({ 800.0f / static_cast<float>(tam_fondo.x), 800.0f / static_cast<float>(tam_fondo.y) });
        }
    }

    // --- VARIABLES DEL COMBATE POR TURNOS ---
    enemigo enemigo_actual;
    int enemigo_pos_x = -1;
    int enemigo_pos_y = -1;
    int enemigo_vida_max = 0;
    bool es_boss_actual = false;
    bool defendiendo = false;
    fase_batalla fase_actual = fase_batalla::espera_input;
    sf::Clock reloj_anim_batalla;
    const float duracion_anim = 0.55f;
    std::string mensaje_batalla = "";

    personaje paolo;
    protagonista(paolo);

    mercader vendedor;
    inicializarmercader(vendedor);
    ordenarmercader(vendedor.catalogo, vendedor.precios, 6);

    int cursor_tienda = 0;
    int cursor_inventario = 0;
    bool en_modo_compra = true;
    bool aviso_puerta = false;

    // Aviso del cofre (recompensas aleatorias)
    bool aviso_cofre = false;
    cofre cofre_resultado;
    std::string mensaje_cofre = "";

    bool en_pausa = false;
    int item_pausa = 0;
    std::vector<sf::Text> opciones_pausa;
    std::vector<std::string> textos_pausa = { "Seguir Jugando", "Guardar Partida", "Ver Controles", "Volver al Menu" };

    for (int i = 0; i < textos_pausa.size(); i++) {
        sf::Text texto(alagard);
        texto.setString(textos_pausa[i]);
        texto.setCharacterSize(30);
        if (i == 0) texto.setFillColor(sf::Color::Red);
        else texto.setFillColor(sf::Color::White);
        texto.setPosition({ 260.0f, 350.0f + (i * 45.0f) });
        opciones_pausa.push_back(texto);
    }

    sf::Text texto_pausa_titulo(alagard);
    texto_pausa_titulo.setString("JUEGO EN PAUSA");
    texto_pausa_titulo.setCharacterSize(45);
    texto_pausa_titulo.setFillColor(sf::Color::Yellow);
    {
        auto bounds = texto_pausa_titulo.getLocalBounds();
        texto_pausa_titulo.setOrigin({ bounds.size.x / 2.0f, 0.0f });
    }
    texto_pausa_titulo.setPosition({ window.getSize().x / 2.0f, 250.0f });

    sf::RectangleShape fondo_pausa({ 460.0f, 340.0f });
    fondo_pausa.setFillColor(sf::Color(0, 0, 0, 220));
    fondo_pausa.setPosition({ 180.0f, 220.0f });
    fondo_pausa.setOutlineColor(sf::Color::White);
    fondo_pausa.setOutlineThickness(2.0f);

    sf::RectangleShape fondo_confirmacion({ 560.0f, 240.0f });
    fondo_confirmacion.setFillColor(sf::Color(0, 0, 0, 230));
    fondo_confirmacion.setOrigin({ 280.0f, 120.0f });
    fondo_confirmacion.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
    fondo_confirmacion.setOutlineColor(sf::Color::White);
    fondo_confirmacion.setOutlineThickness(2.0f);

    sf::RectangleShape fondo_aviso_guardado({ 540.0f, 200.0f });
    fondo_aviso_guardado.setOrigin({ 270.0f, 100.0f });
    fondo_aviso_guardado.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
    fondo_aviso_guardado.setFillColor(sf::Color(0, 0, 0, 230));
    fondo_aviso_guardado.setOutlineColor(sf::Color(60, 200, 60));
    fondo_aviso_guardado.setOutlineThickness(3.0f);

    // Linea decorativa superior dentro del recuadro
    sf::RectangleShape linea_deco_guardado({ 460.0f, 3.0f });
    linea_deco_guardado.setOrigin({ 230.0f, 1.5f });
    linea_deco_guardado.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f - 50.0f });
    linea_deco_guardado.setFillColor(sf::Color(60, 200, 60));

    sf::Text texto_guardado_titulo(alagard);
    texto_guardado_titulo.setString("Partida guardada correctamente");
    texto_guardado_titulo.setCharacterSize(28);
    texto_guardado_titulo.setFillColor(sf::Color::Green);
    texto_guardado_titulo.setOutlineColor(sf::Color::Black);
    texto_guardado_titulo.setOutlineThickness(2.0f);
    {
        auto bounds = texto_guardado_titulo.getLocalBounds();
        texto_guardado_titulo.setOrigin({ bounds.size.x / 2.0f, 0.0f });
    }
    texto_guardado_titulo.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f - 30.0f });

    sf::Text texto_guardado_subtitulo(alagard);
    texto_guardado_subtitulo.setString("Presiona ENTER para continuar");
    texto_guardado_subtitulo.setCharacterSize(20);
    texto_guardado_subtitulo.setFillColor(sf::Color(200, 200, 200));
    {
        auto bounds = texto_guardado_subtitulo.getLocalBounds();
        texto_guardado_subtitulo.setOrigin({ bounds.size.x / 2.0f, 0.0f });
    }
    texto_guardado_subtitulo.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f + 30.0f });

    sf::Text texto_confirmacion_titulo(alagard);
    texto_confirmacion_titulo.setString("Quieres guardar la partida?");
    texto_confirmacion_titulo.setCharacterSize(30);
    texto_confirmacion_titulo.setFillColor(sf::Color::Yellow);
    {
        auto bounds = texto_confirmacion_titulo.getLocalBounds();
        texto_confirmacion_titulo.setOrigin({ bounds.size.x / 2.0f, 0.0f });
    }
    float confirmacion_y = window.getSize().y / 2.0f;
    texto_confirmacion_titulo.setPosition({ window.getSize().x / 2.0f, confirmacion_y - 70.0f });

    std::vector<sf::Text> opciones_confirmacion;
    std::vector<std::string> textos_confirmacion = { "Si", "No" };
    for (int i = 0; i < textos_confirmacion.size(); i++) {
        sf::Text texto(alagard);
        texto.setString(textos_confirmacion[i]);
        texto.setCharacterSize(28);
        texto.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        auto bounds = texto.getLocalBounds();
        texto.setOrigin({ bounds.size.x / 2.0f, 0.0f });
        texto.setPosition({ window.getSize().x / 2.0f, confirmacion_y - 5.0f + (i * 45.0f) });
        opciones_confirmacion.push_back(texto);
    }

    int item_confirmacion = 0;
    bool salir_despues_confirmacion = false;
    bool guardado_reciente = false;
    bool controles_desde_pausa = false;
    bool aviso_boss = false;
    estado_pantalla estado_pendiente = jugando;

    std::vector<registro_partida> partidas_guardadas;
    std::vector<sf::Text> opciones_carga;
    int item_carga = 0;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {

                if (estado_actual == menu_principal) {
                    if (key_pressed->code == sf::Keyboard::Key::W || key_pressed->code == sf::Keyboard::Key::Up) {
                        moverarriba(item_seleccionado, opciones_menu);
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::S || key_pressed->code == sf::Keyboard::Key::Down) {
                        moverabajo(item_seleccionado, opciones_menu);
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::Enter) {
                        switch (item_seleccionado) {
                        case 0: estado_actual = jugando; break;
                        case 1:
                            partidas_guardadas = obtenerPartidas();
                            std::sort(partidas_guardadas.begin(), partidas_guardadas.end(), [](const registro_partida& a, const registro_partida& b) {
                                return a.ultimo_guardado > b.ultimo_guardado;
                            });
                            opciones_carga.clear();
                            item_carga = 0;
                            for (int i = 0; i < static_cast<int>(partidas_guardadas.size()); i++) {
                                const auto& registro = partidas_guardadas[i];
                                std::string nombre_mostrado = registro.pj.name.empty() ? std::string("Paolo") : registro.pj.name;
                                std::ostringstream linea;
                                linea << (i + 1) << ") " << nombre_mostrado
                                    << " - Nivel " << registro.pj.nivel_actual
                                    << " - Oro " << registro.pj.oro << "\n"
                                    << "      " << formatearFecha(registro.ultimo_guardado);
                                sf::Text texto(alagard);
                                texto.setString(linea.str());
                                texto.setCharacterSize(22);
                                texto.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
                                texto.setLineSpacing(1.2f);
                                auto bounds = texto.getLocalBounds();
                                texto.setOrigin({ bounds.size.x / 2.0f, 0.0f });
                                texto.setPosition({ window.getSize().x / 2.0f, 160.0f + (i * 70.0f) });
                                opciones_carga.push_back(texto);
                            }
                            estado_actual = cargar;
                            break;
                        case 2: estado_actual = controles; break;
                        case 3: estado_actual = reglas; break;
                        case 4: estado_actual = creditos; break;
                        case 5: window.close(); break;
                        }
                    }
                }
                else if (estado_actual == cargar && opciones_carga.empty()) {
                    if (key_pressed->code == sf::Keyboard::Key::Enter || key_pressed->code == sf::Keyboard::Key::Escape) {
                        estado_actual = menu_principal;
                    }
                }
                else if (estado_actual == aviso_guardado) {
                    if (key_pressed->code == sf::Keyboard::Key::Enter || key_pressed->code == sf::Keyboard::Key::Escape) {
                        estado_actual = estado_pendiente;
                        if (salir_despues_confirmacion) {
                            estado_actual = menu_principal;
                            en_pausa = false;
                            salir_despues_confirmacion = false;
                        }
                    }
                }
                else if (estado_actual == reglas || estado_actual == controles || estado_actual == creditos) {
                    if (estado_actual == controles && controles_desde_pausa) {
                        // Si vinimos desde la pausa, ESC vuelve al juego (no al menu)
                        if (key_pressed->code == sf::Keyboard::Key::Escape || key_pressed->code == sf::Keyboard::Key::Enter) {
                            controles_desde_pausa = false;
                            estado_actual = jugando;
                        }
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::Enter || key_pressed->code == sf::Keyboard::Key::Escape) {
                        estado_actual = menu_principal;
                    }
                }
                else if (estado_actual == cargar) {
                    if (key_pressed->code == sf::Keyboard::Key::Escape) {
                        estado_actual = menu_principal;
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::W || key_pressed->code == sf::Keyboard::Key::Up) {
                        moverarriba(item_carga, opciones_carga);
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::S || key_pressed->code == sf::Keyboard::Key::Down) {
                        moverabajo(item_carga, opciones_carga);
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::Enter) {
                        if (item_carga >= 0 && item_carga < static_cast<int>(partidas_guardadas.size())) {
                            const registro_partida& partida_seleccionada = partidas_guardadas[item_carga];
                            cargarPartidaPorIndice(paolo, item_carga, matriz_entidades);
                            string matriz_entidades_base[max_filas][max_columnas];
                            cargarnivel(paolo.nivel_actual, matriz_fondo, matriz_entidades_base);
                            for (int i = 0; i < max_filas; i++) {
                                for (int j = 0; j < max_columnas; j++) {
                                    if (matriz_entidades[i][j] == "P") {
                                        matriz_entidades[i][j] = "";
                                    }
                                }
                            }
                            if (paolo.posicion_y >= 0 && paolo.posicion_y < max_filas &&
                                paolo.posicion_x >= 0 && paolo.posicion_x < max_columnas) {
                                matriz_entidades[paolo.posicion_y][paolo.posicion_x] = "P";
                            }
                            // Si el nivel cargado tiene Boss, advertimos al jugador
                            aviso_boss = false;
                            for (int i = 0; i < max_filas && !aviso_boss; i++) {
                                for (int j = 0; j < max_columnas && !aviso_boss; j++) {
                                    if (matriz_entidades[i][j] == "B") {
                                        aviso_boss = true;
                                    }
                                }
                            }
                            estado_actual = jugando;
                        }
                    }
                }
                else if (estado_actual == confirmar_guardado) {
                    if (key_pressed->code == sf::Keyboard::Key::W || key_pressed->code == sf::Keyboard::Key::Up) {
                        moverarriba(item_confirmacion, opciones_confirmacion);
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::S || key_pressed->code == sf::Keyboard::Key::Down) {
                        moverabajo(item_confirmacion, opciones_confirmacion);
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::Enter) {
                        if (item_confirmacion == 0) {
                            guardarPartida(paolo, matriz_entidades);
                            guardado_reciente = true;
                            estado_actual = aviso_guardado;
                            break;
                        }
                        estado_actual = estado_pendiente;
                        if (salir_despues_confirmacion) {
                            estado_actual = menu_principal;
                            en_pausa = false;
                        }
                    }
                }
                else if (estado_actual == jugando) {

                    if (en_pausa) {
                        // --- CONTROL CON EL JUEGO PAUSADO ---
                        if (key_pressed->code == sf::Keyboard::Key::W || key_pressed->code == sf::Keyboard::Key::Up) {
                            moverarriba(item_pausa, opciones_pausa);
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::S || key_pressed->code == sf::Keyboard::Key::Down) {
                            moverabajo(item_pausa, opciones_pausa);
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::Enter) {
                            switch (item_pausa) {
                            case 0: // Seguir Jugando
                                en_pausa = false;
                                break;
                            case 1: // Guardar Partida
                                guardarPartida(paolo, matriz_entidades);
                                guardado_reciente = true;
                                estado_pendiente = jugando;
                                estado_actual = aviso_guardado;
                                break;
                            case 2: // Ver Controles (desde la pausa)
                                estado_actual = controles;
                                en_pausa = false;
                                controles_desde_pausa = true;
                                break;
                            case 3: // Volver al Menu
                                if (guardado_reciente) {
                                    estado_actual = menu_principal;
                                    en_pausa = false;
                                    guardado_reciente = false;
                                }
                                else {
                                    item_confirmacion = 0;
                                    opciones_confirmacion[0].setFillColor(sf::Color::Red);
                                    opciones_confirmacion[1].setFillColor(sf::Color::White);
                                    estado_pendiente = jugando;
                                    salir_despues_confirmacion = true;
                                    estado_actual = confirmar_guardado;
                                }
                                break;
                            }
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::Escape) {
                            en_pausa = false; // Despausar también con Escape
                        }
                    }
                    else {
                        // --- CONTROL DE EXPLORACIÓN NORMAL (Tu código base) ---
                        if (key_pressed->code == sf::Keyboard::Key::Num9) {
                            estado_actual = menu_principal;
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::Escape) {
                            en_pausa = true; // Ahora Escape activa la pausa en lugar de salir directo
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::Num5) {
                            estado_actual = en_inventario;
                            cursor_inventario = 0;
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::Num6) {
                            ordenarburbuja(paolo.inventario, paolo.cant_items);
                            std::cout << "Inventario Ordenado!" << std::endl;
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::Num8) {
                            guardarPartida(paolo, matriz_entidades);
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::W) {
                            moverpj(paolo, 'W', matriz_fondo, matriz_entidades);
                            aviso_puerta = false;
                            aviso_cofre = false;
                            aviso_boss = false;
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::S) {
                            moverpj(paolo, 'S', matriz_fondo, matriz_entidades);
                            aviso_puerta = false;
                            aviso_cofre = false;
                            aviso_boss = false;
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::A) {
                            moverpj(paolo, 'A', matriz_fondo, matriz_entidades);
                            aviso_puerta = false;
                            aviso_cofre = false;
                            aviso_boss = false;
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::D) {
                            moverpj(paolo, 'D', matriz_fondo, matriz_entidades);
                            aviso_puerta = false;
                            aviso_cofre = false;
                            aviso_boss = false;
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::E) {
                            // Limpiamos el resultado para no arrastrar datos viejos
                            cofre_resultado.oro = 0;
                            cofre_resultado.cant_loot = 0;

                            char resultado = interactuar(paolo, matriz_entidades, matriz_fondo, cofre_resultado);

                            if (resultado == 'S') {
                                paolo.nivel_actual = paolo.nivel_actual + 1;
                                cargarnivel(paolo.nivel_actual, matriz_fondo, matriz_entidades);
                                paolo.posicion_x = 1;
                                paolo.posicion_y = 1;
                                aviso_puerta = false;
                                aviso_cofre = false;
                                // Si el nuevo nivel tiene un Boss, advertimos al jugador
                                aviso_boss = false;
                                for (int i = 0; i < max_filas && !aviso_boss; i++) {
                                    for (int j = 0; j < max_columnas && !aviso_boss; j++) {
                                        if (matriz_entidades[i][j] == "B") {
                                            aviso_boss = true;
                                        }
                                    }
                                }
                            }
                            else if (resultado == 'L') {
                                aviso_puerta = true;
                                aviso_cofre = false;
                            }
                            else if (resultado == 'C') {
                                // Armamos el cartel con las recompensas aleatorias del cofre
                                std::ostringstream oss;
                                oss << "Encontraste un cofre!\n\n";
                                oss << "  +" << cofre_resultado.oro << " de oro\n\n";
                                oss << "  Loot obtenido:\n";
                                for (int i = 0; i < cofre_resultado.cant_loot; i++) {
                                    oss << "    - " << cofre_resultado.loot[i] << "\n";
                                }
                                mensaje_cofre = oss.str();
                                aviso_cofre = true;
                                aviso_puerta = false;
                            }
                            else if (resultado == 'M') {
                                estado_actual = en_tienda;
                                cursor_tienda = 0;
                                cursor_inventario = 0;
                                en_modo_compra = true;
                                aviso_puerta = false;
                                aviso_cofre = false;
                            }
                            else if (resultado == 'E' || resultado == 'B') {
                                // Busca al enemigo adyacente (mismo orden que la funcion interactuar)
                                int px = paolo.posicion_x;
                                int py = paolo.posicion_y;
                                enemigo_pos_x = -1;
                                enemigo_pos_y = -1;
                                int dxs[4] = { 0, 0, 1, -1 };
                                int dys[4] = { -1, 1, 0, 0 };
                                for (int d = 0; d < 4; d++) {
                                    int nx = px + dxs[d];
                                    int ny = py + dys[d];
                                    if (nx >= 0 && nx < max_columnas && ny >= 0 && ny < max_filas) {
                                        if (matriz_entidades[ny][nx] == "E" || matriz_entidades[ny][nx] == "B") {
                                            enemigo_pos_x = nx;
                                            enemigo_pos_y = ny;
                                            es_boss_actual = (matriz_entidades[ny][nx] == "B");
                                            break;
                                        }
                                    }
                                }
                                inicializarenemigo(enemigo_actual, es_boss_actual);
                                enemigo_vida_max = enemigo_actual.vida;
                                defendiendo = false;
                                if (es_boss_actual) {
                                    fase_actual = fase_batalla::cinematica_boss;
                                    mensaje_batalla = "";
                                }
                                else {
                                    fase_actual = fase_batalla::espera_input;
                                    mensaje_batalla = "Un enemigo se cruza en tu camino!";
                                }
                                reloj_anim_batalla.restart();
                                estado_actual = en_batalla;
                                aviso_puerta = false;
                                aviso_cofre = false;
                            }
                        }
                    }
                }
                else if (estado_actual == en_inventario) {
                    // Helpers: calculo de grupos del inventario ordenado
                    auto contar_grupos = [&]() -> int {
                        int c = 0;
                        for (int i = 0; i < paolo.cant_items; ) {
                            int j = i;
                            while (j < paolo.cant_items && paolo.inventario[j] == paolo.inventario[i]) j++;
                            c++;
                            i = j;
                        }
                        return c;
                    };
                    auto indice_plano_grupo = [&](int idx_grupo) -> int {
                        int c = 0;
                        for (int i = 0; i < paolo.cant_items; ) {
                            int j = i;
                            while (j < paolo.cant_items && paolo.inventario[j] == paolo.inventario[i]) j++;
                            if (c == idx_grupo) return i;
                            c++;
                            i = j;
                        }
                        return -1;
                    };

                    if (key_pressed->code == sf::Keyboard::Key::Escape || key_pressed->code == sf::Keyboard::Key::Num5) {
                        estado_actual = jugando;
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::W || key_pressed->code == sf::Keyboard::Key::Up) {
                        if (cursor_inventario > 0) cursor_inventario--;
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::S || key_pressed->code == sf::Keyboard::Key::Down) {
                        int n_grupos = contar_grupos();
                        if (cursor_inventario < n_grupos - 1) cursor_inventario++;
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::Enter) {
                        if (paolo.cant_items > 0) {
                            int idx_plano = indice_plano_grupo(cursor_inventario);
                            if (idx_plano < 0) idx_plano = 0;
                            string item_sel = paolo.inventario[idx_plano];

                            if (item_sel == "Palo" || item_sel == "Daga Rota" || item_sel == "Espada de Hierro") {
                                paolo.arma_equipada = item_sel;
                                paolo.ataque = 8 + obtenerataque(item_sel);
                            }
                            else if (item_sel == "Armadura Ligera" || item_sel == "Armadura Pesada") {
                                int defensa_vieja = paolo.defensa;
                                paolo.armadura_equipada = item_sel;
                                paolo.defensa = obtenerdefensa(item_sel);

                                // Ajustamos la vida actual segun el nuevo maximo
                                paolo.vida += (paolo.defensa - defensa_vieja);
                            }
                            else if (item_sel == "Pocion Chica" || item_sel == "Pocion Pequena" || item_sel == "Pocion Grande") {
                                if (item_sel == "Pocion Grande") paolo.vida += 50;
                                else paolo.vida += 20;

                                // EL TOPE DE VIDA AHORA DEPENDE DE LA ARMADURA
                                int vida_maxima = 100 + paolo.defensa;
                                if (paolo.vida > vida_maxima) paolo.vida = vida_maxima;

                                for (int i = idx_plano; i < paolo.cant_items - 1; i++) {
                                    paolo.inventario[i] = paolo.inventario[i + 1];
                                }
                                paolo.cant_items--;

                                // Si el grupo quedo vacio (era el ultimo item del grupo), ajustamos el cursor
                                int n_grupos_nuevos = contar_grupos();
                                if (cursor_inventario >= n_grupos_nuevos && cursor_inventario > 0) {
                                    cursor_inventario--;
                                }
                            }
                        }
                    }
                }
                else if (estado_actual == en_tienda) {
                    if (key_pressed->code == sf::Keyboard::Key::Escape) {
                        estado_actual = jugando;
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::A || key_pressed->code == sf::Keyboard::Key::Left) {
                        en_modo_compra = true;
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::D || key_pressed->code == sf::Keyboard::Key::Right) {
                        if (paolo.cant_items > 0) {
                            en_modo_compra = false;
                        }
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::W || key_pressed->code == sf::Keyboard::Key::Up) {
                        if (en_modo_compra && cursor_tienda > 0) cursor_tienda--;
                        else if (!en_modo_compra && cursor_inventario > 0) cursor_inventario--;
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::S || key_pressed->code == sf::Keyboard::Key::Down) {
                        if (en_modo_compra && cursor_tienda < 5) cursor_tienda++;
                        else if (!en_modo_compra && cursor_inventario < paolo.cant_items - 1) cursor_inventario++;
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::Enter) {
                        if (en_modo_compra) {
                            int precio_item = vendedor.precios[cursor_tienda];
                            if (paolo.oro >= precio_item && paolo.cant_items < 50) {
                                paolo.oro -= precio_item;
                                paolo.inventario[paolo.cant_items] = vendedor.catalogo[cursor_tienda];
                                paolo.cant_items++;

                                ordenarburbuja(paolo.inventario, paolo.cant_items);
                            }
                        }
                        else {
                            if (paolo.cant_items > 0) {
                                std::string item_a_vender = paolo.inventario[cursor_inventario];
                                int pos = buscaritem(paolo.inventario, paolo.cant_items, item_a_vender);

                                paolo.oro += obtenerprecioventa(item_a_vender);

                                for (int i = pos; i < paolo.cant_items - 1; i++) {
                                    paolo.inventario[i] = paolo.inventario[i + 1];
                                }
                                paolo.cant_items--;

                                if (cursor_inventario >= paolo.cant_items && cursor_inventario > 0) {
                                    cursor_inventario--;
                                }
                                if (paolo.cant_items == 0) {
                                    en_modo_compra = true;
                                }
                            }
                        }
                    }
                }
                else if (estado_actual == en_batalla) {
                    // Si la batalla termino, ENTER vuelve al juego o al menu
                    if (fase_actual == fase_batalla::ganada || fase_actual == fase_batalla::huida) {
                        if (key_pressed->code == sf::Keyboard::Key::Enter) {
                            estado_actual = jugando;
                        }
                    }
                    else if (fase_actual == fase_batalla::victoria_final) {
                        // Tras vencer al boss, ENTER lleva al menu principal con la partida terminada
                        if (key_pressed->code == sf::Keyboard::Key::Enter) {
                            estado_actual = menu_principal;
                        }
                    }
                    else if (fase_actual == fase_batalla::perdida) {
                        if (key_pressed->code == sf::Keyboard::Key::Enter) {
                            // Resetea al protagonista y vuelve al menu
                            protagonista(paolo);
                            cargarnivel(paolo.nivel_actual, matriz_fondo, matriz_entidades);
                            estado_actual = menu_principal;
                        }
                    }
                    else if (fase_actual == fase_batalla::cinematica_boss) {
                        // Permite saltear la cinematica con ENTER o ESC
                        if (key_pressed->code == sf::Keyboard::Key::Enter || key_pressed->code == sf::Keyboard::Key::Escape) {
                            fase_actual = fase_batalla::espera_input;
                            mensaje_batalla = "El Guardian de la Mazmorra te desafia! Que haces?";
                            reloj_anim_batalla.restart();
                        }
                    }
                    // Solo aceptamos input cuando es el turno del jugador
                    else if (fase_actual == fase_batalla::espera_input) {
                        if (key_pressed->code == sf::Keyboard::Key::Num1) {
                            reloj_anim_batalla.restart();
                            fase_actual = fase_batalla::anim_pj_ataca;
                            mensaje_batalla = "Atacas al " + enemigo_actual.nombre + "!";
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::Num2) {
                            // Busca una pocion en el inventario
                            int idx_poc = -1;
                            for (int i = 0; i < paolo.cant_items; i++) {
                                if (paolo.inventario[i] == "Pocion Chica" ||
                                    paolo.inventario[i] == "Pocion Pequena" ||
                                    paolo.inventario[i] == "Pocion Grande") {
                                    idx_poc = i;
                                    break;
                                }
                            }
                            if (idx_poc >= 0) {
                                std::string nombre_poc = paolo.inventario[idx_poc];
                                int curar = (nombre_poc == "Pocion Grande") ? 50 : 20;
                                paolo.vida += curar;
                                int vida_max = 100 + paolo.defensa;
                                if (paolo.vida > vida_max) paolo.vida = vida_max;
                                for (int i = idx_poc; i < paolo.cant_items - 1; i++) {
                                    paolo.inventario[i] = paolo.inventario[i + 1];
                                }
                                paolo.cant_items--;
                                mensaje_batalla = "Usaste " + nombre_poc + " (+" + std::to_string(curar) + " HP)";
                                reloj_anim_batalla.restart();
                                fase_actual = fase_batalla::anim_pocion;
                            }
                            else {
                                mensaje_batalla = "No tienes pociones para usar!";
                            }
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::Num3) {
                            defendiendo = true;
                            mensaje_batalla = "Te preparas para defender el proximo ataque.";
                            reloj_anim_batalla.restart();
                            fase_actual = fase_batalla::anim_enemigo_ataca;
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::Num4) {
                            if (es_boss_actual) {
                                mensaje_batalla = "No puedes huir del Boss!";
                            }
                            else {
                                int chance = std::rand() % 100;
                                if (chance < 55) {
                                    mensaje_batalla = "Lograste huir del combate! (ENTER)";
                                    fase_actual = fase_batalla::huida;
                                }
                                else {
                                    mensaje_batalla = "Fallaste la huida! El enemigo aprovecha y ataca!";
                                    reloj_anim_batalla.restart();
                                    fase_actual = fase_batalla::anim_enemigo_ataca;
                                }
                            }
                        }
                    }
                }
            }
        }

        // --- ACTUALIZACION DEL TURNO Y ANIMACIONES DE BATALLA ---
        if (estado_actual == en_batalla) {
            float t_anim = reloj_anim_batalla.getElapsedTime().asSeconds();

            if (fase_actual == fase_batalla::anim_pj_ataca && t_anim >= duracion_anim) {
                // El jugador hace ~150% del dano base (ventaja clara contra enemigos)
                int dano_base = (paolo.ataque * 3) / 2 + (std::rand() % 6);
                int dano_real = dano_base - enemigo_actual.defensa;
                if (dano_real < 2) dano_real = 2;
                enemigo_actual.vida -= dano_real;

                if (enemigo_actual.vida <= 0) {
                    enemigo_actual.vida = 0;
                    // Recompensa segun tipo de enemigo
                    int recompensa = es_boss_actual ? (60 + std::rand() % 41) : (10 + std::rand() % 16);
                    paolo.oro += recompensa;
                    // Borramos al enemigo del mapa
                    if (enemigo_pos_x >= 0 && enemigo_pos_y >= 0 &&
                        enemigo_pos_y < max_filas && enemigo_pos_x < max_columnas) {
                        matriz_entidades[enemigo_pos_y][enemigo_pos_x] = "";
                    }
                    if (es_boss_actual) {
                        mensaje_batalla = "Ganaste " + std::to_string(recompensa) + " de oro!";
                        fase_actual = fase_batalla::victoria_final;
                        reloj_anim_batalla.restart();
                    }
                    else {
                        mensaje_batalla = "Victoria! Causaste " + std::to_string(dano_real) +
                            " de dano final. Ganaste " + std::to_string(recompensa) + " de oro. (ENTER)";
                        fase_actual = fase_batalla::ganada;
                    }
                    // Guardamos automaticamente la partida tras la victoria
                    guardarPartida(paolo, matriz_entidades);
                }
                else {
                    mensaje_batalla = "Causaste " + std::to_string(dano_real) + " de dano al " + enemigo_actual.nombre + ".";
                    reloj_anim_batalla.restart();
                    fase_actual = fase_batalla::anim_enemigo_ataca;
                }
            }
            else if (fase_actual == fase_batalla::anim_enemigo_ataca && t_anim >= duracion_anim) {
                // El enemigo comun pega al 70% de su ataque base; el boss al 80% (mas peligroso pero el jugador tiene chance real)
                int multiplicador = es_boss_actual ? 80 : 70;
                int dano_base = (enemigo_actual.ataque * multiplicador) / 100 + (std::rand() % (es_boss_actual ? 4 : 3));
                int dano_real = dano_base - (paolo.defensa / 10);
                if (defendiendo) {
                    dano_real = dano_real / 2;
                    defendiendo = false;
                }
                if (dano_real < 1) dano_real = 1;
                paolo.vida -= dano_real;

                if (paolo.vida <= 0) {
                    paolo.vida = 0;
                    mensaje_batalla = "Has caido en batalla... (ENTER para volver al menu)";
                    fase_actual = fase_batalla::perdida;
                }
                else {
                    mensaje_batalla = "El " + enemigo_actual.nombre + " te causa " +
                        std::to_string(dano_real) + " de dano. Tu turno! (1/2/3/4)";
                    fase_actual = fase_batalla::espera_input;
                }
            }
            else if (fase_actual == fase_batalla::anim_pocion && t_anim >= duracion_anim) {
                // Tras curarse, ataca el enemigo
                reloj_anim_batalla.restart();
                fase_actual = fase_batalla::anim_enemigo_ataca;
            }
        }

        window.clear();

        if (estado_actual == en_batalla) {
            // === RENDER DE LA PANTALLA DE BATALLA ===
            window.draw(sprite_fondo_pelea);

            // === CINEMATICA EPICA AL ENFRENTAR AL BOSS ===
            if (fase_actual == fase_batalla::cinematica_boss) {
                const float PI = 3.14159265f;
                float t = reloj_anim_batalla.getElapsedTime().asSeconds();
                const float dur_total = 6.5f;

                // Velo negro general que se va aclarando
                {
                    float alpha_velo = 255.f;
                    if (t < 0.8f) alpha_velo = 255.f - (t / 0.8f) * 100.f;
                    else alpha_velo = 155.f - std::min(1.f, (t - 0.8f) / 1.2f) * 95.f;
                    if (alpha_velo < 60.f) alpha_velo = 60.f;
                    sf::RectangleShape velo({ 800.f, 800.f });
                    velo.setFillColor(sf::Color(0, 0, 0, static_cast<std::uint8_t>(alpha_velo)));
                    window.draw(velo);
                }

                // El sprite del boss aparece desde la derecha mientras tiembla
                {
                    sf::Sprite spr_boss(tex_boss);
                    auto tam = tex_boss.getSize();
                    float escala_extra = 1.f;
                    if (t > 2.0f) escala_extra = 1.f + std::min(1.f, (t - 2.0f) / 2.5f) * 0.6f;
                    if (tam.x > 0) {
                        float escala = (260.f / static_cast<float>(tam.x)) * escala_extra;
                        spr_boss.setScale({ escala, escala });
                    }

                    float prog_entrada = std::min(1.f, t / 1.6f);
                    float prog_eased = 1.f - (1.f - prog_entrada) * (1.f - prog_entrada);
                    float pos_x_objetivo = 400.f - 130.f;
                    float pos_x_boss = 820.f + (pos_x_objetivo - 820.f) * prog_eased;
                    float pos_y_boss = 250.f;

                    // Temblor al estar instalado
                    if (t > 1.7f) {
                        pos_x_boss += std::sin(t * 28.f) * 4.f;
                        pos_y_boss += std::cos(t * 24.f) * 3.f;
                    }
                    spr_boss.setPosition({ pos_x_boss, pos_y_boss });
                    window.draw(spr_boss);
                }

                // Destello rojo cuando el boss se planta (a partir de t=2s)
                if (t >= 2.0f && t < 3.0f) {
                    float prog_flash = (t - 2.0f) / 1.0f;
                    float alpha_flash = std::sin(prog_flash * PI) * 140.f;
                    if (alpha_flash > 0.f) {
                        sf::RectangleShape flash({ 800.f, 800.f });
                        flash.setFillColor(sf::Color(180, 0, 0, static_cast<std::uint8_t>(alpha_flash)));
                        window.draw(flash);
                    }
                }

                // Texto dramatico que aparece en cascada
                auto dibujar_texto_dram = [&](const std::string& s, float aparece, float desaparece, float y, unsigned size, sf::Color color) {
                    if (t < aparece || t > desaparece) return;
                    float local = t - aparece;
                    float dur = desaparece - aparece;
                    float alpha = 255.f;
                    if (local < 0.25f) alpha = (local / 0.25f) * 255.f;
                    else if (local > dur - 0.4f) alpha = ((dur - local) / 0.4f) * 255.f;
                    if (alpha < 0.f) alpha = 0.f;
                    if (alpha > 255.f) alpha = 255.f;
                    sf::Text txt(alagard);
                    txt.setString(s);
                    txt.setCharacterSize(size);
                    sf::Color c = color;
                    c.a = static_cast<std::uint8_t>(alpha);
                    txt.setFillColor(c);
                    txt.setOutlineColor(sf::Color(0, 0, 0, static_cast<std::uint8_t>(alpha)));
                    txt.setOutlineThickness(3.f);
                    auto b = txt.getLocalBounds();
                    txt.setOrigin({ b.size.x / 2.f, 0.f });
                    txt.setPosition({ 400.f, y });
                    window.draw(txt);
                };

                dibujar_texto_dram("Una presencia oscura se acerca...", 0.4f, 2.0f, 90.f, 24, sf::Color(220, 220, 220));
                dibujar_texto_dram("EL GUARDIAN DESPIERTA", 2.1f, 4.2f, 80.f, 44, sf::Color(255, 80, 80));
                dibujar_texto_dram("Su mirada se clava en ti...", 3.0f, 5.0f, 150.f, 22, sf::Color(220, 220, 220));
                dibujar_texto_dram("BATALLA FINAL", 4.5f, 6.4f, 580.f, 56, sf::Color(255, 215, 0));
                dibujar_texto_dram("Que el destino decida...", 5.0f, 6.4f, 650.f, 22, sf::Color(220, 220, 220));

                // Hint para saltear
                sf::Text saltear(alagard);
                saltear.setString("(ENTER para saltear)");
                saltear.setCharacterSize(14);
                saltear.setFillColor(sf::Color(180, 180, 180, 200));
                saltear.setPosition({ 620.f, 770.f });
                window.draw(saltear);

                // Al finalizar el tiempo, pasa al combate
                if (t >= dur_total) {
                    fase_actual = fase_batalla::espera_input;
                    mensaje_batalla = "El Guardian de la Mazmorra te desafia! Que haces?";
                    reloj_anim_batalla.restart();
                }

                window.display();
                continue;
            }

            // Calculo del desplazamiento de la animacion (curva senoidal)
            float t_norm = reloj_anim_batalla.getElapsedTime().asSeconds() / duracion_anim;
            if (t_norm > 1.0f) t_norm = 1.0f;
            float offset_pj = 0.f;
            float offset_en = 0.f;
            if (fase_actual == fase_batalla::anim_pj_ataca) {
                offset_pj = std::sin(t_norm * 3.14159265f) * 130.f;
            }
            else if (fase_actual == fase_batalla::anim_enemigo_ataca) {
                offset_en = -std::sin(t_norm * 3.14159265f) * 130.f;
            }
            else if (fase_actual == fase_batalla::anim_pocion) {
                offset_pj = std::sin(t_norm * 3.14159265f * 4.f) * 12.f;
            }

            // Sprite del protagonista (izquierda)
            sf::Sprite sprite_pj_batalla(tex_prota);
            {
                auto tam_pj = tex_prota.getSize();
                if (tam_pj.x > 0) {
                    float escala = 220.f / static_cast<float>(tam_pj.x);
                    sprite_pj_batalla.setScale({ escala, escala });
                }
            }
            sprite_pj_batalla.setPosition({ 110.f + offset_pj, 340.f });
            window.draw(sprite_pj_batalla);

            // Sprite del enemigo (derecha)
            sf::Sprite sprite_enemigo_batalla(es_boss_actual ? tex_boss : tex_enemigo);
            {
                auto tam_en = (es_boss_actual ? tex_boss : tex_enemigo).getSize();
                if (tam_en.x > 0) {
                    float escala = 220.f / static_cast<float>(tam_en.x);
                    sprite_enemigo_batalla.setScale({ escala, escala });
                }
            }
            sprite_enemigo_batalla.setPosition({ 470.f + offset_en, 340.f });
            window.draw(sprite_enemigo_batalla);

            // --- BARRA DE VIDA DEL PROTAGONISTA ---
            int vida_max_pj = 100 + paolo.defensa;
            float porc_pj = (vida_max_pj > 0) ? (static_cast<float>(paolo.vida) / static_cast<float>(vida_max_pj)) : 0.f;
            if (porc_pj < 0.f) porc_pj = 0.f;
            if (porc_pj > 1.f) porc_pj = 1.f;

            sf::RectangleShape marco_vida_pj({ 240.f, 24.f });
            marco_vida_pj.setPosition({ 40.f, 110.f });
            marco_vida_pj.setFillColor(sf::Color(30, 30, 30, 220));
            marco_vida_pj.setOutlineColor(sf::Color::White);
            marco_vida_pj.setOutlineThickness(2.f);
            window.draw(marco_vida_pj);

            sf::RectangleShape barra_vida_pj({ 240.f * porc_pj, 24.f });
            barra_vida_pj.setPosition({ 40.f, 110.f });
            barra_vida_pj.setFillColor(sf::Color(70, 200, 70));
            window.draw(barra_vida_pj);

            sf::Text nombre_pj(alagard);
            nombre_pj.setString((paolo.name.empty() ? std::string("Paolo") : paolo.name) +
                "   HP: " + std::to_string(paolo.vida) + " / " + std::to_string(vida_max_pj));
            nombre_pj.setCharacterSize(20);
            nombre_pj.setFillColor(sf::Color::White);
            nombre_pj.setOutlineColor(sf::Color::Black);
            nombre_pj.setOutlineThickness(2.f);
            nombre_pj.setPosition({ 40.f, 75.f });
            window.draw(nombre_pj);

            // --- BARRA DE VIDA DEL ENEMIGO ---
            float porc_en = (enemigo_vida_max > 0) ? (static_cast<float>(enemigo_actual.vida) / static_cast<float>(enemigo_vida_max)) : 0.f;
            if (porc_en < 0.f) porc_en = 0.f;
            if (porc_en > 1.f) porc_en = 1.f;

            sf::RectangleShape marco_vida_en({ 240.f, 24.f });
            marco_vida_en.setPosition({ 520.f, 110.f });
            marco_vida_en.setFillColor(sf::Color(30, 30, 30, 220));
            marco_vida_en.setOutlineColor(sf::Color::White);
            marco_vida_en.setOutlineThickness(2.f);
            window.draw(marco_vida_en);

            sf::RectangleShape barra_vida_en({ 240.f * porc_en, 24.f });
            barra_vida_en.setPosition({ 520.f, 110.f });
            barra_vida_en.setFillColor(sf::Color(200, 60, 60));
            window.draw(barra_vida_en);

            sf::Text nombre_en(alagard);
            nombre_en.setString(enemigo_actual.nombre + "   HP: " +
                std::to_string(enemigo_actual.vida) + " / " + std::to_string(enemigo_vida_max));
            nombre_en.setCharacterSize(20);
            nombre_en.setFillColor(sf::Color::White);
            nombre_en.setOutlineColor(sf::Color::Black);
            nombre_en.setOutlineThickness(2.f);
            nombre_en.setPosition({ 520.f, 75.f });
            window.draw(nombre_en);

            // --- PANEL INFERIOR DE MENSAJES Y OPCIONES ---
            sf::RectangleShape panel_batalla({ 760.f, 180.f });
            panel_batalla.setPosition({ 20.f, 600.f });
            panel_batalla.setFillColor(sf::Color(0, 0, 0, 220));
            panel_batalla.setOutlineColor(sf::Color(180, 180, 180));
            panel_batalla.setOutlineThickness(3.f);
            window.draw(panel_batalla);

            sf::Text texto_mensaje(alagard);
            texto_mensaje.setString(mensaje_batalla);
            texto_mensaje.setCharacterSize(20);
            texto_mensaje.setFillColor(sf::Color::Yellow);
            texto_mensaje.setPosition({ 40.f, 615.f });
            window.draw(texto_mensaje);

            if (fase_actual == fase_batalla::espera_input) {
                sf::Text texto_opciones(alagard);
                texto_opciones.setString("1) Atacar     2) Usar Pocion     3) Defender     4) Huir");
                texto_opciones.setCharacterSize(22);
                texto_opciones.setFillColor(sf::Color::White);
                texto_opciones.setPosition({ 40.f, 720.f });
                window.draw(texto_opciones);
            }
            else if (fase_actual == fase_batalla::ganada) {
                sf::Text texto_resultado(alagard);
                texto_resultado.setString("VICTORIA - Partida guardada automaticamente");
                texto_resultado.setCharacterSize(22);
                texto_resultado.setFillColor(sf::Color(60, 220, 60));
                texto_resultado.setPosition({ 40.f, 720.f });
                window.draw(texto_resultado);
            }
            else if (fase_actual == fase_batalla::perdida) {
                sf::Text texto_resultado(alagard);
                texto_resultado.setString("DERROTA - ENTER para volver al menu");
                texto_resultado.setCharacterSize(22);
                texto_resultado.setFillColor(sf::Color(220, 60, 60));
                texto_resultado.setPosition({ 40.f, 720.f });
                window.draw(texto_resultado);
            }
            else if (fase_actual == fase_batalla::huida) {
                sf::Text texto_resultado(alagard);
                texto_resultado.setString("Escapaste con vida - ENTER para continuar");
                texto_resultado.setCharacterSize(22);
                texto_resultado.setFillColor(sf::Color::Cyan);
                texto_resultado.setPosition({ 40.f, 720.f });
                window.draw(texto_resultado);
            }

            // === CARTEL GRANDE DE VICTORIA FINAL (TRAS VENCER AL BOSS) ===
            if (fase_actual == fase_batalla::victoria_final) {
                const float PI = 3.14159265f;
                float t_v = reloj_anim_batalla.getElapsedTime().asSeconds();

                // Velo dorado oscuro para resaltar el cartel
                sf::RectangleShape velo_victoria({ 800.f, 800.f });
                velo_victoria.setFillColor(sf::Color(0, 0, 0, 200));
                window.draw(velo_victoria);

                // Marco grande centrado con borde dorado pulsante
                float pulso = (std::sin(t_v * 3.0f) + 1.f) * 0.5f;
                std::uint8_t intensidad = static_cast<std::uint8_t>(180 + pulso * 75);

                sf::RectangleShape marco_victoria({ 700.f, 460.f });
                marco_victoria.setOrigin({ 350.f, 230.f });
                marco_victoria.setPosition({ 400.f, 400.f });
                marco_victoria.setFillColor(sf::Color(20, 15, 5, 240));
                marco_victoria.setOutlineColor(sf::Color(intensidad, static_cast<std::uint8_t>(intensidad * 0.78f), 30));
                marco_victoria.setOutlineThickness(5.f);
                window.draw(marco_victoria);

                // Decoracion superior
                sf::RectangleShape barra_top({ 660.f, 6.f });
                barra_top.setOrigin({ 330.f, 3.f });
                barra_top.setPosition({ 400.f, 215.f });
                barra_top.setFillColor(sf::Color(212, 175, 55));
                window.draw(barra_top);

                sf::RectangleShape barra_bot({ 660.f, 6.f });
                barra_bot.setOrigin({ 330.f, 3.f });
                barra_bot.setPosition({ 400.f, 585.f });
                barra_bot.setFillColor(sf::Color(212, 175, 55));
                window.draw(barra_bot);

                // Titulo "VICTORIA!" con efecto de aparicion
                float prog_titulo = std::min(1.f, t_v / 0.6f);
                std::uint8_t alpha_t = static_cast<std::uint8_t>(prog_titulo * 255.f);

                sf::Text titulo_victoria(alagard);
                titulo_victoria.setString("VICTORIA");
                titulo_victoria.setCharacterSize(82);
                titulo_victoria.setFillColor(sf::Color(255, 215, 0, alpha_t));
                titulo_victoria.setOutlineColor(sf::Color(0, 0, 0, alpha_t));
                titulo_victoria.setOutlineThickness(5.f);
                {
                    auto b = titulo_victoria.getLocalBounds();
                    titulo_victoria.setOrigin({ b.size.x / 2.f, 0.f });
                }
                titulo_victoria.setPosition({ 400.f, 240.f });
                window.draw(titulo_victoria);

                // Mensaje principal de felicitacion
                if (t_v >= 0.6f) {
                    float prog_msg = std::min(1.f, (t_v - 0.6f) / 0.8f);
                    std::uint8_t alpha_m = static_cast<std::uint8_t>(prog_msg * 255.f);

                    sf::Text felicitacion(alagard);
                    felicitacion.setString("Lograste ganarle al Guardian de la");
                    felicitacion.setCharacterSize(26);
                    felicitacion.setFillColor(sf::Color(255, 255, 255, alpha_m));
                    felicitacion.setOutlineColor(sf::Color(0, 0, 0, alpha_m));
                    felicitacion.setOutlineThickness(2.f);
                    {
                        auto b = felicitacion.getLocalBounds();
                        felicitacion.setOrigin({ b.size.x / 2.f, 0.f });
                    }
                    felicitacion.setPosition({ 400.f, 360.f });
                    window.draw(felicitacion);

                    sf::Text felicitacion2(alagard);
                    felicitacion2.setString("Mazmorra y saliste con vida exitosamente!");
                    felicitacion2.setCharacterSize(26);
                    felicitacion2.setFillColor(sf::Color(255, 255, 255, alpha_m));
                    felicitacion2.setOutlineColor(sf::Color(0, 0, 0, alpha_m));
                    felicitacion2.setOutlineThickness(2.f);
                    {
                        auto b = felicitacion2.getLocalBounds();
                        felicitacion2.setOrigin({ b.size.x / 2.f, 0.f });
                    }
                    felicitacion2.setPosition({ 400.f, 400.f });
                    window.draw(felicitacion2);
                }

                // Resumen de recompensas (aparece despues del mensaje)
                if (t_v >= 1.4f) {
                    float prog_rec = std::min(1.f, (t_v - 1.4f) / 0.6f);
                    std::uint8_t alpha_r = static_cast<std::uint8_t>(prog_rec * 255.f);

                    sf::Text texto_recompensa(alagard);
                    texto_recompensa.setString(mensaje_batalla);
                    texto_recompensa.setCharacterSize(24);
                    texto_recompensa.setFillColor(sf::Color(255, 215, 0, alpha_r));
                    texto_recompensa.setOutlineColor(sf::Color(0, 0, 0, alpha_r));
                    texto_recompensa.setOutlineThickness(2.f);
                    {
                        auto b = texto_recompensa.getLocalBounds();
                        texto_recompensa.setOrigin({ b.size.x / 2.f, 0.f });
                    }
                    texto_recompensa.setPosition({ 400.f, 470.f });
                    window.draw(texto_recompensa);

                    sf::Text subtitulo(alagard);
                    subtitulo.setString("Un verdadero heroe de la mazmorra");
                    subtitulo.setCharacterSize(20);
                    subtitulo.setFillColor(sf::Color(200, 200, 200, alpha_r));
                    {
                        auto b = subtitulo.getLocalBounds();
                        subtitulo.setOrigin({ b.size.x / 2.f, 0.f });
                    }
                    subtitulo.setPosition({ 400.f, 510.f });
                    window.draw(subtitulo);
                }

                // Hint final para volver al menu
                if (t_v >= 2.0f) {
                    float alpha_hint = (std::sin(t_v * 2.5f) + 1.f) * 0.5f * 255.f;
                    sf::Text hint(alagard);
                    hint.setString("Presiona ENTER para volver al menu");
                    hint.setCharacterSize(20);
                    hint.setFillColor(sf::Color(255, 255, 255, static_cast<std::uint8_t>(alpha_hint)));
                    {
                        auto b = hint.getLocalBounds();
                        hint.setOrigin({ b.size.x / 2.f, 0.f });
                    }
                    hint.setPosition({ 400.f, 560.f });
                    window.draw(hint);
                }
            }

            window.display();
            continue;
        }

        window.draw(sprite_fondo);

        if (estado_actual == menu_principal) {
            window.draw(texto_titulo);
            window.draw(panel_menu);
            dibujarmenu(window, opciones_menu);
        }
        else {
            if (estado_actual == jugando || estado_actual == en_tienda || estado_actual == en_inventario) {
                sf::View camara_juego(sf::FloatRect({ 0.f, 0.f }, { 2540.f, 2540.f }));
                camara_juego.setCenter(sf::Vector2f(1270.f, 1270.f));
                window.setView(camara_juego);
                dibujarmapa(window, matriz_fondo, matriz_entidades, tex_suelo, tex_pared_arriba, tex_pared_abajo, tex_pared_izq, tex_pared_der, tex_prota, tex_boss, tex_enemigo, tex_mercader, tex_cofre, tex_salida);
                window.setView(window.getDefaultView());
            }

            if (estado_actual != jugando) {
                window.draw(panel_oscuro);
            }

            if (estado_actual == reglas) {
                window.draw(texto_reglas);
            }
            else if (estado_actual == controles) {
                window.draw(texto_controles);
            }
            else if (estado_actual == creditos) {
                window.draw(texto_creditos);
            }
            else if (estado_actual == jugando) {
                if (aviso_puerta) {
                    sf::RectangleShape fondo_aviso({ 650.0f, 50.0f });
                    fondo_aviso.setPosition({ 75.0f, 50.0f });
                    fondo_aviso.setFillColor(sf::Color(0, 0, 0, 220));
                    fondo_aviso.setOutlineColor(sf::Color::Red);
                    fondo_aviso.setOutlineThickness(2.0f);
                    window.draw(fondo_aviso);

                    sf::Text texto_aviso(alagard);
                    texto_aviso.setString("! La puerta esta sellada ! Derrota a todos los enemigos.");
                    texto_aviso.setCharacterSize(22);
                    texto_aviso.setPosition({ 100.0f, 62.0f });
                    texto_aviso.setFillColor(sf::Color::Red);
                    window.draw(texto_aviso);
                }

                if (aviso_boss) {
                    // Advertencia central: hay un boss en este nivel, juntar pociones
                    sf::RectangleShape fondo_boss({ 620.0f, 240.0f });
                    fondo_boss.setOrigin({ 310.0f, 120.0f });
                    fondo_boss.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
                    fondo_boss.setFillColor(sf::Color(20, 5, 5, 235));
                    fondo_boss.setOutlineColor(sf::Color(220, 60, 60));
                    fondo_boss.setOutlineThickness(3.0f);
                    window.draw(fondo_boss);

                    sf::Text titulo_boss(alagard);
                    titulo_boss.setString("!!! ADVERTENCIA !!!");
                    titulo_boss.setCharacterSize(32);
                    titulo_boss.setFillColor(sf::Color(220, 60, 60));
                    titulo_boss.setOutlineColor(sf::Color::Black);
                    titulo_boss.setOutlineThickness(2.0f);
                    {
                        auto b = titulo_boss.getLocalBounds();
                        titulo_boss.setOrigin({ b.size.x / 2.0f, 0.0f });
                    }
                    titulo_boss.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f - 100.0f });
                    window.draw(titulo_boss);

                    sf::Text msg_boss(alagard);
                    msg_boss.setString("El Guardian de la Mazmorra te espera!");
                    msg_boss.setCharacterSize(22);
                    msg_boss.setFillColor(sf::Color::White);
                    msg_boss.setOutlineColor(sf::Color::Black);
                    msg_boss.setOutlineThickness(2.0f);
                    {
                        auto b = msg_boss.getLocalBounds();
                        msg_boss.setOrigin({ b.size.x / 2.0f, 0.0f });
                    }
                    msg_boss.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f - 50.0f });
                    window.draw(msg_boss);

                    sf::Text consejo_boss(alagard);
                    consejo_boss.setString("Asegurate de guardar pociones suficientes\npara sobrevivir la batalla final.");
                    consejo_boss.setCharacterSize(20);
                    consejo_boss.setFillColor(sf::Color(255, 215, 0));
                    consejo_boss.setOutlineColor(sf::Color::Black);
                    consejo_boss.setOutlineThickness(2.0f);
                    consejo_boss.setLineSpacing(1.2f);
                    {
                        auto b = consejo_boss.getLocalBounds();
                        consejo_boss.setOrigin({ b.size.x / 2.0f, 0.0f });
                    }
                    consejo_boss.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f - 5.0f });
                    window.draw(consejo_boss);

                    sf::Text hint_boss(alagard);
                    hint_boss.setString("(Movete con WASD para continuar)");
                    hint_boss.setCharacterSize(16);
                    hint_boss.setFillColor(sf::Color(200, 200, 200));
                    {
                        auto b = hint_boss.getLocalBounds();
                        hint_boss.setOrigin({ b.size.x / 2.0f, 0.0f });
                    }
                    hint_boss.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f + 90.0f });
                    window.draw(hint_boss);
                }

                if (aviso_cofre) {
                    // Cartel central con las recompensas aleatorias del cofre
                    sf::RectangleShape fondo_cofre({ 460.0f, 260.0f });
                    fondo_cofre.setPosition({ 170.0f, 250.0f });
                    fondo_cofre.setFillColor(sf::Color(20, 20, 20, 230));
                    fondo_cofre.setOutlineColor(sf::Color(212, 175, 55));
                    fondo_cofre.setOutlineThickness(3.0f);
                    window.draw(fondo_cofre);

                    sf::Text titulo_cofre(alagard);
                    titulo_cofre.setString("=== RECOMPENSAS ===");
                    titulo_cofre.setCharacterSize(26);
                    titulo_cofre.setFillColor(sf::Color(212, 175, 55));
                    titulo_cofre.setOutlineColor(sf::Color::Black);
                    titulo_cofre.setOutlineThickness(2.0f);
                    {
                        auto bounds = titulo_cofre.getLocalBounds();
                        titulo_cofre.setOrigin({ bounds.size.x / 2.0f, 0.0f });
                    }
                    titulo_cofre.setPosition({ window.getSize().x / 2.0f, 265.0f });
                    window.draw(titulo_cofre);

                    sf::Text texto_cofre(alagard);
                    texto_cofre.setString(mensaje_cofre);
                    texto_cofre.setCharacterSize(20);
                    texto_cofre.setFillColor(sf::Color::White);
                    texto_cofre.setLineSpacing(1.1f);
                    texto_cofre.setPosition({ 200.0f, 305.0f });
                    window.draw(texto_cofre);

                    sf::Text texto_continuar(alagard);
                    texto_continuar.setString("(Movete con WASD para cerrar)");
                    texto_continuar.setCharacterSize(16);
                    texto_continuar.setFillColor(sf::Color(200, 200, 200));
                    {
                        auto bounds = texto_continuar.getLocalBounds();
                        texto_continuar.setOrigin({ bounds.size.x / 2.0f, 0.0f });
                    }
                    texto_continuar.setPosition({ window.getSize().x / 2.0f, 480.0f });
                    window.draw(texto_continuar);
                }

                if (en_pausa) {
                    window.draw(fondo_pausa);
                    window.draw(texto_pausa_titulo);
                    for (const auto& texto_opcion : opciones_pausa) {
                        window.draw(texto_opcion);
                    }
                }
            }
            else if (estado_actual == cargar) {
                sf::Text titulo_cargar(alagard);
                titulo_cargar.setString("SELECCIONAR PARTIDA");
                titulo_cargar.setCharacterSize(35);
                {
                    auto bounds = titulo_cargar.getLocalBounds();
                    titulo_cargar.setOrigin({ bounds.size.x / 2.0f, 0.0f });
                }
                titulo_cargar.setPosition({ window.getSize().x / 2.0f, 80.0f });
                titulo_cargar.setFillColor(sf::Color::Yellow);
                window.draw(titulo_cargar);

                if (opciones_carga.empty()) {
                    sf::Text sin_partidas(alagard);
                    sin_partidas.setString("No hay partidas guardadas");
                    sin_partidas.setCharacterSize(24);
                    {
                        auto bounds = sin_partidas.getLocalBounds();
                        sin_partidas.setOrigin({ bounds.size.x / 2.0f, 0.0f });
                    }
                    sin_partidas.setPosition({ window.getSize().x / 2.0f, 200.0f });
                    sin_partidas.setFillColor(sf::Color::White);
                    window.draw(sin_partidas);

                    sf::Text volver(alagard);
                    volver.setString("ENTER o ESC para volver");
                    volver.setCharacterSize(18);
                    {
                        auto bounds = volver.getLocalBounds();
                        volver.setOrigin({ bounds.size.x / 2.0f, 0.0f });
                    }
                    volver.setPosition({ window.getSize().x / 2.0f, 250.0f });
                    volver.setFillColor(sf::Color(200, 200, 200));
                    window.draw(volver);
                }
                else {
                    for (const auto& opcion : opciones_carga) {
                        window.draw(opcion);
                    }
                }
            }
            else if (estado_actual == confirmar_guardado) {
                window.draw(fondo_confirmacion);
                window.draw(texto_confirmacion_titulo);
                for (const auto& opcion : opciones_confirmacion) {
                    window.draw(opcion);
                }
            }
            else if (estado_actual == aviso_guardado) {
                window.draw(fondo_aviso_guardado);
                window.draw(linea_deco_guardado);
                window.draw(texto_guardado_titulo);
                window.draw(texto_guardado_subtitulo);
            }
            else if (estado_actual == en_inventario) {
                sf::Text titulo_inv(alagard);
                titulo_inv.setString("=== ESTADO Y MOCHILA ===");
                titulo_inv.setCharacterSize(35);
                titulo_inv.setPosition({ 180.0f, 60.0f });
                titulo_inv.setFillColor(sf::Color::Yellow);
                window.draw(titulo_inv);

                // CALCULAMOS EL TOPE DE VIDA PARA MOSTRARLO EN PANTALLA
                int vida_tope = 100 + paolo.defensa;

                sf::Text stats_texto(alagard);
                stats_texto.setString(
                    "Oro: " + std::to_string(paolo.oro) + "\n\n" +
                    "Vida: " + std::to_string(paolo.vida) + " / " + std::to_string(vida_tope) + "\n\n" +
                    "Ataque: " + std::to_string(paolo.ataque) + "\n\n" +
                    "Bonus Salud: +" + std::to_string(paolo.defensa) + "\n\n\n" +
                    "Arma:\n" + (paolo.arma_equipada == "" ? "Ninguna" : paolo.arma_equipada) + "\n\n" +
                    "Armadura:\n" + (paolo.armadura_equipada == "" ? "Ninguna" : paolo.armadura_equipada)
                );
                stats_texto.setCharacterSize(22);
                stats_texto.setPosition({ 80.0f, 150.0f });
                stats_texto.setFillColor(sf::Color::Cyan);
                window.draw(stats_texto);

                // Agrupamos items repetidos (el inventario esta ordenado, asi que items iguales son adyacentes)
                std::vector<std::pair<std::string, int>> grupos_inv;
                for (int i = 0; i < paolo.cant_items; i++) {
                    if (!grupos_inv.empty() && grupos_inv.back().first == paolo.inventario[i]) {
                        grupos_inv.back().second++;
                    }
                    else {
                        grupos_inv.push_back({ paolo.inventario[i], 1 });
                    }
                }

                // Aseguramos que el cursor no se salga del rango de grupos
                if (cursor_inventario >= static_cast<int>(grupos_inv.size())) {
                    cursor_inventario = static_cast<int>(grupos_inv.size()) - 1;
                }
                if (cursor_inventario < 0) cursor_inventario = 0;

                for (int i = 0; i < static_cast<int>(grupos_inv.size()) && i < 10; i++) {
                    std::string texto_item = grupos_inv[i].first;
                    if (grupos_inv[i].second > 1) {
                        texto_item += " x " + std::to_string(grupos_inv[i].second);
                    }

                    sf::Text item_texto(alagard);
                    item_texto.setCharacterSize(22);
                    item_texto.setPosition({ 450.0f, 150.0f + (i * 35.0f) });

                    if (i == cursor_inventario) {
                        item_texto.setFillColor(sf::Color::Red);
                        item_texto.setString("> " + texto_item + " <");
                    }
                    else {
                        item_texto.setFillColor(sf::Color::White);
                        item_texto.setString(texto_item);
                    }
                    window.draw(item_texto);
                }

                sf::Text consejo_inv(alagard);
                consejo_inv.setString("Tip: guarda pociones para el Boss final!");
                consejo_inv.setCharacterSize(16);
                consejo_inv.setFillColor(sf::Color(255, 215, 0));
                consejo_inv.setOutlineColor(sf::Color::Black);
                consejo_inv.setOutlineThickness(1.0f);
                consejo_inv.setPosition({ 60.0f, 490.0f });
                window.draw(consejo_inv);

                sf::Text controles_inv(alagard);
                controles_inv.setString("W/S = Mover | ENTER = Equipar / Usar | 6 = Ordenar | ESC / 5 = Salir");
                controles_inv.setCharacterSize(18);
                controles_inv.setPosition({ 60.0f, 520.0f });
                controles_inv.setFillColor(sf::Color(200, 200, 200));
                window.draw(controles_inv);
            }
            else if (estado_actual == en_tienda) {

                sf::Text titulo_tienda(alagard);
                titulo_tienda.setString("COMPRAR");
                titulo_tienda.setCharacterSize(35);
                titulo_tienda.setPosition({ 150.0f, 60.0f });
                titulo_tienda.setFillColor(en_modo_compra ? sf::Color::Yellow : sf::Color(100, 100, 100));
                window.draw(titulo_tienda);

                sf::Text titulo_mochila(alagard);
                titulo_mochila.setString("VENDER");
                titulo_mochila.setCharacterSize(35);
                titulo_mochila.setPosition({ 500.0f, 60.0f });
                titulo_mochila.setFillColor(!en_modo_compra ? sf::Color::Yellow : sf::Color(100, 100, 100));
                window.draw(titulo_mochila);

                sf::Text oro_texto(alagard);
                oro_texto.setString("Tu Oro: " + std::to_string(paolo.oro));
                oro_texto.setCharacterSize(25);
                oro_texto.setPosition({ 320.0f, 440.0f });
                oro_texto.setFillColor(sf::Color::White);
                window.draw(oro_texto);

                for (int i = 0; i < 6; i++) {
                    sf::Text item_texto(alagard);
                    item_texto.setString(vendedor.catalogo[i] + " (" + std::to_string(vendedor.precios[i]) + ")");
                    item_texto.setCharacterSize(20);
                    item_texto.setPosition({ 60.0f, 130.0f + (i * 35.0f) });

                    if (en_modo_compra && i == cursor_tienda) {
                        item_texto.setFillColor(sf::Color::Red);
                    }
                    else {
                        item_texto.setFillColor(sf::Color::White);
                    }
                    window.draw(item_texto);
                }

                for (int i = 0; i < paolo.cant_items; i++) {
                    if (i < 8) {
                        sf::Text item_texto(alagard);
                        int valor_venta = obtenerprecioventa(paolo.inventario[i]);
                        item_texto.setString(paolo.inventario[i] + " (+" + std::to_string(valor_venta) + ")");
                        item_texto.setCharacterSize(20);
                        item_texto.setPosition({ 450.0f, 130.0f + (i * 35.0f) });

                        if (!en_modo_compra && i == cursor_inventario) {
                            item_texto.setFillColor(sf::Color::Red);
                        }
                        else {
                            item_texto.setFillColor(sf::Color::White);
                        }
                        window.draw(item_texto);
                    }
                }

                sf::Text consejo_tienda(alagard);
                consejo_tienda.setString("Consejo: guarda pociones para enfrentar al Boss final!");
                consejo_tienda.setCharacterSize(18);
                consejo_tienda.setFillColor(sf::Color(255, 215, 0));
                consejo_tienda.setOutlineColor(sf::Color::Black);
                consejo_tienda.setOutlineThickness(1.0f);
                {
                    auto b = consejo_tienda.getLocalBounds();
                    consejo_tienda.setOrigin({ b.size.x / 2.0f, 0.0f });
                }
                consejo_tienda.setPosition({ window.getSize().x / 2.0f, 470.0f });
                window.draw(consejo_tienda);

                sf::Text controles_tienda(alagard);
                controles_tienda.setString("A/D = Cambiar Panel | W/S = Mover | ENTER = Confirmar | ESC = Salir");
                controles_tienda.setCharacterSize(18);
                controles_tienda.setPosition({ 80.0f, 500.0f });
                controles_tienda.setFillColor(sf::Color(200, 200, 200));
                window.draw(controles_tienda);
            }
        }

        window.display();
    }

    return 0;
}

void inicializarmenu(std::vector<sf::Text>& opciones, const sf::Font& fuente, float ancho, float alto) {
    std::vector<std::string> textos = { "Jugar", "Cargar Partida", "Controles", "Reglas", "Creditos", "Salir" };

    for (int i = 0; i < textos.size(); i++) {
        sf::Text texto(fuente);
        texto.setString(textos[i]);
        texto.setCharacterSize(30);

        if (i == 0) texto.setFillColor(sf::Color::Red);
        else texto.setFillColor(sf::Color::White);

        auto bounds = texto.getLocalBounds();
        texto.setOrigin({ bounds.size.x / 2.0f, 0.0f });
        texto.setPosition({ ancho / 2.0f, 230.0f + (i * 45.0f) });
        opciones.push_back(texto);
    }
}

void moverarriba(int& item_seleccionado, std::vector<sf::Text>& opciones) {
    if (item_seleccionado - 1 >= 0) {
        opciones[item_seleccionado].setFillColor(sf::Color::White);
        item_seleccionado--;
        opciones[item_seleccionado].setFillColor(sf::Color::Red);
    }
}

void moverabajo(int& item_seleccionado, std::vector<sf::Text>& opciones) {
    if (item_seleccionado + 1 < opciones.size()) {
        opciones[item_seleccionado].setFillColor(sf::Color::White);
        item_seleccionado++;
        opciones[item_seleccionado].setFillColor(sf::Color::Red);
    }
}

void dibujarmenu(sf::RenderWindow& window, const std::vector<sf::Text>& opciones) {
    for (const auto& texto : opciones) {
        window.draw(texto);
    }
}