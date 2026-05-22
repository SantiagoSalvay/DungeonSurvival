#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <optional>
#include "Menu.h"

enum EstadoPantalla { MENU_PRINCIPAL, JUGANDO, CARGAR, CONTROLES, REGLAS, CREDITOS };

int iniciarJuego() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Dungeon Survival");
    window.setFramerateLimit(60);

    int itemSeleccionado = 0;
    std::vector<sf::Text> opcionesMenu;

    sf::Font alagard;
    if (!alagard.openFromFile("medieval.ttf")) {
        std::cout << "ERROR: No se pudo cargar medieval.ttf. Revisa el nombre y la carpeta." << std::endl;
        return -1;
    }

    sf::Texture texturaFondo;
    if (!texturaFondo.loadFromFile("fondo.png")) {
        std::cout << "ERROR: No se pudo cargar fondo.png. Revisa el nombre y la ruta...\n";
    }
    sf::Sprite spriteFondo(texturaFondo);

    inicializarMenu(opcionesMenu, alagard, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

    sf::Text textoTitulo(alagard);
    textoTitulo.setString("DUNGEON SURVIVAL");
    textoTitulo.setCharacterSize(65);
    textoTitulo.setFillColor(sf::Color::White);
    textoTitulo.setOutlineThickness(4.0f);
    textoTitulo.setOutlineColor(sf::Color::Black);
    textoTitulo.setPosition({ (window.getSize().x / 2.0f) - 280.0f, 40.0f });

    sf::RectangleShape panelMenu({ 280.0f, 330.0f });
    panelMenu.setPosition({ 260.0f, 200.0f });
    panelMenu.setFillColor(sf::Color(20, 20, 20, 220));
    panelMenu.setOutlineColor(sf::Color(140, 140, 140));
    panelMenu.setOutlineThickness(3.0f);

    sf::RectangleShape panelOscuro({ 720.0f, 520.0f });
    panelOscuro.setPosition({ 40.0f, 40.0f });
    panelOscuro.setFillColor(sf::Color(0, 0, 0, 200));
    panelOscuro.setOutlineColor(sf::Color(139, 69, 19));
    panelOscuro.setOutlineThickness(3.0f);

    float spacingAmount = 1.6f;
    float outlineThickness = 2.0f;
    sf::Color outlineColor = sf::Color::Black;

    sf::Text textoReglas(alagard);
    textoReglas.setString("================= REGLAS =================\n\n"
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
    textoReglas.setCharacterSize(21);
    textoReglas.setPosition({ 60.0f, 60.0f });
    textoReglas.setFillColor(sf::Color::White);
    textoReglas.setLineSpacing(spacingAmount);
    textoReglas.setOutlineThickness(outlineThickness);
    textoReglas.setOutlineColor(outlineColor);

    sf::Text textoControles(alagard);
    textoControles.setString("============ MANUAL DE CONTROLES ============\n\n"
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
    textoControles.setCharacterSize(21);
    textoControles.setPosition({ 60.0f, 60.0f });
    textoControles.setFillColor(sf::Color::White);
    textoControles.setLineSpacing(spacingAmount);
    textoControles.setOutlineThickness(outlineThickness);
    textoControles.setOutlineColor(outlineColor);

    sf::Text textoCreditos(alagard);
    textoCreditos.setString("================ CREDITOS ================\n\n"
        " Proyecto Parcial 2 - Programacion I\n\n"
        " Desarrollado por:\n"
        "   - Ignacio Gonzalez\n"
        "   - Santiago Oviedo\n"
        "   - Santiago Salvay\n\n"
        " Profesora: Monica Liliana Nano\n"
        " Carrera: Ing. en Informatica / Telecomunicaciones\n\n"
        "        (Presiona ENTER para volver al menu)");
    textoCreditos.setCharacterSize(21);
    textoCreditos.setPosition({ 60.0f, 60.0f });
    textoCreditos.setFillColor(sf::Color::White);
    textoCreditos.setLineSpacing(spacingAmount);
    textoCreditos.setOutlineThickness(outlineThickness);
    textoCreditos.setOutlineColor(outlineColor);

    EstadoPantalla estadoActual = MENU_PRINCIPAL;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

                if (estadoActual == MENU_PRINCIPAL) {
                    if (keyPressed->code == sf::Keyboard::Key::W || keyPressed->code == sf::Keyboard::Key::Up) {
                        moverArriba(itemSeleccionado, opcionesMenu);
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::S || keyPressed->code == sf::Keyboard::Key::Down) {
                        moverAbajo(itemSeleccionado, opcionesMenu);
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::Enter) {
                        switch (itemSeleccionado) {
                        case 0: estadoActual = JUGANDO; break;
                        case 1: std::cout << "Aqui ira Cargar Partida..." << std::endl; break;
                        case 2: estadoActual = CONTROLES; break;
                        case 3: estadoActual = REGLAS; break;
                        case 4: estadoActual = CREDITOS; break;
                        case 5: window.close(); break;
                        }
                    }
                }
                else if (estadoActual == REGLAS || estadoActual == CONTROLES || estadoActual == CREDITOS) {
                    if (keyPressed->code == sf::Keyboard::Key::Enter || keyPressed->code == sf::Keyboard::Key::Escape) {
                        estadoActual = MENU_PRINCIPAL;
                    }
                }
                else if (estadoActual == JUGANDO) {
                    if (keyPressed->code == sf::Keyboard::Key::Num9 || keyPressed->code == sf::Keyboard::Key::Escape) {
                        estadoActual = MENU_PRINCIPAL;
                    }
                }
            }
        }

        window.clear();

        window.draw(spriteFondo);

        if (estadoActual == MENU_PRINCIPAL) {
            window.draw(textoTitulo);
            window.draw(panelMenu);
            dibujarMenu(window, opcionesMenu);
        }
        else {
            window.draw(panelOscuro);

            if (estadoActual == REGLAS) {
                window.draw(textoReglas);
            }
            else if (estadoActual == CONTROLES) {
                window.draw(textoControles);
            }
            else if (estadoActual == CREDITOS) {
                window.draw(textoCreditos);
            }
            else if (estadoActual == JUGANDO) {
                sf::Text textoJuego(alagard);
                textoJuego.setString("Explorando la mazmorra con Paolo...\n\n(Presiona 9 para salir al menu)");
                textoJuego.setCharacterSize(26);
                textoJuego.setPosition({ 200.0f, 250.0f });
                textoJuego.setFillColor(sf::Color::White);
                textoJuego.setOutlineThickness(2.0f);
                textoJuego.setOutlineColor(sf::Color::Black);
                window.draw(textoJuego);
            }
        }

        window.display();
    }

    return 0;
}

