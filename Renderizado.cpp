#include "Renderizado.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdint>

// MAPA
using namespace std;

void dibujarmapa(
    sf::RenderWindow& ventana,
    string matriz_fondo[max_filas][max_columnas],
    string matriz_entidades[max_filas][max_columnas],
    sf::Texture& tex_suelo,
    sf::Texture& tex_pared_arriba, sf::Texture& tex_pared_abajo,
    sf::Texture& tex_pared_izq, sf::Texture& tex_pared_der,
    sf::Texture& tex_prota, sf::Texture& tex_boss, sf::Texture& tex_enemigo,
    sf::Texture& tex_mercader, sf::Texture& tex_cofre, sf::Texture& tex_salida) {

    sf::Sprite rectangulo(tex_suelo);

    for (int i = 0; i < max_filas; i++) {
        for (int j = 0; j < max_columnas; j++) {

            float pos_x = j * 254.f;
            float pos_y = i * 254.f;

            // Ya no hace falta rotar ni desfasar nada, lo dejamos limpito
            rectangulo.setOrigin(sf::Vector2f(0.f, 0.f));
            rectangulo.setRotation(sf::degrees(0.f));
            rectangulo.setPosition({ pos_x, pos_y });

            if (matriz_fondo[i][j] == "0") {
                rectangulo.setTexture(tex_suelo);
                ventana.draw(rectangulo);
            }

            else if (matriz_fondo[i][j] == "1") {
                // Paredes LATERALES (Izquierda o Derecha)
                if (j == 0) {
                    rectangulo.setTexture(tex_pared_izq);
                }
                else {
                    rectangulo.setTexture(tex_pared_der);
                }
                ventana.draw(rectangulo);
            }
            else if (matriz_fondo[i][j] == "2") {
                // Paredes SUPERIOR o INFERIOR (Arriba o Abajo)
                if (i == 0) {
                    rectangulo.setTexture(tex_pared_arriba);
                }
                else {
                    rectangulo.setTexture(tex_pared_abajo);
                }
                ventana.draw(rectangulo);
            }
            else if (matriz_fondo[i][j] == "S") {
                rectangulo.setTexture(tex_suelo);
                ventana.draw(rectangulo);
                rectangulo.setTexture(tex_salida);
                ventana.draw(rectangulo);
            }

            if (matriz_entidades[i][j] != "") {
                if (matriz_entidades[i][j] == "P") {
                    rectangulo.setTexture(tex_prota);
                }
                else if (matriz_entidades[i][j] == "E") {
                    rectangulo.setTexture(tex_enemigo);
                }
                else if (matriz_entidades[i][j] == "M") {
                    rectangulo.setTexture(tex_mercader);
                }
                else if (matriz_entidades[i][j] == "B") {
                    rectangulo.setTexture(tex_boss);
                }
                else if (matriz_entidades[i][j] == "C") {
                    rectangulo.setTexture(tex_cofre);
                }
                ventana.draw(rectangulo);
            }
        }
    }
}

// MENU
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

// PANTALLAS
void cargarRecursosVisuales(RecursosVisuales& r, sf::RenderWindow& window) {
    (void)r.alagard.openFromFile("medieval.ttf");

    (void)r.textura_fondo.loadFromFile("fondo.png");

    inicializarmenu(r.opciones_menu, r.alagard, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

    r.texto_titulo.setString("DUNGEON SURVIVAL");
    r.texto_titulo.setCharacterSize(65);
    r.texto_titulo.setFillColor(sf::Color::White);
    r.texto_titulo.setOutlineThickness(4.0f);
    r.texto_titulo.setOutlineColor(sf::Color::Black);
    {
        auto bounds = r.texto_titulo.getLocalBounds();
        r.texto_titulo.setOrigin({ bounds.size.x / 2.0f, 0.0f });
    }
    r.texto_titulo.setPosition({ window.getSize().x / 2.0f, 40.0f });

    r.panel_menu.setSize({ 280.0f, 330.0f });
    r.panel_menu.setPosition({ 260.0f, 200.0f });
    r.panel_menu.setFillColor(sf::Color(20, 20, 20, 220));
    r.panel_menu.setOutlineColor(sf::Color(140, 140, 140));
    r.panel_menu.setOutlineThickness(3.0f);

    r.panel_oscuro.setSize({ 720.0f, 520.0f });
    r.panel_oscuro.setPosition({ 40.0f, 40.0f });
    r.panel_oscuro.setFillColor(sf::Color(0, 0, 0, 200));
    r.panel_oscuro.setOutlineColor(sf::Color(139, 69, 19));
    r.panel_oscuro.setOutlineThickness(3.0f);

    float spacing_amount = 1.6f;
    float outline_thickness = 2.0f;
    sf::Color outline_color = sf::Color::Black;

    r.texto_reglas.setString("================= REGLAS =================\n\n"
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
    r.texto_reglas.setCharacterSize(21);
    r.texto_reglas.setPosition({ 60.0f, 60.0f });
    r.texto_reglas.setFillColor(sf::Color::White);
    r.texto_reglas.setLineSpacing(spacing_amount);
    r.texto_reglas.setOutlineThickness(outline_thickness);
    r.texto_reglas.setOutlineColor(outline_color);
    {
        auto bounds = r.texto_reglas.getLocalBounds();
        r.texto_reglas.setOrigin({ bounds.size.x / 2.0f, 0.0f });
        r.texto_reglas.setPosition({ window.getSize().x / 2.0f, 60.0f });
    }

    r.texto_controles.setString("============ MANUAL DE CONTROLES ============\n\n"
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
    r.texto_controles.setCharacterSize(21);
    r.texto_controles.setPosition({ 60.0f, 60.0f });
    r.texto_controles.setFillColor(sf::Color::White);
    r.texto_controles.setLineSpacing(spacing_amount);
    r.texto_controles.setOutlineThickness(outline_thickness);
    r.texto_controles.setOutlineColor(outline_color);
    {
        auto bounds = r.texto_controles.getLocalBounds();
        r.texto_controles.setOrigin({ bounds.size.x / 2.0f, 0.0f });
        r.texto_controles.setPosition({ window.getSize().x / 2.0f, 60.0f });
    }

    r.texto_creditos.setString("================ CREDITOS ================\n\n"
        " Proyecto Parcial 2 - Programacion I\n\n"
        " Desarrollado por:\n"
        "   - Ignacio Gonzalez\n"
        "   - Santiago Oviedo\n"
        "   - Santiago Salvay\n\n"
        " Profesora: Monica Liliana Nano\n"
        " Carrera: Ing. en Informatica / Telecomunicaciones\n\n"
        "        (Presiona ENTER para volver al menu)");
    r.texto_creditos.setCharacterSize(21);
    r.texto_creditos.setPosition({ 60.0f, 60.0f });
    r.texto_creditos.setFillColor(sf::Color::White);
    r.texto_creditos.setLineSpacing(spacing_amount);
    r.texto_creditos.setOutlineThickness(outline_thickness);
    r.texto_creditos.setOutlineColor(outline_color);
    {
        auto bounds = r.texto_creditos.getLocalBounds();
        r.texto_creditos.setOrigin({ bounds.size.x / 2.0f, 0.0f });
        r.texto_creditos.setPosition({ window.getSize().x / 2.0f, 60.0f });
    }

    (void)r.tex_suelo.loadFromFile("suelo.jpg");
    (void)r.tex_pared_izq.loadFromFile("customladrillo.png");
    (void)r.tex_pared_abajo.loadFromFile("customladrillo.png");
    (void)r.tex_pared_der.loadFromFile("customladrillo.png");
    (void)r.tex_pared_arriba.loadFromFile("customladrillo.png");
    (void)r.tex_prota.loadFromFile("prota_01.png");
    (void)r.tex_enemigo.loadFromFile("Enemigo.png");
    (void)r.tex_mercader.loadFromFile("mercader.png");
    (void)r.tex_cofre.loadFromFile("cofre.png");
    (void)r.tex_salida.loadFromFile("salida.png");
    (void)r.tex_boss.loadFromFile("boss-01.png");
    (void)r.tex_fondo_pelea.loadFromFile("fondo_pelea.png");

    std::vector<std::string> textos_pausa = { "Seguir Jugando", "Guardar Partida", "Ver Controles", "Volver al Menu" };
    for (int i = 0; i < static_cast<int>(textos_pausa.size()); i++) {
        sf::Text texto(r.alagard);
        texto.setString(textos_pausa[i]);
        texto.setCharacterSize(30);
        if (i == 0) texto.setFillColor(sf::Color::Red);
        else texto.setFillColor(sf::Color::White);
        texto.setPosition({ 260.0f, 350.0f + (i * 45.0f) });
        r.opciones_pausa.push_back(texto);
    }

    r.texto_pausa_titulo.setString("JUEGO EN PAUSA");
    r.texto_pausa_titulo.setCharacterSize(45);
    r.texto_pausa_titulo.setFillColor(sf::Color::Yellow);
    {
        auto bounds = r.texto_pausa_titulo.getLocalBounds();
        r.texto_pausa_titulo.setOrigin({ bounds.size.x / 2.0f, 0.0f });
    }
    r.texto_pausa_titulo.setPosition({ window.getSize().x / 2.0f, 250.0f });

    r.fondo_pausa.setSize({ 460.0f, 340.0f });
    r.fondo_pausa.setFillColor(sf::Color(0, 0, 0, 220));
    r.fondo_pausa.setPosition({ 180.0f, 220.0f });
    r.fondo_pausa.setOutlineColor(sf::Color::White);
    r.fondo_pausa.setOutlineThickness(2.0f);

    r.fondo_confirmacion.setSize({ 560.0f, 240.0f });
    r.fondo_confirmacion.setFillColor(sf::Color(0, 0, 0, 230));
    r.fondo_confirmacion.setOrigin({ 280.0f, 120.0f });
    r.fondo_confirmacion.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
    r.fondo_confirmacion.setOutlineColor(sf::Color::White);
    r.fondo_confirmacion.setOutlineThickness(2.0f);

    r.fondo_aviso_guardado.setSize({ 540.0f, 200.0f });
    r.fondo_aviso_guardado.setOrigin({ 270.0f, 100.0f });
    r.fondo_aviso_guardado.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
    r.fondo_aviso_guardado.setFillColor(sf::Color(0, 0, 0, 230));
    r.fondo_aviso_guardado.setOutlineColor(sf::Color(60, 200, 60));
    r.fondo_aviso_guardado.setOutlineThickness(3.0f);

    r.linea_deco_guardado.setSize({ 460.0f, 3.0f });
    r.linea_deco_guardado.setOrigin({ 230.0f, 1.5f });
    r.linea_deco_guardado.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f - 50.0f });
    r.linea_deco_guardado.setFillColor(sf::Color(60, 200, 60));

    r.texto_guardado_titulo.setString("Partida guardada correctamente");
    r.texto_guardado_titulo.setCharacterSize(28);
    r.texto_guardado_titulo.setFillColor(sf::Color::Green);
    r.texto_guardado_titulo.setOutlineColor(sf::Color::Black);
    r.texto_guardado_titulo.setOutlineThickness(2.0f);
    {
        auto bounds = r.texto_guardado_titulo.getLocalBounds();
        r.texto_guardado_titulo.setOrigin({ bounds.size.x / 2.0f, 0.0f });
    }
    r.texto_guardado_titulo.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f - 30.0f });

    r.texto_guardado_subtitulo.setString("Presiona ENTER para continuar");
    r.texto_guardado_subtitulo.setCharacterSize(20);
    r.texto_guardado_subtitulo.setFillColor(sf::Color(200, 200, 200));
    {
        auto bounds = r.texto_guardado_subtitulo.getLocalBounds();
        r.texto_guardado_subtitulo.setOrigin({ bounds.size.x / 2.0f, 0.0f });
    }
    r.texto_guardado_subtitulo.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f + 30.0f });

    r.texto_confirmacion_titulo.setString("Quieres guardar la partida?");
    r.texto_confirmacion_titulo.setCharacterSize(30);
    r.texto_confirmacion_titulo.setFillColor(sf::Color::Yellow);
    {
        auto bounds = r.texto_confirmacion_titulo.getLocalBounds();
        r.texto_confirmacion_titulo.setOrigin({ bounds.size.x / 2.0f, 0.0f });
    }
    float confirmacion_y = window.getSize().y / 2.0f;
    r.texto_confirmacion_titulo.setPosition({ window.getSize().x / 2.0f, confirmacion_y - 70.0f });

    std::vector<std::string> textos_confirmacion = { "Si", "No" };
    for (int i = 0; i < static_cast<int>(textos_confirmacion.size()); i++) {
        sf::Text texto(r.alagard);
        texto.setString(textos_confirmacion[i]);
        texto.setCharacterSize(28);
        texto.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        auto bounds = texto.getLocalBounds();
        texto.setOrigin({ bounds.size.x / 2.0f, 0.0f });
        texto.setPosition({ window.getSize().x / 2.0f, confirmacion_y - 5.0f + (i * 45.0f) });
        r.opciones_confirmacion.push_back(texto);
    }
}

