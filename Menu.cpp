#include "Menu.h"

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
