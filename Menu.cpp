#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <optional>
#include <algorithm>
#include <sstream>
#include "Menu.h"
#include "Mapa.h"
#include "funciones.h"
#include "structs.h"

enum estado_pantalla { menu_principal, jugando, cargar, controles, reglas, creditos, en_tienda, en_batalla, en_inventario, confirmar_guardado, aviso_guardado };

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
        "        (Presiona ENTER para volver al menu)");
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

    sf::Texture tex_suelo, tex_pared_arriba, tex_pared_abajo, tex_pared_izq, tex_pared_der, tex_prota, tex_boss, tex_enemigo, tex_mercader, tex_cofre, tex_salida;
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

    personaje paolo;
    protagonista(paolo);

    mercader vendedor;
    inicializarmercader(vendedor);
    ordenarmercader(vendedor.catalogo, vendedor.precios, 6);

    int cursor_tienda = 0;
    int cursor_inventario = 0;
    bool en_modo_compra = true;
    bool aviso_puerta = false;

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

    sf::RectangleShape fondo_aviso_guardado({ 520.0f, 160.0f });
    fondo_aviso_guardado.setFillColor(sf::Color(0, 0, 0, 230));
    fondo_aviso_guardado.setPosition({ 140.0f, 320.0f });
    fondo_aviso_guardado.setOutlineColor(sf::Color::White);
    fondo_aviso_guardado.setOutlineThickness(2.0f);

    sf::Text texto_guardado_titulo(alagard);
    texto_guardado_titulo.setString("Partida guardada correctamente");
    texto_guardado_titulo.setCharacterSize(28);
    texto_guardado_titulo.setFillColor(sf::Color::Green);
    texto_guardado_titulo.setPosition({ 260.0f, 350.0f });

    sf::Text texto_guardado_subtitulo(alagard);
    texto_guardado_subtitulo.setString("ENTER para continuar");
    texto_guardado_subtitulo.setCharacterSize(18);
    texto_guardado_subtitulo.setFillColor(sf::Color(200, 200, 200));
    texto_guardado_subtitulo.setPosition({ 250.0f, 390.0f });

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
                                std::ostringstream linea;
                                linea << (i + 1) << ") " << registro.pj.name
                                    << " - Nivel " << registro.pj.nivel_actual
                                    << " - Oro " << registro.pj.oro;
                                sf::Text texto(alagard);
                                texto.setString(linea.str());
                                texto.setCharacterSize(24);
                                texto.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
                                auto bounds = texto.getLocalBounds();
                                texto.setOrigin({ bounds.size.x / 2.0f, 0.0f });
                                texto.setPosition({ window.getSize().x / 2.0f, 180.0f + (i * 35.0f) });
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
                    if (key_pressed->code == sf::Keyboard::Key::Enter || key_pressed->code == sf::Keyboard::Key::Escape) {
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
                            case 2: // Ver Controles
                                estado_actual = controles;
                                en_pausa = false;
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
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::S) {
                            moverpj(paolo, 'S', matriz_fondo, matriz_entidades);
                            aviso_puerta = false;
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::A) {
                            moverpj(paolo, 'A', matriz_fondo, matriz_entidades);
                            aviso_puerta = false;
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::D) {
                            moverpj(paolo, 'D', matriz_fondo, matriz_entidades);
                            aviso_puerta = false;
                        }
                        else if (key_pressed->code == sf::Keyboard::Key::E) {
                            char resultado = interactuar(paolo, matriz_entidades, matriz_fondo);

                            if (resultado == 'S') {
                                paolo.nivel_actual = paolo.nivel_actual + 1;
                                cargarnivel(paolo.nivel_actual, matriz_fondo, matriz_entidades);
                                paolo.posicion_x = 1;
                                paolo.posicion_y = 1;
                                aviso_puerta = false;
                            }
                            else if (resultado == 'L') {
                                aviso_puerta = true;
                            }
                            else if (resultado == 'M') {
                                estado_actual = en_tienda;
                                cursor_tienda = 0;
                                cursor_inventario = 0;
                                en_modo_compra = true;
                                aviso_puerta = false;
                            }
                            else if (resultado == 'E' || resultado == 'B') {
                                estado_actual = en_batalla;
                                aviso_puerta = false;
                            }
                        }
                    }
                }
                else if (estado_actual == en_inventario) {
                    if (key_pressed->code == sf::Keyboard::Key::Escape || key_pressed->code == sf::Keyboard::Key::Num5) {
                        estado_actual = jugando;
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::W || key_pressed->code == sf::Keyboard::Key::Up) {
                        if (cursor_inventario > 0) cursor_inventario--;
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::S || key_pressed->code == sf::Keyboard::Key::Down) {
                        if (cursor_inventario < paolo.cant_items - 1) cursor_inventario++;
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::Enter) {
                        if (paolo.cant_items > 0) {
                            string item_sel = paolo.inventario[cursor_inventario];

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

                                for (int i = cursor_inventario; i < paolo.cant_items - 1; i++) {
                                    paolo.inventario[i] = paolo.inventario[i + 1];
                                }
                                paolo.cant_items--;

                                if (cursor_inventario >= paolo.cant_items && cursor_inventario > 0) {
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
            }
        }

        window.clear();
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

                for (int i = 0; i < paolo.cant_items; i++) {
                    if (i < 10) {
                        sf::Text item_texto(alagard);
                        item_texto.setString(paolo.inventario[i]);
                        item_texto.setCharacterSize(22);
                        item_texto.setPosition({ 450.0f, 150.0f + (i * 35.0f) });

                        if (i == cursor_inventario) {
                            item_texto.setFillColor(sf::Color::Red);
                            item_texto.setString("> " + paolo.inventario[i] + " <");
                        }
                        else {
                            item_texto.setFillColor(sf::Color::White);
                        }
                        window.draw(item_texto);
                    }
                }

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