void dibujarFondoMenu(sf::RenderWindow& window, const RecursosVisuales& recursos) {
    sf::Sprite sprite_fondo(recursos.textura_fondo);
    window.draw(sprite_fondo);
}

void dibujarMenuPrincipal(sf::RenderWindow& window, const RecursosVisuales& recursos) {
    window.draw(recursos.texto_titulo);
    window.draw(recursos.panel_menu);
    dibujarmenu(window, recursos.opciones_menu);
}

void dibujarPedirNombre(sf::RenderWindow& window, const RecursosVisuales& recursos, const EstadoUI& ui) {
    window.draw(recursos.texto_titulo);

    sf::RectangleShape caja_nombre({ 560.0f, 320.0f });
    caja_nombre.setOrigin({ 280.0f, 160.0f });
    caja_nombre.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
    caja_nombre.setFillColor(sf::Color(15, 15, 20, 235));
    caja_nombre.setOutlineColor(sf::Color(212, 175, 55));
    caja_nombre.setOutlineThickness(3.0f);
    window.draw(caja_nombre);

    sf::Text titulo_nombre(recursos.alagard);
    titulo_nombre.setString("Nombre del personaje");
    titulo_nombre.setCharacterSize(30);
    titulo_nombre.setFillColor(sf::Color(255, 215, 0));
    titulo_nombre.setOutlineColor(sf::Color::Black);
    titulo_nombre.setOutlineThickness(2.0f);
    {
        auto b = titulo_nombre.getLocalBounds();
        titulo_nombre.setOrigin({ b.size.x / 2.0f, 0.0f });
    }
    titulo_nombre.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f - 130.0f });
    window.draw(titulo_nombre);

    bool cursor_visible = (static_cast<int>(ui.reloj_cursor_nombre.getElapsedTime().asMilliseconds() / 500) % 2) == 0;
    sf::RectangleShape campo_texto({ 460.0f, 60.0f });
    campo_texto.setOrigin({ 230.0f, 30.0f });
    campo_texto.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f - 50.0f });
    campo_texto.setFillColor(sf::Color(30, 30, 35));
    campo_texto.setOutlineColor(sf::Color(180, 180, 180));
    campo_texto.setOutlineThickness(2.0f);
    window.draw(campo_texto);

    std::string texto_mostrar = ui.nombre_input;
    if (texto_mostrar.empty()) {
        sf::Text placeholder(recursos.alagard);
        placeholder.setString("Paolo");
        placeholder.setCharacterSize(28);
        placeholder.setFillColor(sf::Color(120, 120, 120));
        {
            auto b = placeholder.getLocalBounds();
            placeholder.setOrigin({ b.size.x / 2.0f, b.size.y / 2.0f });
        }
        placeholder.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f - 55.0f });
        window.draw(placeholder);
    }
    else {
        sf::Text texto_actual(recursos.alagard);
        texto_actual.setString(texto_mostrar + (cursor_visible ? "_" : " "));
        texto_actual.setCharacterSize(28);
        texto_actual.setFillColor(sf::Color::White);
        {
            auto b = texto_actual.getLocalBounds();
            texto_actual.setOrigin({ b.size.x / 2.0f, b.size.y / 2.0f });
        }
        texto_actual.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f - 55.0f });
        window.draw(texto_actual);
    }

    sf::Text hint1(recursos.alagard);
    hint1.setString("Escribe tu nombre y presiona ENTER");
    hint1.setCharacterSize(18);
    hint1.setFillColor(sf::Color::White);
    {
        auto b = hint1.getLocalBounds();
        hint1.setOrigin({ b.size.x / 2.0f, 0.0f });
    }
    hint1.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f + 10.0f });
    window.draw(hint1);

    sf::Text hint2(recursos.alagard);
    hint2.setString("Deja el campo vacio y presiona ENTER para usar \"Paolo\"");
    hint2.setCharacterSize(16);
    hint2.setFillColor(sf::Color(200, 200, 200));
    {
        auto b = hint2.getLocalBounds();
        hint2.setOrigin({ b.size.x / 2.0f, 0.0f });
    }
    hint2.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50.0f });
    window.draw(hint2);

    sf::Text hint3(recursos.alagard);
    hint3.setString("(ESC para volver al menu)");
    hint3.setCharacterSize(14);
    hint3.setFillColor(sf::Color(160, 160, 160));
    {
        auto b = hint3.getLocalBounds();
        hint3.setOrigin({ b.size.x / 2.0f, 0.0f });
    }
    hint3.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f + 100.0f });
    window.draw(hint3);
}