void inicializarMenu(std::vector<sf::Text>& opciones, const sf::Font& fuente, float ancho, float alto) {
    std::vector<std::string> textos = { "Jugar", "Cargar Partida", "Controles", "Reglas", "Creditos", "Salir" };

    for (int i = 0; i < textos.size(); i++) {
        sf::Text texto(fuente);
        texto.setString(textos[i]);
        texto.setCharacterSize(30);

        if (i == 0) {
            texto.setFillColor(sf::Color::Red);
        }
        else {
            texto.setFillColor(sf::Color::White);
        }

        texto.setPosition({ (ancho / 2.0f) - 80.0f, 230.0f + (i * 45.0f) });
        opciones.push_back(texto);
    }
}

void moverArriba(int& itemSeleccionado, std::vector<sf::Text>& opciones) {
    if (itemSeleccionado - 1 >= 0) {
        opciones[itemSeleccionado].setFillColor(sf::Color::White);
        itemSeleccionado--;
        opciones[itemSeleccionado].setFillColor(sf::Color::Red);
    }
}

void moverAbajo(int& itemSeleccionado, std::vector<sf::Text>& opciones) {
    if (itemSeleccionado + 1 < opciones.size()) {
        opciones[itemSeleccionado].setFillColor(sf::Color::White);
        itemSeleccionado++;
        opciones[itemSeleccionado].setFillColor(sf::Color::Red);
    }
}

void dibujarMenu(sf::RenderWindow& window, const std::vector<sf::Text>& opciones) {
    for (const auto& texto : opciones) {
        window.draw(texto);
    }
}