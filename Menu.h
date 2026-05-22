#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#pragma once

int iniciarJuego();

const int MAX_ITEMS = 6;

void inicializarMenu(std::vector<sf::Text>& opciones, const sf::Font& fuente, float width, float height);
void moverArriba(int& itemSeleccionado, std::vector<sf::Text>& opciones);
void moverAbajo(int& itemSeleccionado, std::vector<sf::Text>& opciones);
void dibujarMenu(sf::RenderWindow& window, const std::vector<sf::Text>& opciones);