void dibujarIntroHistoria(sf::RenderWindow& window, const RecursosVisuales& recursos, const EstadoUI& ui) {
    sf::RectangleShape negro_fondo({ 800.f, 800.f });
    negro_fondo.setFillColor(sf::Color::Black);
    window.draw(negro_fondo);

    float t_intro = ui.reloj_intro.getElapsedTime().asSeconds();
    const float PI = 3.14159265f;

    for (int k = 0; k < 6; k++) {
        float radio = 110.f + k * 55.f;
        std::uint8_t alpha_luz = static_cast<std::uint8_t>(std::max(0.f, 38.f - k * 5.f));
        sf::CircleShape halo(radio);
        halo.setOrigin({ radio, radio });
        halo.setPosition({ 400.f, 80.f });
        halo.setFillColor(sf::Color(255, 230, 140, alpha_luz));
        window.draw(halo);
    }

    sf::ConvexShape cono;
    cono.setPointCount(4);
    cono.setPoint(0, { 360.f, 0.f });
    cono.setPoint(1, { 440.f, 0.f });
    cono.setPoint(2, { 560.f, 800.f });
    cono.setPoint(3, { 240.f, 800.f });
    cono.setFillColor(sf::Color(255, 230, 140, 22));
    window.draw(cono);

    float t_caida = std::min(1.f, t_intro / 2.0f);
    float t_easing = t_caida * t_caida;
    float pos_y_pj = -80.f + t_easing * 500.f;
    float rotacion_pj = 0.f;
    if (t_intro < 2.0f) {
        rotacion_pj = std::sin(t_intro * 6.f) * 25.f;
    }
    else {
        float t_rebote = t_intro - 2.0f;
        if (t_rebote < 0.4f) {
            pos_y_pj += std::sin(t_rebote * PI / 0.4f) * -18.f;
        }
    }

    sf::Sprite spr_pj_intro(recursos.tex_prota);
    {
        auto tam_pj = recursos.tex_prota.getSize();
        if (tam_pj.x > 0) {
            float escala = 200.f / static_cast<float>(tam_pj.x);
            spr_pj_intro.setScale({ escala, escala });
            spr_pj_intro.setOrigin({ static_cast<float>(tam_pj.x) / 2.f,
                                     static_cast<float>(tam_pj.y) / 2.f });
        }
    }
    spr_pj_intro.setPosition({ 400.f, pos_y_pj });
    spr_pj_intro.setRotation(sf::degrees(rotacion_pj));
    window.draw(spr_pj_intro);

    if (t_intro >= 1.6f) {
        float prog_sombra = std::min(1.f, (t_intro - 1.6f) / 0.6f);
        sf::CircleShape sombra(80.f);
        sombra.setScale({ 1.f, 0.25f });
        sombra.setOrigin({ 80.f, 80.f });
        sombra.setPosition({ 400.f, 540.f });
        sombra.setFillColor(sf::Color(0, 0, 0, static_cast<std::uint8_t>(prog_sombra * 130)));
        window.draw(sombra);
    }

    if (t_intro >= 2.4f) {
        float prog_t = std::min(1.f, (t_intro - 2.4f) / 1.0f);
        std::uint8_t alpha_t = static_cast<std::uint8_t>(prog_t * 255.f);

        sf::Text texto_intro(recursos.alagard);
        texto_intro.setString("Despiertas aturdido y sin conocimiento");
        texto_intro.setCharacterSize(26);
        texto_intro.setFillColor(sf::Color(230, 230, 230, alpha_t));
        texto_intro.setOutlineColor(sf::Color(0, 0, 0, alpha_t));
        texto_intro.setOutlineThickness(2.f);
        {
            auto b = texto_intro.getLocalBounds();
            texto_intro.setOrigin({ b.size.x / 2.f, 0.f });
        }
        texto_intro.setPosition({ 400.f, 600.f });
        window.draw(texto_intro);

        sf::Text texto_intro2(recursos.alagard);
        texto_intro2.setString("de donde estas...");
        texto_intro2.setCharacterSize(26);
        texto_intro2.setFillColor(sf::Color(230, 230, 230, alpha_t));
        texto_intro2.setOutlineColor(sf::Color(0, 0, 0, alpha_t));
        texto_intro2.setOutlineThickness(2.f);
        {
            auto b = texto_intro2.getLocalBounds();
            texto_intro2.setOrigin({ b.size.x / 2.f, 0.f });
        }
        texto_intro2.setPosition({ 400.f, 640.f });
        window.draw(texto_intro2);
    }

    if (t_intro >= 4.0f) {
        float pulso_e = (std::sin(t_intro * 2.5f) + 1.f) * 0.5f;
        std::uint8_t alpha_e = static_cast<std::uint8_t>(140 + pulso_e * 115);

        sf::Text texto_press(recursos.alagard);
        texto_press.setString("Presiona E para comenzar");
        texto_press.setCharacterSize(28);
        texto_press.setFillColor(sf::Color(255, 215, 0, alpha_e));
        texto_press.setOutlineColor(sf::Color(0, 0, 0, alpha_e));
        texto_press.setOutlineThickness(2.f);
        {
            auto b = texto_press.getLocalBounds();
            texto_press.setOrigin({ b.size.x / 2.f, 0.f });
        }
        texto_press.setPosition({ 400.f, 720.f });
        window.draw(texto_press);
    }
}

void dibujarMapaConCamara(
    sf::RenderWindow& window,
    string matriz_fondo[max_filas][max_columnas],
    string matriz_entidades[max_filas][max_columnas],
    RecursosVisuales& recursos
) {
    sf::View camara_juego(sf::FloatRect({ 0.f, 0.f }, { 2540.f, 2540.f }));
    camara_juego.setCenter(sf::Vector2f(1270.f, 1270.f));
    window.setView(camara_juego);
    dibujarmapa(window, matriz_fondo, matriz_entidades,
        recursos.tex_suelo, recursos.tex_pared_arriba, recursos.tex_pared_abajo,
        recursos.tex_pared_izq, recursos.tex_pared_der,
        recursos.tex_prota, recursos.tex_boss, recursos.tex_enemigo,
        recursos.tex_mercader, recursos.tex_cofre, recursos.tex_salida);
    window.setView(window.getDefaultView());
}

