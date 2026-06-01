#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <optional>
#include "Menu.h"
#include "Mapa.h"
#include "funciones.h"
#include "structs.h"

enum estado_pantalla { menu_principal, jugando, cargar, controles, reglas, creditos, en_tienda, en_batalla, en_inventario };

int iniciarjuego() {
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Dungeon Survival");
    window.setFramerateLimit(60);

    int item_seleccionado = 0;
    std::vector<sf::Text> opciones_menu;

    sf::Font alagard;
    alagard.openFromFile("medieval.ttf");

    sf::Texture textura_fondo;
    textura_fondo.loadFromFile("fondo.png");
    sf::Sprite sprite_fondo(textura_fondo);

    inicializarmenu(opciones_menu, alagard, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

    sf::Text texto_titulo(alagard);
    texto_titulo.setString("DUNGEON SURVIVAL");
    texto_titulo.setCharacterSize(65);
    texto_titulo.setFillColor(sf::Color::White);
    texto_titulo.setOutlineThickness(4.0f);
    texto_titulo.setOutlineColor(sf::Color::Black);
    texto_titulo.setPosition({ (window.getSize().x / 2.0f) - 280.0f, 40.0f });

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

    estado_pantalla estado_actual = menu_principal;

    string matriz_fondo[max_filas][max_columnas];
    string matriz_entidades[max_filas][max_columnas];
    cargarnivel(1, matriz_fondo, matriz_entidades);

    sf::Texture tex_suelo, tex_pared_arriba, tex_pared_abajo, tex_pared_izq, tex_pared_der, tex_prota, tex_boss, tex_enemigo, tex_mercader, tex_cofre, tex_salida;
    tex_suelo.loadFromFile("suelo.jpg");
    tex_pared_izq.loadFromFile("customladrillo.png");
    tex_pared_abajo.loadFromFile("customladrillo.png");
    tex_pared_der.loadFromFile("customladrillo.png");
    tex_pared_arriba.loadFromFile("customladrillo.png");
    tex_prota.loadFromFile("prota_01.png");
    tex_enemigo.loadFromFile("Enemigo.png");
    tex_mercader.loadFromFile("mercader.png");
    tex_cofre.loadFromFile("cofre.png");
    tex_salida.loadFromFile("salida.png");
    tex_boss.loadFromFile("boss-01.png");

    personaje paolo;
    protagonista(paolo);

    mercader vendedor;
    inicializarmercader(vendedor);
    ordenarmercader(vendedor.catalogo, vendedor.precios, 6);

    int cursor_tienda = 0;
    int cursor_inventario = 0;
    bool en_modo_compra = true;
    bool aviso_puerta = false;

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
                        case 1: std::cout << "Aqui ira Cargar Partida..." << std::endl; break;
                        case 2: estado_actual = controles; break;
                        case 3: estado_actual = reglas; break;
                        case 4: estado_actual = creditos; break;
                        case 5: window.close(); break;
                        }
                    }
                }
                else if (estado_actual == reglas || estado_actual == controles || estado_actual == creditos) {
                    if (key_pressed->code == sf::Keyboard::Key::Enter || key_pressed->code == sf::Keyboard::Key::Escape) {
                        estado_actual = menu_principal;
                    }
                }
                else if (estado_actual == jugando) {
                    if (key_pressed->code == sf::Keyboard::Key::Num9 || key_pressed->code == sf::Keyboard::Key::Escape) {
                        estado_actual = menu_principal;
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::Num5) {
                        estado_actual = en_inventario;
                        cursor_inventario = 0;
                    }
                    else if (key_pressed->code == sf::Keyboard::Key::Num6) {
                        ordenarburbuja(paolo.inventario, paolo.cant_items);
                        std::cout << "Inventario Ordenado!" << std::endl;
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

        texto.setPosition({ (ancho / 2.0f) - 80.0f, 230.0f + (i * 45.0f) });
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