void dibujarPantallaJuego(sf::RenderWindow& window, const RecursosVisuales& recursos, const EstadoUI& ui) {
    if (ui.aviso_puerta) {
        sf::RectangleShape fondo_aviso({ 650.0f, 50.0f });
        fondo_aviso.setPosition({ 75.0f, 50.0f });
        fondo_aviso.setFillColor(sf::Color(0, 0, 0, 220));
        fondo_aviso.setOutlineColor(sf::Color::Red);
        fondo_aviso.setOutlineThickness(2.0f);
        window.draw(fondo_aviso);

        sf::Text texto_aviso(recursos.alagard);
        texto_aviso.setString("! La puerta esta sellada ! Derrota a todos los enemigos.");
        texto_aviso.setCharacterSize(22);
        texto_aviso.setPosition({ 100.0f, 62.0f });
        texto_aviso.setFillColor(sf::Color::Red);
        window.draw(texto_aviso);
    }

    if (ui.aviso_boss) {
        sf::RectangleShape fondo_boss({ 620.0f, 240.0f });
        fondo_boss.setOrigin({ 310.0f, 120.0f });
        fondo_boss.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
        fondo_boss.setFillColor(sf::Color(20, 5, 5, 235));
        fondo_boss.setOutlineColor(sf::Color(220, 60, 60));
        fondo_boss.setOutlineThickness(3.0f);
        window.draw(fondo_boss);

        sf::Text titulo_boss(recursos.alagard);
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

        sf::Text msg_boss(recursos.alagard);
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

        sf::Text consejo_boss(recursos.alagard);
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

        sf::Text hint_boss(recursos.alagard);
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

    if (ui.aviso_cofre) {
        sf::RectangleShape fondo_cofre({ 460.0f, 260.0f });
        fondo_cofre.setPosition({ 170.0f, 250.0f });
        fondo_cofre.setFillColor(sf::Color(20, 20, 20, 230));
        fondo_cofre.setOutlineColor(sf::Color(212, 175, 55));
        fondo_cofre.setOutlineThickness(3.0f);
        window.draw(fondo_cofre);

        sf::Text titulo_cofre(recursos.alagard);
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

        sf::Text texto_cofre(recursos.alagard);
        texto_cofre.setString(ui.mensaje_cofre);
        texto_cofre.setCharacterSize(20);
        texto_cofre.setFillColor(sf::Color::White);
        texto_cofre.setLineSpacing(1.1f);
        texto_cofre.setPosition({ 200.0f, 305.0f });
        window.draw(texto_cofre);

        sf::Text texto_continuar(recursos.alagard);
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

    if (ui.en_pausa) {
        window.draw(recursos.fondo_pausa);
        window.draw(recursos.texto_pausa_titulo);
        for (const auto& texto_opcion : recursos.opciones_pausa) {
            window.draw(texto_opcion);
        }
    }
}

void dibujarCargarPartida(sf::RenderWindow& window, const RecursosVisuales& recursos, EstadoUI& ui) {
    sf::Text titulo_cargar(recursos.alagard);
    titulo_cargar.setString("SELECCIONAR PARTIDA");
    titulo_cargar.setCharacterSize(35);
    {
        auto bounds = titulo_cargar.getLocalBounds();
        titulo_cargar.setOrigin({ bounds.size.x / 2.0f, 0.0f });
    }
    titulo_cargar.setPosition({ window.getSize().x / 2.0f, 80.0f });
    titulo_cargar.setFillColor(sf::Color::Yellow);
    window.draw(titulo_cargar);

    if (ui.opciones_carga.empty()) {
        sf::Text sin_partidas(recursos.alagard);
        sin_partidas.setString("No hay partidas guardadas");
        sin_partidas.setCharacterSize(24);
        {
            auto bounds = sin_partidas.getLocalBounds();
            sin_partidas.setOrigin({ bounds.size.x / 2.0f, 0.0f });
        }
        sin_partidas.setPosition({ window.getSize().x / 2.0f, 200.0f });
        sin_partidas.setFillColor(sf::Color::White);
        window.draw(sin_partidas);

        sf::Text volver(recursos.alagard);
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
        const int total = static_cast<int>(ui.opciones_carga.size());
        const int fin = std::min(ui.scroll_carga + MAX_PARTIDAS_VISIBLES, total);
        const float y_inicial = 160.0f;
        const float separacion = 70.0f;
        for (int i = ui.scroll_carga; i < fin; i++) {
            ui.opciones_carga[i].setPosition({ window.getSize().x / 2.0f, y_inicial + (i - ui.scroll_carga) * separacion });
            window.draw(ui.opciones_carga[i]);
        }

        if (ui.scroll_carga > 0) {
            sf::Text flecha_arriba(recursos.alagard);
            flecha_arriba.setString("^  Mas partidas  ^");
            flecha_arriba.setCharacterSize(16);
            flecha_arriba.setFillColor(sf::Color(180, 180, 180));
            auto b = flecha_arriba.getLocalBounds();
            flecha_arriba.setOrigin({ b.size.x / 2.0f, 0.0f });
            flecha_arriba.setPosition({ window.getSize().x / 2.0f, 130.0f });
            window.draw(flecha_arriba);
        }

        if (fin < total) {
            sf::Text flecha_abajo(recursos.alagard);
            flecha_abajo.setString("v  Mas partidas  v");
            flecha_abajo.setCharacterSize(16);
            flecha_abajo.setFillColor(sf::Color(180, 180, 180));
            auto b = flecha_abajo.getLocalBounds();
            flecha_abajo.setOrigin({ b.size.x / 2.0f, 0.0f });
            flecha_abajo.setPosition({ window.getSize().x / 2.0f, y_inicial + MAX_PARTIDAS_VISIBLES * separacion + 5.0f });
            window.draw(flecha_abajo);
        }

        sf::Text pie(recursos.alagard);
        pie.setString("Partida " + std::to_string(ui.item_carga + 1) + " / " + std::to_string(total)
            + "    -    WASD para navegar, ENTER para cargar, ESC para volver");
        pie.setCharacterSize(14);
        pie.setFillColor(sf::Color(160, 160, 160));
        {
            auto b = pie.getLocalBounds();
            pie.setOrigin({ b.size.x / 2.0f, 0.0f });
        }
        pie.setPosition({ window.getSize().x / 2.0f, 760.0f });
        window.draw(pie);
    }
}

void dibujarConfirmarGuardado(sf::RenderWindow& window, const RecursosVisuales& recursos) {
    window.draw(recursos.fondo_confirmacion);
    window.draw(recursos.texto_confirmacion_titulo);
    for (const auto& opcion : recursos.opciones_confirmacion) {
        window.draw(opcion);
    }
}

void dibujarAvisoGuardado(sf::RenderWindow& window, const RecursosVisuales& recursos) {
    window.draw(recursos.fondo_aviso_guardado);
    window.draw(recursos.linea_deco_guardado);
    window.draw(recursos.texto_guardado_titulo);
    window.draw(recursos.texto_guardado_subtitulo);
}

void dibujarInventario(sf::RenderWindow& window, const RecursosVisuales& recursos, const personaje& paolo, EstadoUI& ui) {
    sf::Text titulo_inv(recursos.alagard);
    titulo_inv.setString("=== ESTADO Y MOCHILA ===");
    titulo_inv.setCharacterSize(35);
    titulo_inv.setPosition({ 180.0f, 60.0f });
    titulo_inv.setFillColor(sf::Color::Yellow);
    window.draw(titulo_inv);

    int vida_tope = 100 + paolo.defensa;

    sf::Text stats_texto(recursos.alagard);
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

    std::vector<std::pair<std::string, int>> grupos_inv;
    for (int i = 0; i < paolo.cant_items; i++) {
        if (!grupos_inv.empty() && grupos_inv.back().first == paolo.inventario[i]) {
            grupos_inv.back().second++;
        }
        else {
            grupos_inv.push_back({ paolo.inventario[i], 1 });
        }
    }

    if (ui.cursor_inventario >= static_cast<int>(grupos_inv.size())) {
        ui.cursor_inventario = static_cast<int>(grupos_inv.size()) - 1;
    }
    if (ui.cursor_inventario < 0) ui.cursor_inventario = 0;

    for (int i = 0; i < static_cast<int>(grupos_inv.size()) && i < 10; i++) {
        std::string texto_item = grupos_inv[i].first;
        if (grupos_inv[i].second > 1) {
            texto_item += " x " + std::to_string(grupos_inv[i].second);
        }

        sf::Text item_texto(recursos.alagard);
        item_texto.setCharacterSize(22);
        item_texto.setPosition({ 450.0f, 150.0f + (i * 35.0f) });

        if (i == ui.cursor_inventario) {
            item_texto.setFillColor(sf::Color::Red);
            item_texto.setString("> " + texto_item + " <");
        }
        else {
            item_texto.setFillColor(sf::Color::White);
            item_texto.setString(texto_item);
        }
        window.draw(item_texto);
    }

    sf::Text consejo_inv(recursos.alagard);
    consejo_inv.setString("Tip: guarda pociones para el Boss final!");
    consejo_inv.setCharacterSize(16);
    consejo_inv.setFillColor(sf::Color(255, 215, 0));
    consejo_inv.setOutlineColor(sf::Color::Black);
    consejo_inv.setOutlineThickness(1.0f);
    consejo_inv.setPosition({ 60.0f, 490.0f });
    window.draw(consejo_inv);

    sf::Text controles_inv(recursos.alagard);
    controles_inv.setString("W/S = Mover | ENTER = Equipar / Usar | 6 = Ordenar | ESC / 5 = Salir");
    controles_inv.setCharacterSize(18);
    controles_inv.setPosition({ 60.0f, 520.0f });
    controles_inv.setFillColor(sf::Color(200, 200, 200));
    window.draw(controles_inv);
}

void dibujarTienda(sf::RenderWindow& window, const RecursosVisuales& recursos, const personaje& paolo, const mercader& vendedor, const EstadoUI& ui) {
    sf::Text titulo_tienda(recursos.alagard);
    titulo_tienda.setString("COMPRAR");
    titulo_tienda.setCharacterSize(35);
    titulo_tienda.setPosition({ 150.0f, 60.0f });
    titulo_tienda.setFillColor(ui.en_modo_compra ? sf::Color::Yellow : sf::Color(100, 100, 100));
    window.draw(titulo_tienda);

    sf::Text titulo_mochila(recursos.alagard);
    titulo_mochila.setString("VENDER");
    titulo_mochila.setCharacterSize(35);
    titulo_mochila.setPosition({ 500.0f, 60.0f });
    titulo_mochila.setFillColor(!ui.en_modo_compra ? sf::Color::Yellow : sf::Color(100, 100, 100));
    window.draw(titulo_mochila);

    sf::Text oro_texto(recursos.alagard);
    oro_texto.setString("Tu Oro: " + std::to_string(paolo.oro));
    oro_texto.setCharacterSize(25);
    oro_texto.setPosition({ 320.0f, 440.0f });
    oro_texto.setFillColor(sf::Color::White);
    window.draw(oro_texto);

    for (int i = 0; i < 6; i++) {
        sf::Text item_texto(recursos.alagard);
        item_texto.setString(vendedor.catalogo[i] + " (" + std::to_string(vendedor.precios[i]) + ")");
        item_texto.setCharacterSize(20);
        item_texto.setPosition({ 60.0f, 130.0f + (i * 35.0f) });

        if (ui.en_modo_compra && i == ui.cursor_tienda) {
            item_texto.setFillColor(sf::Color::Red);
        }
        else {
            item_texto.setFillColor(sf::Color::White);
        }
        window.draw(item_texto);
    }

    for (int i = 0; i < paolo.cant_items; i++) {
        if (i < 8) {
            sf::Text item_texto(recursos.alagard);
            int valor_venta = obtenerprecioventa(paolo.inventario[i]);
            item_texto.setString(paolo.inventario[i] + " (+" + std::to_string(valor_venta) + ")");
            item_texto.setCharacterSize(20);
            item_texto.setPosition({ 450.0f, 130.0f + (i * 35.0f) });

            if (!ui.en_modo_compra && i == ui.cursor_inventario) {
                item_texto.setFillColor(sf::Color::Red);
            }
            else {
                item_texto.setFillColor(sf::Color::White);
            }
            window.draw(item_texto);
        }
    }

    sf::Text consejo_tienda(recursos.alagard);
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

    sf::Text controles_tienda(recursos.alagard);
    controles_tienda.setString("A/D = Cambiar Panel | W/S = Mover | ENTER = Confirmar | ESC = Salir");
    controles_tienda.setCharacterSize(18);
    controles_tienda.setPosition({ 80.0f, 500.0f });
    controles_tienda.setFillColor(sf::Color(200, 200, 200));
    window.draw(controles_tienda);
}

void dibujarBatalla(sf::RenderWindow& window, const RecursosVisuales& recursos, EstadoBatalla& batalla, const personaje& paolo) {
    sf::Sprite sprite_fondo_pelea(recursos.tex_fondo_pelea);
    {
        auto tam_fondo = recursos.tex_fondo_pelea.getSize();
        if (tam_fondo.x > 0 && tam_fondo.y > 0) {
            sprite_fondo_pelea.setScale({ 800.0f / static_cast<float>(tam_fondo.x), 800.0f / static_cast<float>(tam_fondo.y) });
        }
    }
    window.draw(sprite_fondo_pelea);

    // CINEMATICA EPICA AL ENFRENTAR AL BOSS
    if (batalla.fase == fase_batalla::cinematica_boss) {
        const float PI = 3.14159265f;
        float t = batalla.reloj_anim.getElapsedTime().asSeconds();
        const float dur_total = 6.5f;

        {
            float alpha_velo = 255.f;
            if (t < 0.8f) alpha_velo = 255.f - (t / 0.8f) * 100.f;
            else alpha_velo = 155.f - std::min(1.f, (t - 0.8f) / 1.2f) * 95.f;
            if (alpha_velo < 60.f) alpha_velo = 60.f;
            sf::RectangleShape velo({ 800.f, 800.f });
            velo.setFillColor(sf::Color(0, 0, 0, static_cast<std::uint8_t>(alpha_velo)));
            window.draw(velo);
        }

        {
            sf::Sprite spr_boss(recursos.tex_boss);
            auto tam = recursos.tex_boss.getSize();
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

            if (t > 1.7f) {
                pos_x_boss += std::sin(t * 28.f) * 4.f;
                pos_y_boss += std::cos(t * 24.f) * 3.f;
            }
            spr_boss.setPosition({ pos_x_boss, pos_y_boss });
            window.draw(spr_boss);
        }

        if (t >= 2.0f && t < 3.0f) {
            float prog_flash = (t - 2.0f) / 1.0f;
            float alpha_flash = std::sin(prog_flash * PI) * 140.f;
            if (alpha_flash > 0.f) {
                sf::RectangleShape flash({ 800.f, 800.f });
                flash.setFillColor(sf::Color(180, 0, 0, static_cast<std::uint8_t>(alpha_flash)));
                window.draw(flash);
            }
        }

        auto dibujar_texto_dram = [&](const std::string& s, float aparece, float desaparece, float y, unsigned size, sf::Color color) {
            if (t < aparece || t > desaparece) return;
            float local = t - aparece;
            float dur = desaparece - aparece;
            float alpha = 255.f;
            if (local < 0.25f) alpha = (local / 0.25f) * 255.f;
            else if (local > dur - 0.4f) alpha = ((dur - local) / 0.4f) * 255.f;
            if (alpha < 0.f) alpha = 0.f;
            if (alpha > 255.f) alpha = 255.f;
            sf::Text txt(recursos.alagard);
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

        sf::Text saltear(recursos.alagard);
        saltear.setString("(ENTER para saltear)");
        saltear.setCharacterSize(14);
        saltear.setFillColor(sf::Color(180, 180, 180, 200));
        saltear.setPosition({ 620.f, 770.f });
        window.draw(saltear);

        if (t >= dur_total) {
            batalla.fase = fase_batalla::espera_input;
            batalla.mensaje = "El Guardian de la Mazmorra te desafia! Que haces?";
            batalla.reloj_anim.restart();
        }

        return;
    }

    float t_norm = batalla.reloj_anim.getElapsedTime().asSeconds() / DURACION_ANIM_BATALLA;
    if (t_norm > 1.0f) t_norm = 1.0f;
    float offset_pj = 0.f;
    float offset_en = 0.f;
    float offset_y_en = 0.f;
    float escala_extra_en = 1.f;
    if (batalla.fase == fase_batalla::anim_pj_ataca) {
        offset_pj = std::sin(t_norm * 3.14159265f) * 130.f;
    }
    else if (batalla.fase == fase_batalla::anim_enemigo_ataca) {
        offset_en = -std::sin(t_norm * 3.14159265f) * 130.f;
    }
    else if (batalla.fase == fase_batalla::anim_pocion) {
        offset_pj = std::sin(t_norm * 3.14159265f * 4.f) * 12.f;
    }
    else if (batalla.fase == fase_batalla::cinematica_curacion_boss) {
        float t_cur = batalla.reloj_anim.getElapsedTime().asSeconds();
        offset_y_en = -std::sin(std::min(1.f, t_cur / 1.0f) * 1.5707963f) * 30.f;
        offset_en = std::sin(t_cur * 30.f) * 4.f;
    }
    else if (batalla.fase == fase_batalla::cinematica_ataque_especial_boss) {
        float t_atk = batalla.reloj_anim.getElapsedTime().asSeconds();
        escala_extra_en = 1.f + std::min(1.f, t_atk / 2.0f) * 0.4f;
        offset_en = std::sin(t_atk * 45.f) * 8.f;
        offset_y_en = std::cos(t_atk * 40.f) * 6.f;
    }
    else if (batalla.fase == fase_batalla::cinematica_golpe_devastador) {
        float t_dev = batalla.reloj_anim.getElapsedTime().asSeconds();
        if (t_dev < 1.4f) {
            float prog = t_dev / 1.4f;
            offset_y_en = -prog * 700.f;
            escala_extra_en = 1.f + prog * 0.3f;
        }
        else if (t_dev < DURACION_GOLPE_DEVASTADOR - 0.6f) {
            offset_y_en = -800.f;
        }
        else {
            float t_caida = (t_dev - (DURACION_GOLPE_DEVASTADOR - 0.6f)) / 0.6f;
            if (t_caida > 1.f) t_caida = 1.f;
            offset_y_en = -800.f + t_caida * t_caida * 1140.f;
            offset_en = -360.f;
            escala_extra_en = 1.3f;
        }
    }

    sf::Sprite sprite_pj_batalla(recursos.tex_prota);
    {
        auto tam_pj = recursos.tex_prota.getSize();
        if (tam_pj.x > 0) {
            float escala = 220.f / static_cast<float>(tam_pj.x);
            sprite_pj_batalla.setScale({ escala, escala });
        }
    }
    sprite_pj_batalla.setPosition({ 110.f + offset_pj, 340.f });
    window.draw(sprite_pj_batalla);

    sf::Sprite sprite_enemigo_batalla(batalla.es_boss_actual ? recursos.tex_boss : recursos.tex_enemigo);
    {
        auto tam_en = (batalla.es_boss_actual ? recursos.tex_boss : recursos.tex_enemigo).getSize();
        if (tam_en.x > 0) {
            float escala = (220.f / static_cast<float>(tam_en.x)) * escala_extra_en;
            sprite_enemigo_batalla.setScale({ escala, escala });
        }
    }
    sprite_enemigo_batalla.setPosition({ 470.f + offset_en, 340.f + offset_y_en });
    window.draw(sprite_enemigo_batalla);

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

    sf::Text nombre_pj(recursos.alagard);
    nombre_pj.setString((paolo.name.empty() ? std::string("Paolo") : paolo.name) +
        "   HP: " + std::to_string(paolo.vida) + " / " + std::to_string(vida_max_pj));
    nombre_pj.setCharacterSize(20);
    nombre_pj.setFillColor(sf::Color::White);
    nombre_pj.setOutlineColor(sf::Color::Black);
    nombre_pj.setOutlineThickness(2.f);
    nombre_pj.setPosition({ 40.f, 75.f });
    window.draw(nombre_pj);

    float porc_en = (batalla.enemigo_vida_max > 0) ? (static_cast<float>(batalla.enemigo_actual.vida) / static_cast<float>(batalla.enemigo_vida_max)) : 0.f;
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

    sf::Text nombre_en(recursos.alagard);
    if (batalla.es_boss_actual) {
        int porcentaje_boss = static_cast<int>(porc_en * 100.f + 0.5f);
        if (porcentaje_boss < 0) porcentaje_boss = 0;
        if (porcentaje_boss > 100) porcentaje_boss = 100;
        nombre_en.setString(batalla.enemigo_actual.nombre + "   HP: " + std::to_string(porcentaje_boss) + "%");
    }
    else {
        nombre_en.setString(batalla.enemigo_actual.nombre + "   HP: " +
            std::to_string(batalla.enemigo_actual.vida) + " / " + std::to_string(batalla.enemigo_vida_max));
    }
    nombre_en.setCharacterSize(20);
    nombre_en.setFillColor(sf::Color::White);
    nombre_en.setOutlineColor(sf::Color::Black);
    nombre_en.setOutlineThickness(2.f);
    nombre_en.setPosition({ 520.f, 75.f });
    window.draw(nombre_en);

    // CINEMATICA DE CURACION DEL BOSS (overlay sobre la batalla)
    if (batalla.fase == fase_batalla::cinematica_curacion_boss) {
        const float PI = 3.14159265f;
        float tc = batalla.reloj_anim.getElapsedTime().asSeconds();

        float pulso_v = (std::sin(tc * 4.f) + 1.f) * 0.5f;
        sf::RectangleShape velo_verde({ 800.f, 800.f });
        velo_verde.setFillColor(sf::Color(30, 200, 60, static_cast<std::uint8_t>(60 + pulso_v * 50)));
        window.draw(velo_verde);

        for (int k = 0; k < 3; k++) {
            float fase_k = std::fmod(tc + k * 0.6f, 1.8f) / 1.8f;
            float radio = 60.f + fase_k * 220.f;
            float alpha_ring = (1.f - fase_k) * 220.f;
            sf::CircleShape anillo(radio);
            anillo.setOrigin({ radio, radio });
            anillo.setPosition({ 470.f + 110.f + offset_en, 340.f + 110.f + offset_y_en });
            anillo.setFillColor(sf::Color::Transparent);
            anillo.setOutlineColor(sf::Color(80, 255, 120, static_cast<std::uint8_t>(alpha_ring)));
            anillo.setOutlineThickness(4.f);
            window.draw(anillo);
        }

        for (int k = 0; k < 6; k++) {
            float fase_k = std::fmod(tc * 0.9f + k * 0.35f, 1.8f) / 1.8f;
            float pos_x = 470.f + 60.f + std::sin(k * 1.2f) * 90.f;
            float pos_y = 480.f - fase_k * 220.f;
            float alpha_c = (1.f - fase_k) * 255.f;
            sf::Text cruz(recursos.alagard);
            cruz.setString("+");
            cruz.setCharacterSize(36);
            cruz.setFillColor(sf::Color(100, 255, 130, static_cast<std::uint8_t>(alpha_c)));
            cruz.setOutlineColor(sf::Color(0, 80, 20, static_cast<std::uint8_t>(alpha_c)));
            cruz.setOutlineThickness(2.f);
            cruz.setPosition({ pos_x, pos_y });
            window.draw(cruz);
        }

        float alpha_titulo = std::min(1.f, tc / 0.4f) * 255.f;
        if (tc > DURACION_CURACION_BOSS - 0.4f) {
            alpha_titulo = ((DURACION_CURACION_BOSS - tc) / 0.4f) * 255.f;
        }
        if (alpha_titulo < 0.f) alpha_titulo = 0.f;
        sf::Text titulo_cura(recursos.alagard);
        titulo_cura.setString("REGENERACION");
        titulo_cura.setCharacterSize(56);
        titulo_cura.setFillColor(sf::Color(120, 255, 140, static_cast<std::uint8_t>(alpha_titulo)));
        titulo_cura.setOutlineColor(sf::Color(0, 60, 20, static_cast<std::uint8_t>(alpha_titulo)));
        titulo_cura.setOutlineThickness(4.f);
        {
            auto b = titulo_cura.getLocalBounds();
            titulo_cura.setOrigin({ b.size.x / 2.f, 0.f });
        }
        titulo_cura.setPosition({ 400.f, 250.f });
        window.draw(titulo_cura);

        sf::Text sub_cura(recursos.alagard);
        sub_cura.setString("El Guardian recupera su poder!");
        sub_cura.setCharacterSize(22);
        sub_cura.setFillColor(sf::Color(220, 255, 220, static_cast<std::uint8_t>(alpha_titulo)));
        sub_cura.setOutlineColor(sf::Color::Black);
        sub_cura.setOutlineThickness(2.f);
        {
            auto b = sub_cura.getLocalBounds();
            sub_cura.setOrigin({ b.size.x / 2.f, 0.f });
        }
        sub_cura.setPosition({ 400.f, 320.f });
        window.draw(sub_cura);
    }

    // CINEMATICA DE ATAQUE ESPECIAL DEL BOSS (overlay sobre la batalla)
    if (batalla.fase == fase_batalla::cinematica_ataque_especial_boss) {
        const float PI = 3.14159265f;
        float ta = batalla.reloj_anim.getElapsedTime().asSeconds();

        float intensidad = std::min(1.f, ta / DURACION_ATAQUE_ESPECIAL_BOSS);
        float pulso_a = (std::sin(ta * 8.f) + 1.f) * 0.5f;
        sf::RectangleShape velo_rojo({ 800.f, 800.f });
        velo_rojo.setFillColor(sf::Color(180, 20, 20, static_cast<std::uint8_t>(40 + intensidad * 120 + pulso_a * 20)));
        window.draw(velo_rojo);

        for (int k = 0; k < 4; k++) {
            float fase_k = std::fmod(ta * 1.4f + k * 0.45f, 1.4f) / 1.4f;
            float radio = 70.f + fase_k * 200.f;
            float alpha_ring = (1.f - fase_k) * 240.f;
            sf::CircleShape anillo(radio);
            anillo.setOrigin({ radio, radio });
            anillo.setPosition({ 470.f + 110.f + offset_en, 340.f + 110.f + offset_y_en });
            anillo.setFillColor(sf::Color::Transparent);
            anillo.setOutlineColor(sf::Color(255, 80, 30, static_cast<std::uint8_t>(alpha_ring)));
            anillo.setOutlineThickness(5.f);
            window.draw(anillo);
        }

        for (int k = 0; k < 10; k++) {
            float angulo = (k / 10.f) * 2.f * PI + ta * 0.8f;
            float largo = 80.f + std::sin(ta * 3.f + k) * 30.f + intensidad * 60.f;
            sf::RectangleShape rayo({ largo, 3.f });
            rayo.setOrigin({ 0.f, 1.5f });
            rayo.setPosition({ 470.f + 110.f + offset_en, 340.f + 110.f + offset_y_en });
            rayo.setRotation(sf::radians(angulo));
            rayo.setFillColor(sf::Color(255, 200, 50, static_cast<std::uint8_t>(180 + pulso_a * 75)));
            window.draw(rayo);
        }

        if (ta > DURACION_ATAQUE_ESPECIAL_BOSS - 0.5f) {
            float prog_flash = (ta - (DURACION_ATAQUE_ESPECIAL_BOSS - 0.5f)) / 0.5f;
            float alpha_flash = std::sin(prog_flash * PI) * 230.f;
            sf::RectangleShape flash({ 800.f, 800.f });
            flash.setFillColor(sf::Color(255, 255, 255, static_cast<std::uint8_t>(alpha_flash)));
            window.draw(flash);
        }

        float alpha_titulo_a = std::min(1.f, ta / 0.3f) * 255.f;
        if (ta > DURACION_ATAQUE_ESPECIAL_BOSS - 0.3f) {
            alpha_titulo_a = ((DURACION_ATAQUE_ESPECIAL_BOSS - ta) / 0.3f) * 255.f;
        }
        if (alpha_titulo_a < 0.f) alpha_titulo_a = 0.f;

        sf::Text titulo_atk(recursos.alagard);
        titulo_atk.setString("ATAQUE ESPECIAL");
        titulo_atk.setCharacterSize(56);
        titulo_atk.setFillColor(sf::Color(255, 80, 50, static_cast<std::uint8_t>(alpha_titulo_a)));
        titulo_atk.setOutlineColor(sf::Color::Black);
        titulo_atk.setOutlineThickness(4.f);
        {
            auto b = titulo_atk.getLocalBounds();
            titulo_atk.setOrigin({ b.size.x / 2.f, 0.f });
        }
        titulo_atk.setPosition({ 400.f + std::sin(ta * 35.f) * 3.f, 240.f });
        window.draw(titulo_atk);

        sf::Text sub_atk(recursos.alagard);
        sub_atk.setString("Preparate para el golpe devastador!");
        sub_atk.setCharacterSize(22);
        sub_atk.setFillColor(sf::Color(255, 220, 220, static_cast<std::uint8_t>(alpha_titulo_a)));
        sub_atk.setOutlineColor(sf::Color::Black);
        sub_atk.setOutlineThickness(2.f);
        {
            auto b = sub_atk.getLocalBounds();
            sub_atk.setOrigin({ b.size.x / 2.f, 0.f });
        }
        sub_atk.setPosition({ 400.f, 310.f });
        window.draw(sub_atk);
    }

    // CINEMATICA DE GOLPE DEVASTADOR (overlay sobre la batalla)
    if (batalla.fase == fase_batalla::cinematica_golpe_devastador) {
        const float PI = 3.14159265f;
        float td = batalla.reloj_anim.getElapsedTime().asSeconds();

        if (td < 1.4f) {
            float prog = td / 1.4f;
            sf::RectangleShape velo_d({ 800.f, 800.f });
            velo_d.setFillColor(sf::Color(80, 0, 0, static_cast<std::uint8_t>(prog * 80.f)));
            window.draw(velo_d);

            float alpha_t = std::sin(prog * PI) * 255.f;
            sf::Text salto(recursos.alagard);
            salto.setString("El Guardian se eleva...");
            salto.setCharacterSize(34);
            salto.setFillColor(sf::Color(255, 200, 100, static_cast<std::uint8_t>(alpha_t)));
            salto.setOutlineColor(sf::Color::Black);
            salto.setOutlineThickness(3.f);
            {
                auto b = salto.getLocalBounds();
                salto.setOrigin({ b.size.x / 2.f, 0.f });
            }
            salto.setPosition({ 400.f, 260.f });
            window.draw(salto);
        }
        else if (td < DURACION_GOLPE_DEVASTADOR - 0.6f) {
            float t_local = td - 1.4f;
            float dur_etapa = (DURACION_GOLPE_DEVASTADOR - 0.6f) - 1.4f;
            float prog = (dur_etapa > 0.f) ? (t_local / dur_etapa) : 1.f;

            sf::RectangleShape velo_d({ 800.f, 800.f });
            velo_d.setFillColor(sf::Color(80, 0, 0, 130));
            window.draw(velo_d);

            float radio_sombra = 30.f + prog * 110.f;
            sf::CircleShape sombra(radio_sombra);
            sombra.setScale({ 1.f, 0.4f });
            sombra.setOrigin({ radio_sombra, radio_sombra });
            sombra.setPosition({ 220.f, 540.f });
            sombra.setFillColor(sf::Color(0, 0, 0, 200));
            window.draw(sombra);

            float radio_anillo = 60.f + std::sin(td * 12.f) * 18.f;
            sf::CircleShape anillo(radio_anillo);
            anillo.setScale({ 1.f, 0.4f });
            anillo.setOrigin({ radio_anillo, radio_anillo });
            anillo.setPosition({ 220.f, 540.f });
            anillo.setFillColor(sf::Color::Transparent);
            anillo.setOutlineColor(sf::Color(255, 50, 50, 220));
            anillo.setOutlineThickness(3.f);
            window.draw(anillo);

            float pulso_w = (std::sin(td * 8.f) + 1.f) * 0.5f;
            std::uint8_t alpha_w = static_cast<std::uint8_t>(180 + pulso_w * 75);
            sf::Text peligro(recursos.alagard);
            peligro.setString("CUIDADO!");
            peligro.setCharacterSize(44);
            peligro.setFillColor(sf::Color(255, 60, 60, alpha_w));
            peligro.setOutlineColor(sf::Color(0, 0, 0, alpha_w));
            peligro.setOutlineThickness(4.f);
            {
                auto b = peligro.getLocalBounds();
                peligro.setOrigin({ b.size.x / 2.f, 0.f });
            }
            peligro.setPosition({ 400.f + std::sin(td * 30.f) * 4.f, 240.f });
            window.draw(peligro);
        }
        else {
            float t_imp = td - (DURACION_GOLPE_DEVASTADOR - 0.6f);
            float prog_imp = t_imp / 0.6f;

            float alpha_flash = std::sin(prog_imp * PI) * 230.f;
            sf::RectangleShape flash({ 800.f, 800.f });
            flash.setFillColor(sf::Color(255, 240, 200, static_cast<std::uint8_t>(alpha_flash)));
            window.draw(flash);

            if (prog_imp > 0.3f) {
                for (int k = 0; k < 3; k++) {
                    float ph = (prog_imp - 0.3f) / 0.7f + k * 0.2f;
                    if (ph < 0.f || ph > 1.f) continue;
                    float radio = 50.f + ph * 380.f;
                    sf::CircleShape onda(radio);
                    onda.setOrigin({ radio, radio });
                    onda.setPosition({ 220.f, 540.f });
                    onda.setFillColor(sf::Color::Transparent);
                    onda.setOutlineColor(sf::Color(255, 200, 100, static_cast<std::uint8_t>((1.f - ph) * 220.f)));
                    onda.setOutlineThickness(4.f);
                    window.draw(onda);
                }
            }

            sf::Text titulo_d(recursos.alagard);
            titulo_d.setString("GOLPE DEVASTADOR");
            titulo_d.setCharacterSize(54);
            titulo_d.setFillColor(sf::Color(255, 100, 60));
            titulo_d.setOutlineColor(sf::Color::Black);
            titulo_d.setOutlineThickness(5.f);
            {
                auto b = titulo_d.getLocalBounds();
                titulo_d.setOrigin({ b.size.x / 2.f, 0.f });
            }
            titulo_d.setPosition({ 400.f + std::sin(td * 80.f) * 8.f,
                                    260.f + std::cos(td * 70.f) * 6.f });
            window.draw(titulo_d);
        }
    }

    // --- PANEL INFERIOR DE MENSAJES Y OPCIONES ---
    sf::RectangleShape panel_batalla({ 760.f, 180.f });
    panel_batalla.setPosition({ 20.f, 600.f });
    panel_batalla.setFillColor(sf::Color(0, 0, 0, 220));
    panel_batalla.setOutlineColor(sf::Color(180, 180, 180));
    panel_batalla.setOutlineThickness(3.f);
    window.draw(panel_batalla);

    sf::Text texto_mensaje(recursos.alagard);
    texto_mensaje.setString(batalla.mensaje);
    texto_mensaje.setCharacterSize(20);
    texto_mensaje.setFillColor(sf::Color::Yellow);
    texto_mensaje.setPosition({ 40.f, 615.f });
    window.draw(texto_mensaje);

    if (batalla.fase == fase_batalla::espera_input) {
        sf::Text texto_opciones(recursos.alagard);
        texto_opciones.setString("1) Atacar     2) Usar Pocion     3) Defender     4) Huir");
        texto_opciones.setCharacterSize(22);
        texto_opciones.setFillColor(sf::Color::White);
        texto_opciones.setPosition({ 40.f, 720.f });
        window.draw(texto_opciones);
    }
    else if (batalla.fase == fase_batalla::ganada) {
        sf::Text texto_resultado(recursos.alagard);
        texto_resultado.setString("VICTORIA - Partida guardada automaticamente");
        texto_resultado.setCharacterSize(22);
        texto_resultado.setFillColor(sf::Color(60, 220, 60));
        texto_resultado.setPosition({ 40.f, 720.f });
        window.draw(texto_resultado);
    }
    else if (batalla.fase == fase_batalla::huida) {
        sf::Text texto_resultado(recursos.alagard);
        texto_resultado.setString("Escapaste con vida - ENTER para continuar");
        texto_resultado.setCharacterSize(22);
        texto_resultado.setFillColor(sf::Color::Cyan);
        texto_resultado.setPosition({ 40.f, 720.f });
        window.draw(texto_resultado);
    }

    // CARTEL GRANDE DE VICTORIA FINAL (TRAS VENCER AL BOSS)
    if (batalla.fase == fase_batalla::victoria_final) {
        const float PI = 3.14159265f;
        float t_v = batalla.reloj_anim.getElapsedTime().asSeconds();

        sf::RectangleShape velo_victoria({ 800.f, 800.f });
        velo_victoria.setFillColor(sf::Color(0, 0, 0, 200));
        window.draw(velo_victoria);

        float pulso = (std::sin(t_v * 3.0f) + 1.f) * 0.5f;
        std::uint8_t intensidad = static_cast<std::uint8_t>(180 + pulso * 75);

        sf::RectangleShape marco_victoria({ 700.f, 460.f });
        marco_victoria.setOrigin({ 350.f, 230.f });
        marco_victoria.setPosition({ 400.f, 400.f });
        marco_victoria.setFillColor(sf::Color(20, 15, 5, 240));
        marco_victoria.setOutlineColor(sf::Color(intensidad, static_cast<std::uint8_t>(intensidad * 0.78f), 30));
        marco_victoria.setOutlineThickness(5.f);
        window.draw(marco_victoria);

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

        float prog_titulo = std::min(1.f, t_v / 0.6f);
        std::uint8_t alpha_t = static_cast<std::uint8_t>(prog_titulo * 255.f);

        sf::Text titulo_victoria(recursos.alagard);
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

        if (t_v >= 0.6f) {
            float prog_msg = std::min(1.f, (t_v - 0.6f) / 0.8f);
            std::uint8_t alpha_m = static_cast<std::uint8_t>(prog_msg * 255.f);

            sf::Text felicitacion(recursos.alagard);
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

            sf::Text felicitacion2(recursos.alagard);
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

        if (t_v >= 1.4f) {
            float prog_rec = std::min(1.f, (t_v - 1.4f) / 0.6f);
            std::uint8_t alpha_r = static_cast<std::uint8_t>(prog_rec * 255.f);

            sf::Text texto_recompensa(recursos.alagard);
            texto_recompensa.setString(batalla.mensaje);
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

            sf::Text subtitulo(recursos.alagard);
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

        if (t_v >= 2.0f) {
            float alpha_hint = (std::sin(t_v * 2.5f) + 1.f) * 0.5f * 255.f;
            sf::Text hint(recursos.alagard);
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

    // CARTEL CON CINEMATICA DE DERROTA
    if (batalla.fase == fase_batalla::perdida) {
        float t_d = batalla.reloj_anim.getElapsedTime().asSeconds();

        float alpha_velo = std::min(1.f, t_d / 1.5f) * 240.f;
        sf::RectangleShape velo_derrota({ 800.f, 800.f });
        velo_derrota.setFillColor(sf::Color(0, 0, 0, static_cast<std::uint8_t>(alpha_velo)));
        window.draw(velo_derrota);

        if (t_d >= 0.8f) {
            float prog_tinte = std::min(1.f, (t_d - 0.8f) / 1.5f);
            float pulso_d = (std::sin(t_d * 1.5f) + 1.f) * 0.5f;
            sf::RectangleShape tinte_rojo({ 800.f, 800.f });
            tinte_rojo.setFillColor(sf::Color(80, 0, 0, static_cast<std::uint8_t>(prog_tinte * (50.f + pulso_d * 40.f))));
            window.draw(tinte_rojo);
        }

        if (t_d >= 1.2f) {
            float prog_marco = std::min(1.f, (t_d - 1.2f) / 0.6f);
            std::uint8_t alpha_m = static_cast<std::uint8_t>(prog_marco * 245.f);

            sf::RectangleShape marco_derrota({ 680.f, 320.f });
            marco_derrota.setOrigin({ 340.f, 160.f });
            marco_derrota.setPosition({ 400.f, 400.f });
            marco_derrota.setFillColor(sf::Color(20, 0, 0, alpha_m));
            marco_derrota.setOutlineColor(sf::Color(220, 40, 40, alpha_m));
            marco_derrota.setOutlineThickness(4.f);
            window.draw(marco_derrota);

            sf::RectangleShape linea_top({ 620.f, 4.f });
            linea_top.setOrigin({ 310.f, 2.f });
            linea_top.setPosition({ 400.f, 270.f });
            linea_top.setFillColor(sf::Color(220, 40, 40, alpha_m));
            window.draw(linea_top);

            sf::RectangleShape linea_bot({ 620.f, 4.f });
            linea_bot.setOrigin({ 310.f, 2.f });
            linea_bot.setPosition({ 400.f, 530.f });
            linea_bot.setFillColor(sf::Color(220, 40, 40, alpha_m));
            window.draw(linea_bot);
        }

        if (t_d >= 1.6f) {
            float prog_tit = std::min(1.f, (t_d - 1.6f) / 0.8f);
            std::uint8_t alpha_tit = static_cast<std::uint8_t>(prog_tit * 255.f);

            sf::Text titulo_derrota(recursos.alagard);
            titulo_derrota.setString("DERROTA");
            titulo_derrota.setCharacterSize(78);
            titulo_derrota.setFillColor(sf::Color(220, 40, 40, alpha_tit));
            titulo_derrota.setOutlineColor(sf::Color(0, 0, 0, alpha_tit));
            titulo_derrota.setOutlineThickness(5.f);
            {
                auto b = titulo_derrota.getLocalBounds();
                titulo_derrota.setOrigin({ b.size.x / 2.f, 0.f });
            }
            titulo_derrota.setPosition({ 400.f, 290.f });
            window.draw(titulo_derrota);
        }

        if (t_d >= 2.4f) {
            float prog_msg = std::min(1.f, (t_d - 2.4f) / 0.8f);
            std::uint8_t alpha_msg = static_cast<std::uint8_t>(prog_msg * 255.f);

            std::string linea1 = batalla.es_boss_actual
                ? std::string("El Guardian de la Mazmorra te ha vencido...")
                : std::string("La mazmorra ha reclamado tu vida...");

            sf::Text msg1(recursos.alagard);
            msg1.setString(linea1);
            msg1.setCharacterSize(22);
            msg1.setFillColor(sf::Color(255, 220, 220, alpha_msg));
            msg1.setOutlineColor(sf::Color(0, 0, 0, alpha_msg));
            msg1.setOutlineThickness(2.f);
            {
                auto b = msg1.getLocalBounds();
                msg1.setOrigin({ b.size.x / 2.f, 0.f });
            }
            msg1.setPosition({ 400.f, 405.f });
            window.draw(msg1);

            sf::Text msg2(recursos.alagard);
            msg2.setString("Tu aventura termina aqui.");
            msg2.setCharacterSize(20);
            msg2.setFillColor(sf::Color(200, 180, 180, alpha_msg));
            msg2.setOutlineColor(sf::Color(0, 0, 0, alpha_msg));
            msg2.setOutlineThickness(2.f);
            {
                auto b = msg2.getLocalBounds();
                msg2.setOrigin({ b.size.x / 2.f, 0.f });
            }
            msg2.setPosition({ 400.f, 445.f });
            window.draw(msg2);
        }

        if (t_d >= DURACION_DERROTA) {
            float pulso_h = (std::sin(t_d * 2.5f) + 1.f) * 0.5f;
            std::uint8_t alpha_h = static_cast<std::uint8_t>(150 + pulso_h * 105);

            sf::Text hint_d(recursos.alagard);
            hint_d.setString("Presiona ENTER para volver al menu");
            hint_d.setCharacterSize(20);
            hint_d.setFillColor(sf::Color(255, 255, 255, alpha_h));
            hint_d.setOutlineColor(sf::Color(0, 0, 0, alpha_h));
            hint_d.setOutlineThickness(2.f);
            {
                auto b = hint_d.getLocalBounds();
                hint_d.setOrigin({ b.size.x / 2.f, 0.f });
            }
            hint_d.setPosition({ 400.f, 510.f });
            window.draw(hint_d);
        }
    }
}

// NIVEL: CARGA Y DIBUJO
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
) {
	cargarnivel(numero_nivel, matriz_fondo, matriz_entidades);
	dibujarmapa(ventana, matriz_fondo, matriz_entidades,
		tex_suelo, tex_pared_arriba, tex_pared_abajo, tex_pared_izq, tex_pared_der,
		tex_prota, tex_boss, tex_enemigo, tex_mercader, tex_cofre, tex_salida);
}

